#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include "esp_http_server.h"
#include "esp_log.h"
#include "handlers.h"

static esp_err_t motor_uri_handler(httpd_req_t* request);
static void register_uri_handlers(httpd_handle_t server);
httpd_handle_t start_websocket_server(void);


#endif