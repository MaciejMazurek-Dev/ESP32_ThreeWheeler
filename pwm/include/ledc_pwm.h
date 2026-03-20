#ifndef LEDC_PWM_H
#define LEDC_PWM_H

#include "driver/ledc.h"


void set_pwm_config(void);
void set_left_motor(int duty);
void set_right_motor(int duty);

#endif