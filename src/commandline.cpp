#include "Arduino.h"
#include "debug.h"
#include "duckscript.hpp"
#include "settings.h"

bool getArgument(char *Command, int i, char *buffer , int bufferlen,bool addslashes=false) 
{
    int index = 0;
    bool quote=false;
    //debugf("GetArg %s, %d\n",Command,i);    
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
                        if(*Command =='\"') {    
                            quote=!quote;
                        } else {
                            if(addslashes) {*buffer='/';bufferlen--;buffer++;addslashes=false;}
                            *buffer = *Command;
                            buffer++;
                        }
                        Command++; 
                        bufferlen--; 
                    }
                }
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

String listDir(String dirName)
{
    String res="";
    bool first = true;
    res.reserve(255);
    if (!dirName.startsWith("/"))dirName= "/" + dirName;
    File root = LittleFS.open(dirName);
    File file = root.openNextFile();
    while (file)
    {
        if(!first) res+="\n";    
        first=false;
        res += "\""+String(file.name()) + "\" " + String(file.size()) ;
        file = root.openNextFile();
    }
    if (res.length() == 0)
        res += "\n";
    root.close();
    return res;
}

void Commandline(char * Command, char *buffer, int buffer_len )
{
    char commandbuffer[32];
    buffer[0] = 0;
    memset(commandbuffer, 0, sizeof(commandbuffer));
    debugln("Command: [" + String(Command) + "] ");
    getArgument(Command, 0, commandbuffer, sizeof(commandbuffer));
    //debugln("commandbuffer [" + String(commandbuffer) + "] ");
    if (strncmp(commandbuffer, "status", 6) == 0)
    {
        bool Ready = true;
        //debugln("Status");
        for (DuckScript duckscript : DuckScripts)
        {
            if (duckscript.isRunning())
            {
                if(!Ready)snprintf(buffer+strlen(buffer),buffer_len-strlen(buffer),"\n");
                Ready = false;
                snprintf(buffer+strlen(buffer),buffer_len-strlen(buffer),"running \"%s\" %d",duckscript.currentScript(),duckscript.running_line);
            }
        }
        if (Ready == true)
        {
            snprintf(buffer,buffer_len,"Ultra WifiDuck -- Ready");
        }
    } 
    else if (strncmp(commandbuffer, "settings", 8) == 0) 
    {
        settings::load();
        snprintf(buffer,buffer_len,"%s",settings::toString().c_str());
    }
    else if (strncmp(commandbuffer, "ram", 3) == 0) 
    {   // Prints number of free bytes in the RAM
        snprintf(buffer,buffer_len,"%d bytes available\n%d byte free heap_size\n%d byte free internal_heap_size\n%d byte ArduinoLoopTaskStackSize\n%d byte getSketchSize",
            ESP.getFreeHeap(),
            esp_get_free_heap_size(),
            esp_get_free_internal_heap_size(),
            getArduinoLoopTaskStackSize(),
            ESP.getSketchSize()
        );
    }
    else if (strncmp(commandbuffer, "version", 7) == 0) 
    {   // * Prints the current version number
#ifdef ENABLE_DEBUG
        bool debug_enable= true;
#else
        bool debug_enable= false;
#endif
        snprintf(buffer,buffer_len,"Version " VERSION " " __DATE__ " " __TIME__ " " _TARGET_ESP_ "\n"
        "esp_idf_version: %d.%d.%d\n"
        "arduino_version:  %d.%d.%d\n"
        "%s"
        "Temperature %3.1f °C",    
        ESP_IDF_VERSION_MAJOR,ESP_IDF_VERSION_MINOR,ESP_IDF_VERSION_PATCH,    
        ESP_ARDUINO_VERSION_MAJOR,ESP_ARDUINO_VERSION_MINOR,ESP_ARDUINO_VERSION_PATCH,
        debug_enable?"Debug Enabled\n":"",
        temperatureRead()// internal TemperatureSensor
        );    
    }
    else if (strncmp(commandbuffer, "set", 3) == 0)
    {
        char name[32];
        char value[64];
        getArgument(Command, 1, name, sizeof(name));
        getArgument(Command, 2, value, sizeof(value));
        //*buffer = "Arg[1] " + String(getArgument(Command, 1,name,sizeof(name))) + " Arg[2] " + String(getArgument(Command, 2,value,sizeof(value)));
        snprintf(buffer,buffer_len,"> set \"%s\" to \"%s\"",name, value);
        settings::set(name, value);
        settings::save();
    }
    else if (strncmp(commandbuffer, "reset", 5) == 0)
    {
        settings::reset();
        settings::save();
        snprintf(buffer,buffer_len,"%s",settings::toString().c_str());
    }
    else if (strncmp(commandbuffer, "reboot", 5) == 0)
    {
        ESP.restart();
    }
    else if (strncmp(commandbuffer, "ls", 2) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value),true);
        // debugf("LS value [%s]\n", value);
        snprintf(buffer,buffer_len,"%s",listDir(String(value)).c_str());
    }
    else if (strncmp(commandbuffer, "mem", 3) == 0)
    {
        snprintf(buffer,buffer_len,"%d byte LittleFS\n%d byte used LittleFS\n%d byte free LittleFS",
            LittleFS.totalBytes(),
            LittleFS.usedBytes(),
            LittleFS.totalBytes() - LittleFS.usedBytes()
        );    
    }
    else if (strncmp(commandbuffer, "cat", 3) == 0)
    {   // this will not work for big files > 2K
        char value[64];
        getArgument(Command, 1, value, sizeof(value),true);
        if (LittleFS.exists(value))
        {
            debugln("File found");
            File f = LittleFS.open(value);
            int i=0;
            buffer[0]=0;
            while(f && f.available() && i<(buffer_len-1))
            {
                buffer[i++] = f.read();
                buffer[i]=0;
            }
            if(f && f.available())
            {
                DEBUG_PORT.write(buffer);
                while(f && f.available())
                {
                    DEBUG_PORT.write(f.read());
                }
                snprintf(buffer,buffer_len,"File To big to Cat Output so on Serial port ony");
                debugln("File is big");
            } 
            f.close();
        } else
        {
            debugln("File Not found");
            snprintf(buffer,buffer_len,"File not found");
        }
    }
    else if (strncmp(commandbuffer, "run", 3) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value),true);
        duckscripts_run(value);
        snprintf(buffer,buffer_len,"> started \"%s\"",value);
    }
    else if (strncmp(commandbuffer, "stopall", 7) == 0)
    {
        duckscripts_stopall();
        snprintf(buffer,buffer_len,"> stoppedall");
    }
    else if (strncmp(commandbuffer, "stop", 4) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value),true);
        duckscripts_stop(value);
        snprintf(buffer,buffer_len,"> stopped \"%s\"",value);
    }
    else if (strncmp(commandbuffer, "create", 6) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value),true);
        File f=LittleFS.open(value,"w");
        f.close();
        snprintf(buffer,buffer_len,"> Created file \"%s\"",value);
    }
    else if (strncmp(commandbuffer, "remove", 6) == 0)
    {
        char value[64];
        getArgument(Command, 1, value, sizeof(value),true);
        LittleFS.remove(value);
        snprintf(buffer,buffer_len,"> removed file \"%s\"",value);
    }
    else if (strncmp(commandbuffer, "rename", 6) == 0)
    {
        char value[64];
        char value2[64];
        getArgument(Command, 1, value, sizeof(value),true);
        getArgument(Command, 2, value2, sizeof(value2),true);

        LittleFS.rename(value, value2);
        snprintf(buffer,buffer_len,"> renamed \"%s\" to \"%s\"",value,value2);
    }
    else if (strncmp(commandbuffer, "format", 6) == 0)
    {
        bool FormatStatus = LittleFS.format();
        snprintf(buffer,buffer_len,"Formatted LittleFS %s",FormatStatus?"OK":"FAILED");
    }
    else if (strncmp(commandbuffer, "?", 1) == 0 || strncmp(commandbuffer, "help", 4) == 0)
    {
        snprintf(buffer,buffer_len,"status\nsettings\nram\ncat\nls\nmem\ncat\nrun\nstopall\nstop\ncreate\nremove\nrename\nformat");
    }
    else
    {
        snprintf(buffer,buffer_len,"Unknown Command");
    }
    debugln(buffer);
}
