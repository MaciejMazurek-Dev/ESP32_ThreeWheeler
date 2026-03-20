#include "gpio.h"

#define LEFT_MOTOR_FORWARD      CONFIG_LEFT_MOTOR_FORWARD
#define LEFT_MOTOR_REVERSE      CONFIG_LEFT_MOTOR_REVERSE

#define RIGHT_MOTOR_FORWARD     CONFIG_RIGHT_MOTOR_FORWARD
#define RIGHT_MOTOR_REVERSE     CONFIG_RIGHT_MOTOR_REVERSE

#define GPIO_PIN_BITMASK ((1ULL << LEFT_MOTOR_FORWARD) | (1ULL << LEFT_MOTOR_REVERSE) | (1ULL << RIGHT_MOTOR_FORWARD) | (1ULL << RIGHT_MOTOR_REVERSE))


void set_gpio_config()
{
    gpio_config_t config_data = { 
                                    .pin_bit_mask = (1ULL << GPIO_NUM_32 | 1ULL << GPIO_NUM_25),
                                    .mode = GPIO_MODE_INPUT_OUTPUT,
                                    .pull_up_en = GPIO_PULLUP_DISABLE,
                                    .pull_up_en = GPIO_PULLDOWN_DISABLE,
                                    .intr_type=GPIO_INTR_DISABLE
                                 };
    gpio_config(&config_data);

    
}

void set_gpio_default_levels()
{
    gpio_set_level(LEFT_MOTOR_FORWARD, 1);
    gpio_set_level(RIGHT_MOTOR_FORWARD, 1);
}