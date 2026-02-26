#ifndef URI_HANDLERS_H
#define URI_HANDLERS_H

#include "esp_http_server.h"
#include "esp_log.h"

esp_err_t motor_uri_handler(httpd_req_t* request);

#endif