#ifndef GPIO_H
#define GPIO_H

#include "driver/gpio.h"

enum motor
{
    LEFT_MOTOR_FORWARD = CONFIG_LEFT_MOTOR_FORWARD,
    LEFT_MOTOR_REVERSE = CONFIG_LEFT_MOTOR_REVERSE,
    RIGHT_MOTOR_FORWARD = CONFIG_RIGHT_MOTOR_FORWARD,
    RIGHT_MOTOR_REVERSE = CONFIG_RIGHT_MOTOR_REVERSE,
};

/*
enum motor
{
    LEFT_MOTOR_FORWARD,      
    LEFT_MOTOR_REVERSE,      
    RIGHT_MOTOR_FORWARD,     
    RIGHT_MOTOR_REVERSE, 
};
*/

void config_gpio(void);
void set_motor(enum motor motor);

#endif