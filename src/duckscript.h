/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#include <Arduino.h> // String
#include "USBHID.h"
#include "USB.h"
#include <class/hid/hid.h>
#include <class/hid/hid_device.h>
#if defined(CONFIG_TINYUSB_ENABLED)
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"
#endif
#define COMMAND_DO_NOT_RESTORE_KEYREPORT 0x01
#define COMMAND_ADD_ENTER 0x02
namespace duckscript {

    void runTest();
    void run(String fileName);

   // void nextLine();
   // void repeat();
    void stop();
    void begin();
    bool isRunning();
    String FixPath(String Path);
    String currentScript();
    void Runfile(String fileName);
    uint32_t getUniCode(char *buffer, uint8_t *utf_code_len = 0);
    void  LineCommand();
    void  PointToNextParammeter();
    void  WriteLine(bool ControlCommands = true);
    void LineDelay();
    int toInt(const char *str, size_t len);
    void press(int Unicode);
    void sendReport(KeyReport *k);
    void releaseAll();
    void releaseRaw(uint8_t Key);
    void pressRaw(uint8_t Key);
    void toggelmodifiers(uint8_t Key);
    void ReleaseKeyboardMouse();
    uint8_t mouse_GetButtons(char *strButtons);
    void mouse_move(int8_t x, int8_t y, int8_t wheel = 0, int8_t pan = 0);
    void mouse_absmove(int8_t x, int8_t y, int8_t wheel=0, int8_t pan=0);
    void mouse_click(uint8_t b = MOUSE_LEFT);
    void mouse_release(uint8_t b = MOUSE_LEFT);
    void mouse_press(uint8_t b = MOUSE_LEFT);
};