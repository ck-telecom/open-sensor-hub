#ifndef _LED_DRIVER_H
#define _LED_DRIVER_H

#include "stm32f4xx_hal.h"

int32_t LED_Initialize (void);
int32_t LED_On (uint32_t num);
int32_t LED_Off (uint32_t num);
int32_t LED_Toggle(uint32_t num);

enum LED_NO {
    LED_YELLOW,
    LED_GREEN,
    LED_RED,
    LED_BLUE,
    LED_MAX
};

#endif
