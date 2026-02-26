#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include "uri_handlers.h"

static void register_uri_handlers(httpd_handle_t server);
httpd_handle_t start_websocket_server(void);


#endif