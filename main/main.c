#include "main.h"

static const char TAG[] = "main";
static esp_err_t result_main_err;

void app_main(void)
{
    static httpd_handle_t websocket_server = NULL;

    ESP_LOGI(TAG, "Initializing NVS (Non-Volatile Storage).");
    result_main_err = nvs_flash_init();
    if(result_main_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize NVS.");
    }
    set_gpio_config();
    set_pwm_config();

    // TEST
    ESP_LOGI(TAG, "GPIO 32 state: %d", gpio_get_level(GPIO_NUM_32));
    result_main_err = gpio_set_level(GPIO_NUM_32, 1);
    if(result_main_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Error when setting gpio 32");
    }
    ESP_LOGI(TAG, "GPIO 32 state: %d", gpio_get_level(GPIO_NUM_32));

    ESP_LOGI(TAG, "GPIO 25 state: %d", gpio_get_level(GPIO_NUM_25));
    result_main_err = gpio_set_level(GPIO_NUM_25, 0);
    if(result_main_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Error when setting gpio 25");
    }
    ESP_LOGI(TAG, "GPIO 25 state: %d", gpio_get_level(GPIO_NUM_25));
    set_left_motor_duty(50);

    
    start_wifi();
    websocket_server = start_websocket_server();

}
