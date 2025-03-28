/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#define VERSION "2.1.0"
#define PRODUCTNAME "UltraWiFiDuck"
/*! ===== DEBUG Settings ===== */
//#define ENABLE_DEBUG
#define DEBUG_PORT Serial
#define DEBUG_BAUD 115200

/*! ===== Communication Settings ===== */
// #define ENABLE_SERIAL
#define SERIAL_PORT DEBUG_PORT
#define SERIAL_BAUD DEBUG_BAUD

#define BUFFER_SIZE 1024
#define PACKET_SIZE 32

/*! ===== WiFi Settings ===== */
#define WIFI_APSSID "UltraWiFiDuck"
#define WIFI_APPASSWORD ""
#define WIFI_CHANNEL "1"
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define RGBLEDPIN ""

#define HOSTNAME "UltraWiFiDuck"
#define URL "UltraWiFiDuck.duck"

#define CUSTOM_USB_PRODUCT "UltraWiFiDuck"
#define CUSTOM_USB_PID 0x0002
#define CUSTOM_USB_VID 0x303a
#define CUSTOM_USB_MANUFACTURER "Espressif Systems"

#define NEOPIXEL_NUM 144  // So that you can connect a 1 meter led strip 