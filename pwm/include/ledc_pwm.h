#ifndef LEDC_PWM_H
#define LEDC_PWM_H

#include "driver/ledc.h"


void config_pwm(void);
void set_left_motor_speed(int8_t duty);
void set_right_motor_speed(int8_t duty);

#endif