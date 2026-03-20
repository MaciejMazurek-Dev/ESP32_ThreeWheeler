#include "uri_handlers.h"

static char TAG[] = "uri_handlers";
static esp_err_t result_err;


static esp_err_t get_payload(httpd_req_t *request, uint8_t **out_payload)
{
    if(request->method == HTTP_GET)
    {
        return check_websocket_upgrade(request);
    }

    httpd_ws_frame_t ws_frame = {0}; 
    // Set max_len to 0 to get the frame length first
    result_err = httpd_ws_recv_frame(request, &ws_frame, 0);
    if(result_err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get length of the frame.");
        return result_err;
    }

    if(ws_frame.len)
    {
        ESP_LOGI(TAG, "Length of payload: %d", ws_frame.len);
        uint8_t *payload = calloc(1, ws_frame.len + 1);
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
            free(payload);
            return ESP_FAIL;
        }
        ESP_LOGI(TAG, "Message received: %s", ws_frame.payload);
        *out_payload = payload;
        return ESP_OK;
    }
    ESP_LOGW(TAG, "Received empty frame");
    return ESP_FAIL;
}

static esp_err_t check_websocket_upgrade(httpd_req_t *request)
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
        ESP_LOGE(TAG, "Unknown protocol");
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "Handshake complete. Connection upgraded to WebSocket");
    return ESP_OK;
}

esp_err_t motor_uri_handler(httpd_req_t *request)
{
    uint8_t *payload = NULL;
    result_err = get_payload(request, &payload);
    if(result_err != ESP_OK)
    {
        return result_err;
    } else if(payload == NULL)
    {
        ESP_LOGI(TAG, "Payload is empty");
        return ESP_OK;
    }

    if(payload[0] == 'L')
    {
        set_left_motor(150);
        
    } else if(payload[0] == 'R')
    {
        set_right_motor(150);
    }
    free(payload);
    return ESP_OK;    
}

