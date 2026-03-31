#include "ledc_pwm.h"

#define TIMER_SPEED_MODE          LEDC_LOW_SPEED_MODE
#define TIMER_DUTY_RESOLUTION     LEDC_TIMER_8_BIT
#define TIMER_TIMER               LEDC_TIMER_0
#define TIMER_FREQUENCY           500
#define TIMER_CLOCK               LEDC_AUTO_CLK
#define TIMER_DECONFIGURE         false

// Left motor channel configuration
#define LM_GPIO         CONFIG_LM_PWM_GPIO
#define LM_CHANNEL      LEDC_CHANNEL_0
#define LM_INTR_TYPE    LEDC_INTR_DISABLE
#define LM_DUTY         150
#define LM_HPOINT       0
#define LM_SLEEP_MODE   LEDC_SLEEP_MODE_NO_ALIVE_NO_PD

// Right motor channel configuration
#define RM_GPIO         CONFIG_RM_PWM_GPIO
#define RM_CHANNEL      LEDC_CHANNEL_1
#define RM_INTR_TYPE    LEDC_INTR_DISABLE
#define RM_DUTY         150
#define RM_HPOINT       0
#define RM_SLEEP_MODE   LEDC_SLEEP_MODE_NO_ALIVE_NO_PD


void config_pwm(void)
{
    ledc_timer_config_t left_motor_timer = {
                                                .speed_mode = TIMER_SPEED_MODE,
                                                .duty_resolution = TIMER_DUTY_RESOLUTION,
                                                .timer_num = TIMER_TIMER,
                                                .freq_hz = TIMER_FREQUENCY,
                                                .clk_cfg = TIMER_CLOCK,
                                                .deconfigure = TIMER_DECONFIGURE
                                            };

    ESP_ERROR_CHECK(ledc_timer_config(&left_motor_timer));

    ledc_channel_config_t left_motor_channel = {
                                                    .gpio_num = LM_GPIO,
                                                    .speed_mode = TIMER_SPEED_MODE,
                                                    .channel = LM_CHANNEL,
                                                    .intr_type = LM_INTR_TYPE,
                                                    .timer_sel = TIMER_TIMER,
                                                    .duty = LM_DUTY,
                                                    .hpoint = LM_HPOINT,
                                                    .sleep_mode = LM_SLEEP_MODE
                                               };
    ESP_ERROR_CHECK(ledc_channel_config(&left_motor_channel));

    ledc_channel_config_t right_motor_channel = {
                                                    .gpio_num = RM_GPIO,
                                                    .speed_mode = TIMER_SPEED_MODE,
                                                    .channel = RM_CHANNEL,
                                                    .intr_type = RM_INTR_TYPE,
                                                    .timer_sel = TIMER_TIMER,
                                                    .duty = RM_DUTY,
                                                    .hpoint = RM_HPOINT,
                                                    .sleep_mode = RM_SLEEP_MODE
                                                };
    ESP_ERROR_CHECK(ledc_channel_config(&right_motor_channel));
}

void set_left_motor_speed(int8_t duty)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_set_duty(TIMER_SPEED_MODE, LM_CHANNEL, duty));
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_update_duty(TIMER_SPEED_MODE, LM_CHANNEL));
}

void set_right_motor_speed(int8_t duty)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_set_duty(TIMER_SPEED_MODE, RM_CHANNEL, duty));
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_update_duty(TIMER_SPEED_MODE, RM_CHANNEL));
}

