/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#define VERSION "1.2.0"

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

#define MSG_CONNECTED "LED 0 0 25\n"
#define MSG_STARTED "LED 0 25 0\n"

/*! ===== WiFi Settings ===== */
#define WIFI_APSSID "wifiduck"
#define WIFI_APPASSWORD "wifiduck"
#define WIFI_CHANNEL "1"
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#define HOSTNAME "wifiduck"
#define URL "wifi.duck"
