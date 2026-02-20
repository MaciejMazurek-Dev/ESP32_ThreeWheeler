#include "websocket.h"

static const char* TAG = "websocket";
static esp_err_t result_err;



static esp_err_t motor_uri_handler(httpd_req_t* request)
{
    // Struct for storing websocket frame
    httpd_ws_frame_t ws_frame;
    uint8_t *payload;
    
    // Set max_len to 0 to get the frame length
    result_err = httpd_ws_recv_frame(request, &ws_frame, 0);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get length of the frame");
        return ESP_FAIL;
    }
    ESP_LOGD(TAG, "Received WebSocket frame of length: %d", ws_frame.len);

    // Get the payload using the previously determined frame length
    result_err = httpd_ws_recv_frame(request, &ws_frame, ws_frame.len);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get frame payload");
        return ESP_FAIL;
    }
    return ESP_OK;
}


static void register_uri_handlers(httpd_handle_t server)
{
    httpd_uri_t motor_uri = {
                                .uri = "/motor",
                                .method = HTTP_GET,
                                .handler = motor_uri_handler,
                                .user_ctx = NULL,
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