//Header Guards
#ifndef WIFI_STATION_H
#define WIFI_STATION_H

#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"


void wifi_station_init(void);
void wifi_configure(void);

#endif