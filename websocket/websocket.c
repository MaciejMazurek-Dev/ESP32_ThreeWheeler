#include "websocket.h"

static const char* TAG = "websocket";
static esp_err_t result_err;

static void register_uri_handlers(httpd_handle_t server)
{
    httpd_uri_t motor_uri = {
                                .uri = "/motor",
                                .method = HTTP_GET,
                                .handler = motor_uri_handler,
                                .user_ctx = NULL,
                                .is_websocket = true,
                            };
    httpd_register_uri_handler(server, &motor_uri);
}


httpd_handle_t start_websocket_server(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    
    ESP_LOGI(TAG, "Starting server...");
    result_err = httpd_start(&server, &config);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start server");
        return NULL;
    }
    ESP_LOGI(TAG, "Server started, listening on port: %d", config.server_port);

    ESP_LOGI(TAG, "Registering uri handlers");
    register_uri_handlers(server);
    return server;
}