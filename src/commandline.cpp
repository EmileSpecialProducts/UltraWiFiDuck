#include "Arduino.h"
#include "debug.h"
#include "duckscript.hpp"
#include "settings.h"

bool getArgument(char *Command, int i, char *buffer , int bufferlen )
{
    int index = 0;
    bool quote=false;
    debugf("GetArg %s, %d\n",Command,i);    
    memset(buffer, 0, bufferlen);
    while (*Command)
    {
        while (*Command == ' ') { Command++; bufferlen--; }
        if(index==i)
        {
            while ((*Command != ' ' || quote==true) && *Command != 0)
                {
                    if (bufferlen > 1)
                    {
                        debug(*Command);

                        if(*Command =='\"') 
                        {    
                            quote=!quote;
                            debug('#');
                        }
                        else
                        {
                            *buffer = *Command;
                            buffer++;
                        }
                        Command++; 
                        bufferlen--; 
                    }
                }
            debugln(buffer);
            return true;
        }
        index++;
        while ((*Command != ' ' || quote==true) && *Command !=0)
        {  
            if(*Command =='\"') 
                quote=!quote;
            Command++;
        }
    } 
    return false;
}

void fixPath(String &path)
{
    path.replace("\"", "");
    if (!path.startsWith("/"))
    {
        path = "/" + path;
    }
}

String listDir(String dirName)
{
    String res="";
    res.reserve(255);
    fixPath(dirName);
        File root = LittleFS.open(dirName);
        File file = root.openNextFile();
        while (file)
        {
            res += "\""+String(file.name()) + "\" " + String(file.size()) +"\n";
            file = root.openNextFile();
        }
        if (res.length() == 0)
            res += "\n";
        root.close();
    return res;
}

void Commandline(char * Command, String *buffer)
{
    char commandbuffer[32];
    *buffer = "";
    memset(commandbuffer, 0, sizeof(commandbuffer));
    debugln("Commandline [" + String(Command) + "]");
    getArgument(Command, 0, commandbuffer, sizeof(commandbuffer));
    debugln("commandbuffer [" + String(commandbuffer) + "]");
    if (strncmp(commandbuffer, "status", 6) == 0)
    {
        bool Ready = true;
        debugln("Status");
        for (DuckScript duckscript : DuckScripts)
        {
            if (duckscript.running)
            {
                Ready = false;
                *buffer += "running \""+duckscript.currentScript() + "\" " + duckscript.running_line + "\n";
            }
        }
        if (Ready == true)
        {
            debugln("No Running Tasks");
            *buffer = "Ultra WifiDuck -- Ready";
        }
        debug(*buffer);
    } else if (strncmp(commandbuffer, "settings", 8) == 0) 
    {
        settings::load();
        *buffer=settings::toString();
        debugln("settings:\n" + *buffer);
    }
    else if (strncmp(commandbuffer, "ram", 3) == 0) // Prints number of free bytes in the RAM
    {
        *buffer = String(ESP.getFreeHeap()) + " bytes available\n"
         + String(esp_get_free_heap_size())
         + " byte free heap_size\n"
         + String(esp_get_free_internal_heap_size())
         + " byte free internal_heap_size\n"
         + String(getArduinoLoopTaskStackSize())
         + " byte ArduinoLoopTaskStackSize\n"
         + String(ESP.getSketchSize())
         + " byte getSketchSize\n"
         ;
    }
    else if (strncmp(commandbuffer, "version", 7) == 0) // * Prints the current version number
    {
        *buffer = "Version " + String(VERSION) + " " + String(__DATE__ " " __TIME__ " ");
        #if defined (CONFIG_IDF_TARGET_ESP32S3)
        *buffer+="ESP-S3";
        #elif defined (CONFIG_IDF_TARGET_ESP32S2)
        *buffer+="ESP-S2";
        #elif defined (CONFIG_IDF_TARGET_ESP32C3)
        *buffer+="ESP-C3";
        #elif defined (CONFIG_IDF_TARGET_ESP32C6)
        *buffer+="ESP-C6";
        #elif defined (CONFIG_IDF_TARGET_ESP32)
        *buffer+="ESP-CLASIC";
        #endif
        *buffer+="\nesp_idf_version: " +String(ESP_IDF_VERSION_MAJOR) +"."+String(ESP_IDF_VERSION_MINOR)+"."+(ESP_IDF_VERSION_PATCH);
        *buffer+="\narduino_version: " +String(ESP_ARDUINO_VERSION_MAJOR)+"."+String(ESP_ARDUINO_VERSION_MINOR)+"."+String(ESP_ARDUINO_VERSION_PATCH);
#ifdef ENABLE_DEBUG
        *buffer+="\nDebug Enabled";
#endif
        *buffer+="\nTemperature: " + String(temperatureRead()) + " °C "; // internal TemperatureSensor
    }
    else if (strncmp(commandbuffer, "set", 3) == 0)
    {
        char name[32];
        char value[64];
        getArgument(Command, 1, name, sizeof(name));
        getArgument(Command, 2, value, sizeof(value));
        //*buffer = "Arg[1] " + String(getArgument(Command, 1,name,sizeof(name))) + " Arg[2] " + String(getArgument(Command, 2,value,sizeof(value)));
        *buffer = "> set \"" + String(name) + "\" to \"" + String(value) + "\"";
        settings::set(name, value);
        settings::save();
    }
    else if (strncmp(commandbuffer, "reset", 5) == 0)
    {
        settings::reset();
        settings::save();
        *buffer=settings::toString();
    }
    else if (strncmp(commandbuffer, "reboot", 5) == 0)
    {
        ESP.restart();
    }
    else if (strncmp(commandbuffer, "ls", 2) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value));
        debugf("LS value [%s]\n", value);
        debugf("commandbuffer [%s]\n", commandbuffer);
        *buffer = listDir(String(value));
    }
    else if (strncmp(commandbuffer, "mem", 3) == 0)
    {
        *buffer = String(LittleFS.totalBytes())
         + " byte LittleFS\n"
         + String(LittleFS.usedBytes())
         + " byte used LittleFS\n"
         + String(LittleFS.totalBytes() - LittleFS.usedBytes())
         + " byte free LittleFS\n";
    }
    else if (strncmp(commandbuffer, "cat", 3) == 0)
    {   // this will not work for big files > 2K
        char value[64];
        getArgument(Command, 1, value, sizeof(value));
        String filename=String(value);
        fixPath(filename);
        debugln(filename);
 
        File f = LittleFS.open(filename);

        int buf_size{2048};
        char filebuffer[buf_size];

        if (f && f.available())
        {
            for (size_t i = 0; i < buf_size; ++i)
            {
                if (!f.available() || (i == buf_size - 1))
                {
                    filebuffer[i] = '\0';
                    i = buf_size;
                }
                else
                {
                    filebuffer[i] = f.read();
                }
            }
            *buffer=filebuffer;
            f.close();
        }
    }
    else if (strncmp(commandbuffer, "run", 3) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value));
        duckscripts_run(value);
        *buffer = "> started \"" + String(value) + "\"";
    }
    else if (strncmp(commandbuffer, "stopall", 7) == 0)
    {
        duckscripts_stopall();
        *buffer = "> stoppedall";
    }
    else if (strncmp(commandbuffer, "stop", 4) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value));
        duckscripts_stop(value);
        *buffer = "> stopped \"" + String(value) + "\"";
    }
    else if (strncmp(commandbuffer, "create", 6) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value));
        String filename=String(value);
        fixPath(filename);
        debugln(filename);
        File f=LittleFS.open(filename,"w");
        f.close();
        *buffer = "> Created file \"" + filename + "\"";
    }
    else if (strncmp(commandbuffer, "remove", 6) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value));
        String filename=String(value);
        fixPath(filename);
        debugln(filename);
        LittleFS.remove(filename);
        *buffer = "> removed file \"" + filename + "\"";
    }
    else if (strncmp(commandbuffer, "rename", 6) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value));
        char value2[64];
        getArgument(Command, 2, value2, sizeof(value2));
        String fileold = String(value);
        String filenew = String(value2);
        fixPath(fileold);
        fixPath(filenew);
        LittleFS.rename(fileold, filenew);
        *buffer = "> renamed \"" + fileold + "\" to \"" + filenew + "\"";
    }
    else if (strncmp(commandbuffer, "format", 6) == 0)
    {
        bool FormatStatus = LittleFS.format();
        *buffer = "Formatted LittleFS ";
        if (FormatStatus)
            *buffer += "OK";
        else
            *buffer += "FAILED";
    }
    else
    {
        *buffer += "Unknown Command";
    }
}
