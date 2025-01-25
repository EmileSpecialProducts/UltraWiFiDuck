/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */
#include <FS.h> // File
#include <LittleFS.h>
#include "config.h"
#include "settings.h"
#include "debug.h"

namespace settings
{
    // ===== PRIVATE ===== //
    typedef struct settings_t
    {

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
        debugln("Initializing Settings....");
        load();
    }

    void load()
    {
        String line;
        debugln("Load");
        reset();
        File f = LittleFS.open(SETTINGSFILENAME,"r");
        if (f)
        {
            debugln("Load OPen File found");    
            while (f.available())
            {
                line = f.readStringUntil('\n');
                debugln("readString:" + line);
                debugln(line.substring(0, line.indexOf("=")));
                debugln(line.substring(line.indexOf("=")+1, line.length()));
                set(line.substring(0, line.indexOf("=")).c_str(), line.substring(line.indexOf("=") + 1, line.length()).c_str());
            }
            debugln(toString());
        }
        else
        {
            debugln("Load File Not found");
            save();
        }
    }

    void reset()
    {
        debugln("Resetting Settings");
        setAPSSID(WIFI_APSSID);
        setAPPassword(WIFI_APPASSWORD);
        setAPChannel(WIFI_CHANNEL);
        setSSID(WIFI_SSID);
        setPassword(WIFI_PASSWORD);
    }

    void save()
    {
        debugln("Saving Settings");
        File f = LittleFS.open(SETTINGSFILENAME,"w",true);
        String s = toString();
        debug("Save Settings" + s);
        f.print(s);
        f.close();
    }

    String toString()
    {
        String s ;
        s = "APssid="
        + String(getAPSSID())
        +"\n" + "APpassword="
        + String(getAPPassword())
        + "\n"+ "channel="
        + String(getAPChannel())
        + "\n"
        + "ssid="
        + String(getSSID())
        + "\n"
        + "password="
        + String(getPassword())
        + "\n"
        + "autorun="
        + String(getAutorun())
        + "\n";
        debug(s);
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
        debugln("Settings::set \"" + String(name) + "\" \"" + String(value) + "\"");
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
            memset(data.ssid, 0, sizeof(data.ssid));
            strncpy(data.ssid, ssid, sizeof(data.ssid) - 1);
        }
    }

    void setPassword(const char *password)
    {
        if (password && ((strlen(password) >= 8)||(strlen(password) == 0)))
        { 
            memset(data.password, 0, sizeof(data.password));
            strncpy(data.password, password, sizeof(data.password) - 1);
        }
    }
    void setAPSSID(const char *ssid)
    {
        if (ssid)
        {
            memset(data.APssid, 0, sizeof(data.APssid));
            strncpy(data.APssid, ssid, sizeof(data.APssid) - 1);
        }
    }

    void setAPPassword(const char *password)
    {
        if (password && ((strlen(password) >= 8)||(strlen(password) == 0)))
        {
            memset(data.APpassword, 0, sizeof(data.APpassword));
            strncpy(data.APpassword, password, sizeof(data.APpassword) - 1);
        }
    }

    void setAPChannel(const char *channel)
    {
        if (channel && ((strcmp(channel, "auto") == 0) || ((atoi(channel) >= 1) && (atoi(channel) <= 13))))
        {
            memset(data.APchannel, 0, 5);
            strncpy(data.APchannel, channel, 4);
        }
    }

    void setAutorun(const char *autorun)
    {
        if (autorun)
        {
            memset(data.autorun, 0, sizeof(data.autorun));
            strncpy(data.autorun, autorun, sizeof(data.autorun) - 1);
        }
    }
}
