/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#define VERSION "2.0.0"

/*! ===== DEBUG Settings ===== */
//#define ENABLE_DEBUG
#define DEBUG_PORT Serial
#define DEBUG_BAUD 115200

/*! ===== Communication Settings ===== */
// #define ENABLE_SERIAL
#define SERIAL_PORT Serial
#define SERIAL_BAUD 115200

#define BUFFER_SIZE 256
#define PACKET_SIZE 32

/*! ===== WiFi Settings ===== */
#define WIFI_APSSID "wifiduck"
#define WIFI_APPASSWORD "wifiduck"
#define WIFI_CHANNEL "1"
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define RGBLEDPIN ""

#define HOSTNAME "wifiduck"
#define URL "wifi.duck"

#define NEOPIXEL_NUM 144  // So that you can connect a 1 meter led strip 