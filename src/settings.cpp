/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#include "settings.h"

#include "spiffs.h"
#include "debug.h"
#include "config.h"
#include "eeprom0.h"

#define SETTINGS_ADDRES 1
#define SETTINGS_MAGIC_NUM 1234567891

namespace settings
{
    // ===== PRIVATE ===== //
    typedef struct settings_t
    {
        uint32_t magic_num;
        char APssid[33];
        char APpassword[65];
        char APchannel[5];
        char ssid[33];
        char password[65];
        char autorun[65];
    } settings_t;

    settings_t data;

    // ===== PUBLIC ====== //
    void begin()
    {
        eeprom::begin();
        load();
    }

    void load()
    {
        eeprom::getObject(SETTINGS_ADDRES, data);
        if (data.magic_num != SETTINGS_MAGIC_NUM)
            reset();

        if (data.APssid[32] != 0)
            setAPSSID(WIFI_APSSID);
        if (data.APpassword[64] != 0)
            setAPPassword(WIFI_APPASSWORD);
        if (data.ssid[32] != 0)
            setSSID(WIFI_SSID);
        if (data.password[64] != 0)
            setPassword(WIFI_PASSWORD);
        if (data.APchannel[4] != 0)
            setAPChannel(WIFI_CHANNEL);
        if (data.autorun[64] != 0)
            setAutorun("");
    }

    void reset()
    {
        debugln("Resetting Settings");
        data.magic_num = SETTINGS_MAGIC_NUM;

        setAPSSID(WIFI_APSSID);
        setAPPassword(WIFI_APPASSWORD);
        setAPChannel(WIFI_CHANNEL);
        setSSID(WIFI_SSID);
        setPassword(WIFI_PASSWORD);
    }

    void save()
    {
        debugln("Saving Settings");
        eeprom::saveObject(SETTINGS_ADDRES, data);
    }

    String toString()
    {
        String s;
        s += "APssid=";
        s += getAPSSID();
        s += "\n";
        s += "APpassword=";
        s += getAPPassword();
        s += "\n";
        s += "channel=";
        s += getAPChannel();
        s += "\n";
        s += "ssid=";
        s += getSSID();
        s += "\n";
        s += "password=";
        s += getPassword();
        s += "\n";
        s += "autorun=";
        s += getAutorun();
        s += "\n";

        return s;
    }

    const char *getSSID()
    {
        return data.ssid;
    }

    const char *getPassword()
    {
        return data.password;
    }

    const char *getAPSSID()
    {
        return data.APssid;
    }

    const char *getAPPassword()
    {
        return data.APpassword;
    }

    const char *getAPChannel()
    {
        return data.APchannel;
    }

    int getAPChannelNum()
    {
        if (strcmp(data.APchannel, "auto") != 0)
            return atoi(data.APchannel);
        return 1;
    }

    const char *getAutorun()
    {
        return data.autorun;
    }

    void set(const char *name, const char *value)
    {
        if (strcmp(name, "APssid") == 0)
        {
            setAPSSID(value);
        }
        else if (strcmp(name, "APpassword") == 0)
        {
            setAPPassword(value);
        }
        else if (strcmp(name, "ssid") == 0)
        {
            setSSID(value);
        }
        else if (strcmp(name, "password") == 0)
        {
            setPassword(value);
        }
        else if (strcmp(name, "channel") == 0)
        {
            setAPChannel(value);
        }
        else if (strcmp(name, "autorun") == 0)
        {
            setAutorun(value);
        }
    }

    void setSSID(const char *ssid)
    {
        if (ssid)
        {
            memset(data.ssid, 0, 33);
            strncpy(data.ssid, ssid, 32);
            save();
        }
    }

    void setPassword(const char *password)
    {
        if (password && (strlen(password) >= 8))
        {
            memset(data.password, 0, 65);
            strncpy(data.password, password, 64);
            save();
        }
    }
    void setAPSSID(const char *ssid)
    {
        if (ssid)
        {
            memset(data.APssid, 0, 33);
            strncpy(data.APssid, ssid, 32);
            save();
        }
    }

    void setAPPassword(const char *password)
    {
        if (password && (strlen(password) >= 8))
        {
            memset(data.APpassword, 0, 65);
            strncpy(data.APpassword, password, 64);
            save();
        }
    }

    void setAPChannel(const char *channel)
    {
        if (channel && ((strcmp(channel, "auto") == 0) || ((atoi(channel) >= 1) && (atoi(channel) <= 13))))
        {
            memset(data.APchannel, 0, 5);
            strncpy(data.APchannel, channel, 4);
            save();
        }
    }

    void setAutorun(const char *autorun)
    {
        if (autorun)
        {
            memset(data.autorun, 0, 65);
            strncpy(data.autorun, autorun, 64);
            save();
        }
    }
}