idf_component_register(
        SRCS "websocket.c"
        INCLUDE_DIRS "include"
        PRIV_REQUIRES esp_http_server
)