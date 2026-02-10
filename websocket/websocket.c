#include "websocket.h"

static const char* TAG = "websocket";
static esp_err_t result_err;


static esp_err_t test_uri_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Knock Knock Neo");
    return ESP_OK;
}

static void register_uri_handlers(httpd_handle_t server)
{
    httpd_uri_t test_uri = {
                                .uri = "/test",
                                .method = HTTP_GET,
                                .handler = test_uri_handler,
                                .user_ctx = NULL
                            };

    httpd_register_uri_handler(server, &test_uri);
}

esp_err_t start_server(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    ESP_LOGI(TAG, "Starting server...");
    result_err = httpd_start(&server, &config);
    if(result_err != ESP_OK)
    {
        ESP_LOGI(TAG, "Failed to start server");
        return result_err;
    }
    ESP_LOGI(TAG, "Server started, listening on port: %d", config.server_port);

    ESP_LOGI(TAG, "Registering uri handlers");
    register_uri_handlers(server);
    return ESP_OK;
}