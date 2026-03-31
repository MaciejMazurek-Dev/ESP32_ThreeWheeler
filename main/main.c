#include "main.h"

static const char TAG[] = "main";

void app_main(void)
{
    static httpd_handle_t websocket_server = NULL;

    ESP_LOGI(TAG, "Initializing NVS (Non-Volatile Storage).");
    ESP_ERROR_CHECK(nvs_flash_init());
    
    config_pwm();
    config_gpio();
    
    start_wifi();
    websocket_server = start_websocket_server();
}
