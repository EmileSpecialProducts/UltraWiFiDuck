/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#define VERSION "2.2.0"
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


/*! ===== WiFi Settings ===== */
#define WIFI_APSSID "UltraWiFiDuck"
#define WIFI_APPASSWORD ""
#define WIFI_CHANNEL "1"
#define WIFI_SSID ""
#define WIFI_PASSWORD ""



#if   defined(CONFIG_IDF_TARGET_ESP32C3)
#define RGBLEDPIN "8"
#define _TARGET_ESP_ "ESP32-C3"
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
#define RGBLEDPIN "8"
#define _TARGET_ESP_ "ESP32-C6"
#elif defined(CONFIG_IDF_TARGET_ESP32S2)
#define RGBLEDPIN ""
#define _TARGET_ESP_ "ESP32-S2"
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
#define _TARGET_ESP_ "ESP32-S3"
#define RGBLEDPIN "48"
#endif

#define HOSTNAME "UltraWiFiDuck"

#define CUSTOM_USB_PRODUCT "UltraWiFiDuck"
#define CUSTOM_USB_PID 0x0002
#define CUSTOM_USB_VID 0x303a
#define CUSTOM_USB_MANUFACTURER "Espressif Systems"

#define NEOPIXEL_NUM 144  // So that you can connect a 1 meter led strip 