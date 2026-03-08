#include "ledc_pwm.h"

#define LM_SPEED_MODE          LEDC_LOW_SPEED_MODE
#define LM_DUTY_RESOLUTION     LEDC_TIMER_8_BIT
#define LM_TIMER               LEDC_TIMER_0
#define LM_FREQUENCY           10000
#define LM_CLOCK               LEDC_AUTO_CLK
#define LM_DECONFIGURE         false

#define LM_GPIO         33
#define LM_CHANNEL      LEDC_CHANNEL_0
#define LM_INTR_TYPE    LEDC_INTR_DISABLE
#define LM_DUTY         0
#define LM_HPOINT       0
#define LM_SLEEP_MODE   LEDC_SLEEP_MODE_NO_ALIVE_NO_PD


void set_pwm_config()
{
    ledc_timer_config_t left_motor_timer = {
                                                .speed_mode = LM_SPEED_MODE,
                                                .duty_resolution = LM_DUTY_RESOLUTION,
                                                .timer_num = LM_TIMER,
                                                .freq_hz = LM_FREQUENCY,
                                                .clk_cfg = LM_CLOCK,
                                                .deconfigure = LM_DECONFIGURE
                                            };

    ledc_timer_config(&left_motor_timer);

    ledc_channel_config_t left_motor_channel = {
                                                    .gpio_num = LM_GPIO,
                                                    .speed_mode = LM_SPEED_MODE,
                                                    .channel = LM_CHANNEL,
                                                    .intr_type = LM_INTR_TYPE,
                                                    .timer_sel = LM_TIMER,
                                                    .duty = LM_DUTY,
                                                    .hpoint = LM_HPOINT,
                                                    .sleep_mode = LM_SLEEP_MODE,
                                               };

    ledc_channel_config(&left_motor_channel);
}

void set_left_motor_duty(int speed)
{
    ESP_ERROR_CHECK(ledc_set_duty(LM_SPEED_MODE, LM_CHANNEL, speed));
    ESP_ERROR_CHECK(ledc_update_duty(LM_SPEED_MODE, LM_CHANNEL));
}