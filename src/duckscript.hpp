/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once
#include <Arduino.h> // String
#include "config.h"
#include "debug.h"

#if defined(CONFIG_TINYUSB_ENABLED)
#include "USBHID.h"
#include "USB.h"
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"
#include "USBHIDGamepad.h"
#include "USBHIDConsumerControl.h"
#include "USBHIDSystemControl.h"
#endif

#if defined(CONFIG_SOC_BLE_SUPPORTED)
#include "BleConnectionStatus.h"
#include "BleCompositeHID.h"
#include "KeyboardDevice.h"
#include "MouseDevice.h"
#include <NimBLEDevice.h>
#endif

#include "USB-HID-Types.h"

#include <FS.h> // File
#include <LittleFS.h>
#include "settings.h"

typedef struct UnicodeToKeyCode_t
{
  uint32_t unicode;
  uint8_t RawKeyCodes[4];
} UnicodeToKeyCode_t;

typedef struct Keyboards_t
{
  const char KeyboardName[12];
  const UnicodeToKeyCode_t *KeyboardUniCodes;
} Keyboards_t;

class DuckScript // declared/created using class keyword
{
  private:
  File file;
  
  char Line_Buffer[BUFFER_SIZE + 1];
  char *Line_BufferPtr; // This is the pointer to the current location in the Line_Buffer
  unsigned int defaultDelay = 0;
  unsigned int defaultKeyDelay = 20;   // The delay in ms between key presses
  unsigned int defaultMouseDelay = 20; // The delay in ms between mouse presses
 
  const UnicodeToKeyCode_t *KeyboardUniCodes;
  KeyReport CurrentKeyReport = {0, 0, {0, 0, 0, 0, 0, 0}};
  KeyReport LastSendKeyReport = {0, 0, {0, 0, 0, 0, 0, 0}};
  uint32_t StartoflineTime = 0;
public:
  volatile bool running = false;
  uint32_t running_line = 0; // This will indicat the current line number of the running script
  DuckScript();
  void Test();

  void runTask(char *parameter);
  void run(char *fileName);
  void Runfile(String fileName);
  void stop();
  bool isRunning();
  const UnicodeToKeyCode_t *GetLocalKeyboard(char *BufferPtr);   
  const char* currentScript();
  void WriteLine();
  uint32_t getUniCode(char *buffer, uint8_t *utf_len_return);
  void LineCommand();
  void LineDelay();
  void PointToNextParammeter();
  int toInt(const char *str, size_t len);
  void press(int Unicode);
  void pressRaw(uint8_t Key);
  void releaseRaw(uint8_t Key);
  void toggelmodifiers(uint8_t Key);
  void releaseAll();
  void sendReport(KeyReport *k);
  void pressMedia(uint16_t Media);
  void mouse_move(int8_t x, int8_t y, int8_t wheel, int8_t pan);
  void mouse_absmove(int8_t x, int8_t y, int8_t wheel, int8_t pan);
  uint8_t mouse_GetButtons(char *strButtons);
  void mouse_click(uint8_t b);
  void mouse_release(uint8_t b);
  void mouse_press(uint8_t b);
  void ReleaseKeyboardMouse();
  uint8_t capsLock();
  uint8_t numLock();
};
#if defined (CONFIG_IDF_TARGET_ESP32C3)
// As the ESP32C3 has only 320 KB ram
#define DUCKSCRIPTLEN 5
#else
#define DUCKSCRIPTLEN 5
#endif
extern DuckScript DuckScripts[DUCKSCRIPTLEN];

void duckscript_begin();
void duckscripts_run(char *filename);
void duckscripts_stop(char *filename);
void duckscripts_stopall();



