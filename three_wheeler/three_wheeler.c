#include "three_wheeler.h"


void set_gpio()
{
    gpio_config_t gpio_config = { 
                                    .mode = GPIO_MODE_OUTPUT,
                                    .pull_up_en = GPIO_PULLUP_DISABLE,
                                    .pull_up_en = GPIO_PULLDOWN_DISABLE,
                                    .intr_type=GPIO_INTR_DISABLE,
                                 };


}

