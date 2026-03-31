idf_component_register(
        SRCS "uri_handlers.c" "websocket.c"
        INCLUDE_DIRS "include"
        REQUIRES esp_http_server pwm gpio
)