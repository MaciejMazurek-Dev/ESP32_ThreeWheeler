#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include "esp_http_server.h"
#include "esp_log.h"

static esp_err_t test_uri_handler(httpd_req_t *req);
static void register_uri_handlers(httpd_handle_t server);
esp_err_t start_server(void);


#endif