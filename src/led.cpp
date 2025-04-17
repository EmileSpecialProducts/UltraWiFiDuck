/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#include "led.h"
#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "settings.h"
namespace led
{
    Adafruit_NeoPixel strip{NEOPIXEL_NUM, -1, NEO_GRB + NEO_KHZ800};

    void begin()
    {
        //DEBUG_PORT.printf("settings::getRGBLedPinNum() %d\n",settings::getRGBLedPinNum());
        if(settings::getRGBLedPinNum()!=-1)
        {
            strip.setPin(settings::getRGBLedPinNum());
            strip.begin();
            setColor(0, 0, 0);
        }

    }

    void setColor(int r, int g, int b, int start , int end )
    {
        if(settings::getRGBLedPinNum()!=-1)
        {
            if (start == 0 && end ==0 )
            {
                end = strip.numPixels();
            }
            if (end > strip.numPixels()) end = strip.numPixels();
            for (size_t i = start; i < end; i++)
            {
                strip.setPixelColor(i, r, g, b);
            }
            strip.show();       
        }
    }
}
