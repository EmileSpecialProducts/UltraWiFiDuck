#include <Arduino.h>

#include "config.h"
#include "debug.h"
#include "duckscript.h"
#include "duckparser.h"
#include "webserver.h"
#include "spiffs.h"
#include "settings.h"
#include "cli.h"
#include "USB.h"


void setup() {
    debug_init();
    spiffs::begin();
    settings::begin();
    duckparser::beginKeyboard();
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