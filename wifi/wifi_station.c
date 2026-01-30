#include "wifi_station.h"

#define WIFI_SSID       CONFIG_WIFI_SSDI
#define WIFI_PASSWORD   CONFIG_WIFI_PASSWORD


static const char TAG[] = "wifi_station"; 

esp_err_t result_err;
esp_netif_t* result_netif;


static void wifi_event_handler(void* handler_arg, 
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void* event_data)
{
    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        result_err = esp_wifi_connect();
    }
}



void wifi_station_init(void)
{
    result_err = esp_netif_init();
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize TCP/IP stack.");
        return;
    }

    result_err = esp_event_loop_create_default();
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start event loop.");
        return;
    }

    result_netif = esp_netif_create_default_wifi_sta();
    if(result_netif != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to create network interface.");
        return;
    }

    wifi_init_config_t defaultConfiguration = WIFI_INIT_CONFIG_DEFAULT();
    result_err = esp_wifi_init(&defaultConfiguration);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize WiFi driver.");
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

    result_err = esp_wifi_set_mode(WIFI_MODE_STA);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set WiFi mode.");
        return;
    }
    
    result_err = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to configure WiFi.");
        return;
    }

    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL);

    // The startup function is asynchronous: it returns immediately and does not wait for the completion of the startup process.
    result_err = esp_wifi_start();
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start WiFi driver.");
        return;
    }





}
