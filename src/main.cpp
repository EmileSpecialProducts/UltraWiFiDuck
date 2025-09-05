#include <Arduino.h>
#include <FS.h> // File
#include <LittleFS.h>
#include <USB.h>
#include "config.h"
#include "debug.h"
#include "duckscript.hpp"
#include "webserver.h"
#include "settings.h"
#include "led.h"
#include "GPIO_trigger.hpp"

GpioTrigger Gpiotrigger;

void setup() {
    debug_init();
    DEBUG_PORT.printf(PRODUCTNAME "\n");
    DEBUG_PORT.printf("esp_idf_version: %d.%d.%d\n" ,ESP_IDF_VERSION_MAJOR ,ESP_IDF_VERSION_MINOR,ESP_IDF_VERSION_PATCH);
    DEBUG_PORT.printf("arduino_version: %d.%d.%d\n" ,ESP_ARDUINO_VERSION_MAJOR,ESP_ARDUINO_VERSION_MINOR,ESP_ARDUINO_VERSION_PATCH);
    DEBUG_PORT.printf("Build Date: " __DATE__ " " __TIME__ "\n");
    debugln("Initializing LittleFS...");
    LittleFS.begin(true);
    settings::begin();
    led::begin();
    duckscript_begin();

    delay(200);
    webserver::begin();
    Gpiotrigger.begin(settings::getRGBLedPinNum());
    if(strlen(settings::getAutorun())>0)duckscripts_run(settings::getAutorun());
    debugln("End of Setup");
}

void loop() {
    webserver::update();
    Gpiotrigger.update();
    debug_update();
}