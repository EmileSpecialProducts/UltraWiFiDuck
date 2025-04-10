#pragma once
#ifndef _GPIO_TRIGGER_H_
#define _GPIO_TRIGGER_H_
#include <Arduino.h> // String
#include "debug.h"

#if defined (CONFIG_IDF_TARGET_ESP32S3)
const uint8_t gpio_pins[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,21,35,36,37,38,47,48}; // https://github.com/atomic14/esp32-s3-pinouts
#elif defined (CONFIG_IDF_TARGET_ESP32C3)
const uint8_t gpio_pins[]={0,1,2,3,4,5,6,7,10};
#elif defined (CONFIG_IDF_TARGET_ESP32C6)
const uint8_t gpio_pins[]={0};
#elif defined (CONFIG_IDF_TARGET_ESP32)
const uint8_t gpio_pins[]={0};
#endif
#define gpio_pins_len (sizeof(gpio_pins)/sizeof(gpio_pins[0]))

class GpioTrigger
{
private:
    uint8_t pinstate[gpio_pins_len]; 
    uint8_t ledpinNum;
public:
    GpioTrigger();
    void begin(int ledpinNum);
    void update();   
};

#endif // _GPIO_TRIGGER_H_