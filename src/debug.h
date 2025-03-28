/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#include <Arduino.h>
#include "config.h"
#include "commandline.h"


#define debug_init()              \
    DEBUG_PORT.begin(DEBUG_BAUD); \
    DEBUG_PORT.setTimeout(200);

#define debug_update() \
    {\
        if (DEBUG_PORT.available()) {\
        String output;\
        String input = DEBUG_PORT.readStringUntil('\n');\
        Commandline((char *)input.c_str(), &output);\
        DEBUG_PORT.println(output);\
       }\
    }


#ifdef ENABLE_DEBUG

#define debug(...) DEBUG_PORT.print(__VA_ARGS__)
#define debugln(...) DEBUG_PORT.println(__VA_ARGS__)
#define debugf(...) DEBUG_PORT.printf(__VA_ARGS__)

#else /* ifdef ENABLE_DEBUG */

#define debug(...) 0
#define debugln(...) 0
#define debugf(...) 0

#endif /* ifdef ENABLE_DEBUG */