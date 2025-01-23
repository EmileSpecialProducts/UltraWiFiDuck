/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#include <Arduino.h> // String

namespace settings
{
  void begin();
  void load();

  void reset();
  void save();

  String toString();

  const char *getAPSSID();
  const char *getAPPassword();
  const char *getAPChannel();
  const char *getSSID();
  const char *getPassword();
  const char *getAutorun();

  int getAPChannelNum();

  void set(const char *name, const char *value);

  void setAPSSID(const char *ssid);
  void setAPPassword(const char *password);
  void setSSID(const char *ssid);
  void setPassword(const char *password);
  void setAPChannel(const char *channel);
  void setAutorun(const char *autorun);
}