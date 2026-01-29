#include "wifi_station.h"

#define WIFI_SSID       CONFIG_WIFI_SSDI
#define WIFI_PASSWORD   CONFIG_WIFI_PASSWORD


static const char TAG[] = "wifi_station"; 

esp_err_t result_err;
esp_netif_t* result_netif;


void wifi_station_init(void)
{
    //INIT PHASE
    // Initialize network stack
    result_err = esp_netif_init();
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize TCP/IP stack.");
        return;
    }

    // Start default event loop
    result_err = esp_event_loop_create_default();
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start event loop.");
        return;
    }

    // Create default network interface 
    result_netif = esp_netif_create_default_wifi_sta();
    if(result_netif != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to create network interface.");
    }

    // Create task and initialize WiFi driver.
    wifi_init_config_t defaultConfiguration = WIFI_INIT_CONFIG_DEFAULT();
    result_err = esp_wifi_init(&defaultConfiguration);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize WiFi driver.");
    }



    // CONFIGURATION PHASE
    // Configuration data
    wifi_config_t wifi_config = {
                                 .sta = {
                                            .ssid = WIFI_SSID,
                                            .password = WIFI_PASSWORD,
                                            // Set minimum authentication mode
                                            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
                                        },
                                };

    // Set to Station Mode                                       
    result_err = esp_wifi_set_mode(WIFI_MODE_STA);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set WiFi mode.");
    }
    
    result_err = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to configure WiFi.");
    }




}
