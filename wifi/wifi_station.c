#include "wifi_station.h"

#define WIFI_SSID       CONFIG_WIFI_SSDI
#define WIFI_PASSWORD   CONFIG_WIFI_PASSWORD


static const char TAG[] = "wifi_station"; 

#define WIFI_CONNECTED_BIT 0x01
EventGroupHandle_t wifi_event_group_handle;

esp_err_t result_err;
esp_netif_t* result_netif;


// Handle Wi-Fi start event and initiate connection
static void wifi_start_event_handler(void* handler_arg, 
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void* event_data)
{
    if(event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(TAG, "Trying to connect %s access point...", WIFI_SSID);
        result_err = esp_wifi_connect();
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
        xEventGroupSetBits(wifi_event_group_handle, WIFI_CONNECTED_BIT);
    }
}



void wifi_station_init(void)
{
    ESP_LOGI(TAG, "Initializing TCP/IP stack");
    result_err = esp_netif_init();
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize TCP/IP stack.");
        return;
    }

    // Create the default event loop, which is a special type of loop used for system events (Wi-Fi, Bluetooth, etc.).
    result_err = esp_event_loop_create_default();
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to create default event loop.");
        return;
    }

    // Create (and return pointer to) esp_netif object, register wifi handlers to the default event loop.
    esp_netif_create_default_wifi_sta();
    
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_start_event_handler, NULL, NULL);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_event_handler, NULL, NULL);

    // Initialize WiFi: allocate resources for the driver and start the WiFi task.   
    wifi_init_config_t defaultConfiguration = WIFI_INIT_CONFIG_DEFAULT();
    result_err = esp_wifi_init(&defaultConfiguration);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize WiFi driver.");
        return;
    }

    result_err = esp_wifi_set_mode(WIFI_MODE_STA);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set WiFi mode.");
        return;
    }
    
    wifi_config_t wifi_config = {
                                 .sta = {
                                            .ssid = WIFI_SSID,
                                            .password = WIFI_PASSWORD,
                                            // Set minimum authentication mode
                                            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
                                        },
                                };
    result_err = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to configure WiFi.");
        return;
    }

    // The startup function is asynchronous: it returns immediately and does not wait for the completion of the startup process.
    result_err = esp_wifi_start();
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start WiFi driver.");
        return;
    }

    // Create an event group (FreeRTOS feature) used to block a task until certain conditions are met.
    wifi_event_group_handle = xEventGroupCreate();
    if(wifi_event_group_handle == NULL)
    {
        ESP_LOGE(TAG, "Failed to create event group (insufficient heap memory?).");
        return;
    }

    // Block Task - Wait for connection
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group_handle, WIFI_CONNECTED_BIT, pdFALSE, pdFALSE, portMAX_DELAY);

    ESP_LOGI(TAG, "Connection successful.");



    



}
