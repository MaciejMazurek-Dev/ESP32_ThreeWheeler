#include "gpio.h"

#define LEFT_MOTOR      CONFIG_LEFT_MOTOR
#define LEFT_MOTOR_PWM  CONFIG_LEFT_MOTOR_PWM

#define RIGHT_MOTOR     CONFIG_RIGHT_MOTOR
#define RIGHT_MOTOR_PWM CONFIG_RIGHT_MOTOR_PWM

#define GPIO_PIN_BITMASK ((1ULL << LEFT_MOTOR) | (1ULL << LEFT_MOTOR_PWM) | (1ULL << RIGHT_MOTOR) | (1ULL << RIGHT_MOTOR_PWM))



void set_gpio_configuration()
{
    gpio_config_t gpio_config = { 
                                    .pin_bit_mask = GPIO_PIN_BITMASK,
                                    .mode = GPIO_MODE_OUTPUT,
                                    .pull_up_en = GPIO_PULLUP_DISABLE,
                                    .pull_up_en = GPIO_PULLDOWN_DISABLE,
                                    .intr_type=GPIO_INTR_DISABLE
                                 };
}

