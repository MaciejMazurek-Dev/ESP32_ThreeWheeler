#include "wifi_station.h"

#define WIFI_SSID       CONFIG_WIFI_SSDI
#define WIFI_PASSWORD   CONFIG_WIFI_PASSWORD


static const char TAG[] = "wifi_station"; 

#define WIFI_CONNECTED_BIT 0x01
EventGroupHandle_t wifi_event_group_handle;

static esp_err_t result_wifi_err;


// Handle Wi-Fi start event and initiate connection
static void wifi_start_event_handler(void* handler_arg, 
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void* event_data)
{
    if(event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(TAG, "Trying to connect %s access point...", WIFI_SSID);
        result_wifi_err = esp_wifi_connect();
    }else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        ESP_LOGI(TAG, "Connection failed. Trying again...");
        esp_wifi_connect();
    }
}

// Got IP address from the AP. Set the WIFI_CONNECTED_BIT for the event group
static void ip_event_handler(void* handler_arg, 
                             esp_event_base_t event_base,
                             int32_t event_id,
                             void* event_data)
{
    if(event_id == IP_EVENT_STA_GOT_IP)
    {
        ESP_LOGI(TAG, "Connected with access point. IP");
        xEventGroupSetBits(wifi_event_group_handle, WIFI_CONNECTED_BIT);
    }
}



void wifi_station_init(void)
{
    ESP_LOGI(TAG, "Initializing TCP/IP stack");
    result_wifi_err = esp_netif_init();
    if(result_wifi_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize TCP/IP stack.");
        return;
    }

    ESP_LOGI(TAG, "Creating default event loop");
    result_wifi_err = esp_event_loop_create_default();
    if(result_wifi_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to create default event loop.");
        return;
    }

    ESP_LOGI(TAG, "Create default network interface.");
    esp_netif_create_default_wifi_sta();
    
    ESP_LOGI(TAG, "Registering event handlers");
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_start_event_handler, NULL, NULL);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_event_handler, NULL, NULL);

    ESP_LOGI(TAG, "Initializing WiFi - Allocate resources for the driver and start the WiFi task.");   
    wifi_init_config_t defaultConfiguration = WIFI_INIT_CONFIG_DEFAULT();
    result_wifi_err = esp_wifi_init(&defaultConfiguration);
    if(result_wifi_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize WiFi driver.");
        return;
    }

    ESP_LOGI(TAG, "Setting WiFi mode as station.");
    result_wifi_err = esp_wifi_set_mode(WIFI_MODE_STA);
    if(result_wifi_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set WiFi mode.");
        return;
    }
    
    ESP_LOGI(TAG, "Configuring WiFi (SSID, password etc.)");
    wifi_config_t wifi_config = {
                                 .sta = {
                                            .ssid = WIFI_SSID,
                                            .password = WIFI_PASSWORD,
                                            // Set minimum authentication mode
                                            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
                                        },
                                };
    result_wifi_err = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    if(result_wifi_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to configure WiFi.");
        return;
    }

    // The startup function is asynchronous, it returns immediately.
    ESP_LOGI(TAG, "Starting WiFi driver.");
    result_wifi_err = esp_wifi_start();
    if(result_wifi_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start WiFi driver.");
        return;
    }

    // Create an event group (FreeRTOS feature) used to block a task until certain conditions are met.
    ESP_LOGI(TAG, "Creating event group.");
    wifi_event_group_handle = xEventGroupCreate();
    if(wifi_event_group_handle == NULL)
    {
        ESP_LOGE(TAG, "Failed to create event group (insufficient heap memory?).");
        return;
    }

    // Block Task - Wait for successful connection
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group_handle, WIFI_CONNECTED_BIT, pdFALSE, pdFALSE, portMAX_DELAY);

    // TODO: How to handle unsuccessful connection?

    ESP_LOGI(TAG, "Connected with %s access point.", WIFI_SSID);



    



}
