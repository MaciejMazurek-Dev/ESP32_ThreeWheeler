#ifndef URI_HANDLERS_H
#define URI_HANDLERS_H

#include "esp_http_server.h"
#include "esp_log.h"
#include "ledc_pwm.h"

esp_err_t motor_uri_handler(httpd_req_t *request);
static esp_err_t check_websocket_upgrade(httpd_req_t *request);
static esp_err_t get_payload(httpd_req_t *request, u_int8_t *out_payload);

#endif