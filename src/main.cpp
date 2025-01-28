#include <Arduino.h>
#include <FS.h> // File
#include <LittleFS.h>
#include <USB.h>

#include "config.h"
#include "debug.h"
#include "duckscript.h"
#include "duckparser.h"
#include "webserver.h"
#include "settings.h"
#include "cli.h"

#include "led.h"

void setup() {
    debug_init();

    debug("Initializing LittleFS...");
    LittleFS.begin(true);
    settings::begin();
    led::begin();
    duckparser::beginKeyboard();
    USB.productName(CUSTOM_USB_PRODUCT);
    USB.VID(CUSTOM_USB_VID);
    USB.PID(CUSTOM_USB_PID);
    USB.manufacturerName(CUSTOM_USB_MANUFACTURER);
    USB.begin();
    delay(200);
    cli::begin();
    webserver::begin();
    duckscript::run(settings::getAutorun());
}

void loop() {
    webserver::update();
    debug_update();
}