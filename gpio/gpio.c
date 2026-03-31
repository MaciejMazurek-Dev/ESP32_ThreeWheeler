#include "gpio.h"

/*
#define LEFT_MOTOR_FORWARD      CONFIG_LEFT_MOTOR_FORWARD
#define LEFT_MOTOR_REVERSE      CONFIG_LEFT_MOTOR_REVERSE

#define RIGHT_MOTOR_FORWARD     CONFIG_RIGHT_MOTOR_FORWARD
#define RIGHT_MOTOR_REVERSE     CONFIG_RIGHT_MOTOR_REVERSE
*/

#define GPIO_PIN_BITMASK ((1ULL << LEFT_MOTOR_FORWARD) | (1ULL << LEFT_MOTOR_REVERSE) | (1ULL << RIGHT_MOTOR_FORWARD) | (1ULL << RIGHT_MOTOR_REVERSE))


void config_gpio()
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

void set_motor(enum motor motor)
{
    switch(motor)
    {
        case LEFT_MOTOR_FORWARD:
            gpio_set_level(LEFT_MOTOR_REVERSE, 0);
            break;
        case LEFT_MOTOR_REVERSE:
            gpio_set_level(LEFT_MOTOR_FORWARD, 0);
            break;
        case RIGHT_MOTOR_FORWARD:
            gpio_set_level(RIGHT_MOTOR_REVERSE, 0);
            break;
        case RIGHT_MOTOR_REVERSE:
            gpio_set_level(RIGHT_MOTOR_FORWARD, 0);
            break;
    }
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_set_level(motor, 1));
}