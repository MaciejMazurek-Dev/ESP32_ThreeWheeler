#include "main.h"

static const char TAG[] = "main";
static esp_err_t result_main_err;

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing NVS (Non-Volatile Storage).");
    result_main_err = nvs_flash_init();
    if(result_main_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize NVS.");
    }
    start_wifi();
    start_server();
}
