#include "uri_handlers.h"

static char* TAG = "uri_handlers";
static esp_err_t result_err;

esp_err_t motor_uri_handler(httpd_req_t* request)
{
    if(request->method == HTTP_GET)
    {
        char hdr_value_buffer[11];
        result_err = httpd_req_get_hdr_value_str(request, "Upgrade", hdr_value_buffer, sizeof(hdr_value_buffer));
        if(result_err != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to switch protocols");
            return ESP_FAIL;
        }
        int result = strcmp(hdr_value_buffer, "websocket");
        if(result != 0)
        {
            ESP_LOGE(TAG, "Protocol not supported");
            return ESP_FAIL;
        }
        ESP_LOGI(TAG, "Handshake complete. Connection upgraded to WebSocket");
        return ESP_OK;
    }

    httpd_ws_frame_t ws_frame = { 0 };
    uint8_t *payload;
    // Set max_len to 0 to get the frame length
    result_err = httpd_ws_recv_frame(request, &ws_frame, 0);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get length of the frame.");
        return ESP_FAIL;
    }
    
    if(ws_frame.len)
    {
        payload = calloc(0, ws_frame.len);
        if(payload == NULL)
        {
            ESP_LOGE(TAG, "Failed to allocate memory for payload");
            return ESP_ERR_NO_MEM;
        }
        ws_frame.payload = payload;
        // Get the payload using the previously determined frame length
        result_err = httpd_ws_recv_frame(request, &ws_frame, ws_frame.len);
        if(result_err != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to get frame payload.");
            return ESP_FAIL;
        }
        ESP_LOGI(TAG, "Message received: %s", ws_frame.payload);
        return ESP_OK;
    }
    ESP_LOGW(TAG, "Received empty frame");
    return ESP_FAIL;
}