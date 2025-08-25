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
        static char input[40]="";\
        static char output[2048]="";\
        static int input_len=0;\
        while(DEBUG_PORT.available()) {\
            int c= DEBUG_PORT.read();\
            if ( c=='\b' )\
            {\
                if(input_len > 0) input[--input_len]=0;\
            }\
            if ( c=='\r' || c=='\n' )\
            {\
                if(strlen(input)>0){ Commandline(input, output, sizeof(output));DEBUG_PORT.println(output);}\
                memset(input,0,sizeof(input));\
                input_len=0;\
            }\
            if(c>=' ' && c<127 && input_len < (sizeof(input)-1))\
            {\
                input[input_len++]=(char)c;\
                input[input_len]=0;\
            }\
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