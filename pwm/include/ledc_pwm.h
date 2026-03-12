#ifndef LEDC_PWM_H
#define LEDC_PWM_H

#include "driver/ledc.h"


void set_pwm_config(void);
void set_left_motor_duty(int speed);

#endif