#include <Arduino.h>
#include <FS.h> // File
#include <LittleFS.h>
#include <USB.h>
#include "config.h"
#include "debug.h"
#include "duckscript.h"
#include "webserver.h"
#include "settings.h"
#include "cli.h"

#include "led.h"

void setup() {
    debug_init();                                         
    debugln( " esp_idf_version: " + String(ESP_IDF_VERSION_MAJOR) + "." + String(ESP_IDF_VERSION_MINOR) + "." + String(ESP_IDF_VERSION_PATCH));
    debugln( " arduino_version: " + String(ESP_ARDUINO_VERSION_MAJOR) + "." + String(ESP_ARDUINO_VERSION_MINOR) + "." + String(ESP_ARDUINO_VERSION_PATCH));
    debugln( " Build Date: " + String(__DATE__ " " __TIME__));
    debugln("Initializing LittleFS...");
    LittleFS.begin(true);
    settings::begin();
    led::begin();
    duckscript::begin();

    delay(200);
    cli::begin();
    webserver::begin();
    duckscript::run(settings::getAutorun());
    debugln("End of Setup");
}

void loop() {
    webserver::update();
    debug_update();
}