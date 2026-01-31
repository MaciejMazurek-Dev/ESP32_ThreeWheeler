//Header Guards
#ifndef WIFI_STATION_H
#define WIFI_STATION_H

#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

static void wifi_start_event_handler(void* arg, 
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void* event_data);
                               
static void ip_event_handler(void* arg,
                             esp_event_base_t event_base,
                             int32_t event_id,
                             void* event_data);

void wifi_station_init(void);
void wifi_configure(void);

#endif