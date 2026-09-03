#pragma once
#ifndef _GPIO_TRIGGER_H_
#define _GPIO_TRIGGER_H_
#include <Arduino.h> // String
#include "debug.h"

#if defined (CONFIG_IDF_TARGET_ESP32S3)
const uint8_t gpio_pins[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,21,35,36,37,38,47,48}; // https://github.com/atomic14/esp32-s3-pinouts
#elif defined (CONFIG_IDF_TARGET_ESP32S2)
const uint8_t gpio_pins[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,21,22,26};
#elif defined (CONFIG_IDF_TARGET_ESP32C2)
const uint8_t gpio_pins[]={0,1,2,3,8,9,10,18}; // 20=TXD,19=RXD  
#elif defined (CONFIG_IDF_TARGET_ESP32C3)
const uint8_t gpio_pins[]={0,1,2,3,4,5,6,7,8,9,10}; // 21=TXD,20=RXD 18=USB-D- 19=USB-D+ 
#elif defined (CONFIG_IDF_TARGET_ESP32C5)
const uint8_t gpio_pins[]={0,1,2,3,6,7,8,9,10,15,23,24,25,26,27,28}; // 11=TXD,12=RXD 13=USB-D- 14=USB-D+ 28 = boot 
#elif defined (CONFIG_IDF_TARGET_ESP32C61)
const uint8_t gpio_pins[]={0,1,2,3,4,5,6,7,8,9,22,23,24,25,26,27,28,29}; // 11=TXD,10=RXD 12=USB-D- 13=USB-D+ 9=Boot 
#elif defined (CONFIG_IDF_TARGET_ESP32C6)
const uint8_t gpio_pins[]={0,1,2,3,4,5,6,7,8,9,10,11,15,18,19,20,21,22,23,27}; // 16=TXD,17=RXD 12=USB-D- 13=USB-D+ 9=Boot
#elif defined (CONFIG_IDF_TARGET_ESP32)
const uint8_t gpio_pins[]={0};
#endif
#define gpio_pins_len (sizeof(gpio_pins)/sizeof(gpio_pins[0]))

class GpioTrigger
{
private:
    uint8_t pinstate[gpio_pins_len]; 
    int ledpinNum;
public:
    GpioTrigger();
    void begin(int ledpinNum);
    void update();   
};

#endif // _GPIO_TRIGGER_H_