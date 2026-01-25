#include "wifi_station.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_wifi.h"

static const char TAG[] = "wifi_station"; 


void wifi_station_init(void)
{
    esp_err_t resultErr;
    esp_netif_t* resultNetif;

    // Initialize network stack
    resultErr = esp_netif_init();
    if(resultErr != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize TCP/IP stack.");
        return;
    }

    // Start default event loop
    resultErr = esp_event_loop_create_default();
    if(resultErr != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start event loop.");
        return;
    }

    // Create default network interface 
    resultNetif = esp_netif_create_default_wifi_sta();
    if(resultNetif != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to create network interface.");
    }

    // Create WiFi driver task and initialize WiFi driver.
    wifi_init_config_t defaultConfiguration = WIFI_INIT_CONFIG_DEFAULT();
    resultErr = esp_wifi_init(&defaultConfiguration);
    if(resultErr != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize WiFi driver.");
    }
}