#include "gpio.h"

#define LEFT_MOTOR_FORWARD      CONFIG_LEFT_MOTOR_FORWARD
#define LEFT_MOTOR_REVERSE      CONFIG_LEFT_MOTOR_REVERSE

#define RIGHT_MOTOR_FORWARD     CONFIG_RIGHT_MOTOR_FORWARD
#define RIGHT_MOTOR_REVERSE     CONFIG_RIGHT_MOTOR_REVERSE

#define GPIO_PIN_BITMASK ((1ULL << LEFT_MOTOR_FORWARD) | (1ULL << LEFT_MOTOR_REVERSE) | (1ULL << RIGHT_MOTOR_FORWARD) | (1ULL << RIGHT_MOTOR_REVERSE))

enum MOTOR
{
    Left_Forward =  LEFT_MOTOR_FORWARD,
    Left_Reverse =  LEFT_MOTOR_REVERSE,
    Right_Forward = RIGHT_MOTOR_FORWARD,
    Right_Reverse = RIGHT_MOTOR_REVERSE,
};     

static void set_config()
{
    gpio_config_t config_data = { 
                                    .pin_bit_mask = GPIO_PIN_BITMASK,
                                    .mode = GPIO_MODE_OUTPUT,
                                    .pull_up_en = GPIO_PULLUP_DISABLE,
                                    .pull_down_en = GPIO_PULLDOWN_ENABLE,
                                    .intr_type=GPIO_INTR_DISABLE
                                 };
    ESP_ERROR_CHECK(gpio_config(&config_data));    
}

void set_gpio(void)
{
    set_config();

}
