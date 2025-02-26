/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */
#include <Arduino.h>
#include "config.h"
#include "debug.h"

#include <FS.h> // File
#include <LittleFS.h>
#include "duckscript.h"

#if defined(CONFIG_TINYUSB_ENABLED)
#include "USBHID.h"
#include "USB.h"
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"
USBHIDMouse UsbMouse;
USBHIDKeyboard UsbKeyboard;
USBHID hid;
#endif

#if defined(CONFIG_BT_BLE_ENABLED)
BleComboKeyboard BleKeyboard;
BleComboMouse BleMouse(&BleKeyboard);
#endif

#include "led.h"
#include "Local_KeyBoard.h"
    namespace duckscript {

    File file;
    bool running = false ;
    uint32_t running_line = 0; // This will indicat the current line number of the running script
    char Line_Buffer[BUFFER_SIZE + 1];
    char *Line_BufferPtr; // This is the pointer to the current location in the Line_Buffer
    unsigned int defaultDelay=0;
    unsigned int defaultKeyDelay = 20; // The delay in ms between key presses
    unsigned int defaultMouseDelay = 20; // The delay in ms between mouse presses 

    UnicodeToKeyCode_t *KeyboardUniCodes = Keyboard_US; // Keyboard_NONE; // Keyboard_US
    KeyReport CurrentKeyReport = {0, 0, {0, 0, 0, 0, 0, 0}};
    KeyReport LastSendKeyReport = {0, 0, {0, 0, 0, 0, 0, 0}};
    uint32_t StartoflineTime =0;
    void begin()
    {
#if defined(CONFIG_TINYUSB_ENABLED)
        USB.productName((CUSTOM_USB_PRODUCT" USB"));
        USB.VID(CUSTOM_USB_VID);
        USB.PID(CUSTOM_USB_PID);
        USB.manufacturerName(CUSTOM_USB_MANUFACTURER);
        USB.begin();
        UsbKeyboard.begin();
        UsbMouse.begin();
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
        BleKeyboard.deviceManufacturer = (CUSTOM_USB_MANUFACTURER);
        BleKeyboard.deviceName = (CUSTOM_USB_PRODUCT " BLE");
        BleKeyboard.begin();
        BleMouse.begin();
#endif
    }

    static void runTask(void *parameter)
    {
        String* fileNamePtr = (String*) parameter;
        String fileName = *fileNamePtr;
        delete fileNamePtr;  // Free the heap memory
        Runfile(fileName);
        vTaskDelete(NULL);  // Delete this task when done
    }

    void run(String fileName) {
        // Create a heap copy of fileName
        String* fileNamePtr = new String(fileName);

        // Create a new task
        xTaskCreate(
                runTask,               // Function that should be executed
                "runDuckScriptTask",   // Name of the task
                4096*2,                  // Stack size in words
                fileNamePtr,           // Parameter to pass to the task
                1,                     // Priority
                NULL                   // Task handle
        );
    }

    void Runfile( String fileName) {

        unsigned int Line_Buffer_i = 0;
        bool eol = false; // End of line
        KeyReport StartKeyReport;
        bool RestoreModifiers = true;
        running_line = 0;
        memset(&CurrentKeyReport, 0, sizeof(CurrentKeyReport));
        if (fileName.length() > 0)
        {
            debugf("Run file %s\n", fileName.c_str());
            file = LittleFS.open(FixPath(fileName));
            running = true;
        } else 
        {
            return;
        }
        while (running)
        {
            if (!file) {
                debugln("File error");
                stop();
                return;
            }

            if (!file.available()) {
                debugln("Reached end of file");
                stop();
                return;
            }
            Line_Buffer_i = 0;
            eol = false; // End of line

            StartKeyReport=CurrentKeyReport;
            StartoflineTime = millis();
            memset(Line_Buffer, 0, BUFFER_SIZE);
            // Read a utf8 line into the buffer https://www.fileformat.info/info/unicode/utf8.htm
            while (file.available() && !eol && Line_Buffer_i < BUFFER_SIZE)
            {
                if ('\n' == (Line_Buffer[Line_Buffer_i] = file.read()))
                {
                    eol=true;
                    Line_Buffer[Line_Buffer_i] = 0;
                } else
                {
                    ++Line_Buffer_i;
                }
            }
            running_line ++;
            Line_BufferPtr = Line_Buffer;
#ifdef ENABLE_DEBUG
            debug("Line:[");
            for (int f = 0; f < Line_Buffer_i; f++)
                if (Line_Buffer[f] >= ' ')
                    debug(Line_Buffer[f]);
                    else
                    debug('.');
            debug("][");
            for (int f = 0; f < Line_Buffer_i; f++)
                debugf("%02x ", Line_Buffer[f]);
            debug("]...\n");
#endif
            LineCommand();
        }
        if (file)
            file.close();
        ReleaseKeyboardMouse();
        debugln("End of Script");
    }

    void stop() {
        if (running)
        {
            debugf("Stop Script [%s] at  Line = %d \n", FixPath(file.name()).c_str(),running_line);
            running = false;
        }
        else
            debugf("Script was already Stoped\n");
        if (file)
            file.close();
        ReleaseKeyboardMouse();
    }

    bool isRunning() {
        return running;
    }
    String FixPath( String Path)
    {
        if (Path.startsWith("/"))
            return (Path);
        return ("/"+Path);
    }
    String currentScript() {
        if (!running) return String("");
        return FixPath(file.name()) + " Line = " + String(running_line);
    }

    struct KeyCommands
     {  
        char StrCommand[15];
        uint8_t RawKeycode;
     } KeyCommands[] =
         {
             {"n", HID_KEY_ENTER},
             {"e", HID_KEY_ESCAPE},
             {"r", HID_KEY_RETURN},
             {"t", HID_KEY_TAB},
             {"b", HID_KEY_BACKSPACE},
             {"F10", HID_KEY_F10},
             {"F11", HID_KEY_F11},
             {"F12", HID_KEY_F12},
             {"F13", HID_KEY_F13},
             {"F14", HID_KEY_F14},
             {"F15", HID_KEY_F15},
             {"F16", HID_KEY_F16},
             {"F17", HID_KEY_F17},
             {"F18", HID_KEY_F18},
             {"F19", HID_KEY_F19},
             {"F20", HID_KEY_F20},
             {"F21", HID_KEY_F21},
             {"F22", HID_KEY_F22},
             {"F23", HID_KEY_F23},
             {"F24", HID_KEY_F24},
             {"F1", HID_KEY_F1}, // first the longer Commands strings
             {"F2", HID_KEY_F2},
             {"F3", HID_KEY_F3},
             {"F4", HID_KEY_F4},
             {"F5", HID_KEY_F5},
             {"F6", HID_KEY_F6},
             {"F7", HID_KEY_F7},
             {"F8", HID_KEY_F8},
             {"F9", HID_KEY_F9},
             {"NUM_0", HID_KEY_KEYPAD_0},
             {"NUM_1", HID_KEY_KEYPAD_1},
             {"NUM_2", HID_KEY_KEYPAD_2},
             {"NUM_3", HID_KEY_KEYPAD_3},
             {"NUM_4", HID_KEY_KEYPAD_4},
             {"NUM_5", HID_KEY_KEYPAD_5},
             {"NUM_6", HID_KEY_KEYPAD_6},
             {"NUM_7", HID_KEY_KEYPAD_7},
             {"NUM_8", HID_KEY_KEYPAD_8},
             {"NUM_9", HID_KEY_KEYPAD_9},
             {"NUM_ASTERIX", HID_KEY_KEYPAD_MULTIPLY},
             {"NUM_ENTER", HID_KEY_KEYPAD_ENTER},
             {"NUM_MINUS", HID_KEY_KEYPAD_SUBTRACT},
             {"NUM_DOT", HID_KEY_KEYPAD_DECIMAL},
             {"NUM_PLUS", HID_KEY_KEYPAD_ADD},
             {"MENU", HID_KEY_MENU},
             {"APP", HID_KEY_MENU},
             {"DELETE", HID_KEY_DELETE},
             {"HOME", HID_KEY_HOME},
             {"ENTER", HID_KEY_ENTER},
             {"INSERT", HID_KEY_INSERT},
             {"PAGEUP", HID_KEY_PAGE_UP},
             {"PAGEDOWN", HID_KEY_PAGE_DOWN},
             {"ARROWUP", HID_KEY_ARROW_UP},
             {"ARROWDOWN", HID_KEY_ARROW_DOWN},
             {"ARROWLEFT", HID_KEY_ARROW_LEFT},
             {"ARROWRIGHT", HID_KEY_ARROW_RIGHT},
             {"ARROW_U", HID_KEY_ARROW_UP},
             {"ARROW_D", HID_KEY_ARROW_DOWN},
             {"ARROW_L", HID_KEY_ARROW_LEFT},
             {"ARROW_R", HID_KEY_ARROW_RIGHT},
             {"TAB", HID_KEY_TAB},
             {"END", HID_KEY_END},
             {"ESC", HID_KEY_ESCAPE},
             {"ESCAPE", HID_KEY_ESCAPE},
             {"SPACE", HID_KEY_SPACE},
             {"PAUSE", HID_KEY_PAUSE},
             {"BREAK", HID_KEY_PAUSE},
             {"CAPSLOCK", HID_KEY_CAPS_LOCK},
             {"NUMLOCK", HID_KEY_NUM_LOCK},
             {"PRINTSCREEN", HID_KEY_PRINT_SCREEN},
             {"SCROLLLOCK", HID_KEY_SCROLL_LOCK},
             {"CONTROLLEFT", HID_KEY_CONTROL_LEFT},
             {"CONTROLRICHT", HID_KEY_CONTROL_RIGHT},
             {"CONTROL", HID_KEY_CONTROL_LEFT},
             {"CTRL", HID_KEY_CONTROL_LEFT},
             {"SHIFTLEFT", HID_KEY_SHIFT_LEFT},
             {"SHIFTRICHT", HID_KEY_SHIFT_RIGHT},
             {"SHIFT", HID_KEY_SHIFT_LEFT},
             {"ALTLEFT", HID_KEY_ALT_LEFT},
             {"ALTRICHT", HID_KEY_ALT_RIGHT},
             {"ALT", HID_KEY_ALT_LEFT},
             {"GUILEFT", HID_KEY_GUI_LEFT},
             {"GUIRICHT", HID_KEY_GUI_RIGHT},
             {"GUI", HID_KEY_GUI_LEFT},
             {"WINDOWSLEFT", HID_KEY_GUI_LEFT},
             {"WINDOWSRICHT", HID_KEY_GUI_RIGHT},
             {"WINDOWS", HID_KEY_GUI_LEFT}};

     struct KeyCommands StartOfLineKeys[]{
         {"CONTROL_LEFT", HID_KEY_CONTROL_LEFT},
         {"CONTROLLEFT", HID_KEY_CONTROL_LEFT},
         {"CONTROL_RICHT", HID_KEY_CONTROL_RIGHT},
         {"CONTROLRICHT", HID_KEY_CONTROL_RIGHT},
         {"CONTROL", HID_KEY_CONTROL_LEFT},
         {"CTRL", HID_KEY_CONTROL_LEFT},
         {"SHIFT_LEFT", HID_KEY_SHIFT_LEFT},
         {"SHIFTLEFT", HID_KEY_SHIFT_LEFT},
         {"SHIFT_RICHT", HID_KEY_SHIFT_RIGHT},
         {"SHIFTRICHT", HID_KEY_SHIFT_RIGHT},
         {"SHIFT", HID_KEY_SHIFT_LEFT},
         {"ALT_LEFT", HID_KEY_ALT_LEFT},
         {"ALTLEFT", HID_KEY_ALT_LEFT},
         {"ALT_RICHT", HID_KEY_ALT_RIGHT},
         {"ALTRICHT", HID_KEY_ALT_RIGHT},
         {"ALT", HID_KEY_ALT_LEFT},
         {"GUI_LEFT", HID_KEY_GUI_LEFT},
         {"GUILEFT", HID_KEY_GUI_LEFT},
         {"GUI_RICHT", HID_KEY_GUI_RIGHT},
         {"GUIRICHT", HID_KEY_GUI_RIGHT},
         {"GUI", HID_KEY_GUI_LEFT},
         {"WINDOWS_LEFT", HID_KEY_GUI_LEFT},
         {"WINDOWSLEFT", HID_KEY_GUI_LEFT},
         {"WINDOWS_RICHT", HID_KEY_GUI_RIGHT},
         {"WINDOWSRICHT", HID_KEY_GUI_RIGHT},
         {"WINDOWS", HID_KEY_GUI_LEFT}};

     void  WriteLine(bool ControlCommands)
     {
         uint32_t utf_code = 0;
         uint8_t utf_code_len = 0;
         while (strlen(Line_BufferPtr))
         {
            debugf("WriteLine[%s]\n", Line_BufferPtr);
            if (*Line_BufferPtr == '\\')
                {
                Line_BufferPtr++;
                if (*Line_BufferPtr == '\\')
                    {
                        press('\\');
                    }
                    else
                    {
                        int commands = 0;
                        for (commands = 0; commands < sizeof(KeyCommands) / sizeof(KeyCommands[0]); commands++)
                        {
                            if (strncmp(Line_BufferPtr, KeyCommands[commands].StrCommand, strlen(KeyCommands[commands].StrCommand)) == 0)
                            {
                                debugf("Found Command : %s\n", KeyCommands[commands].StrCommand);
                                Line_BufferPtr += strlen(KeyCommands[commands].StrCommand);
                                if ((KeyCommands[commands].RawKeycode & 0xf0) == 0xE0) //  a modifier release key
                                    toggelmodifiers(KeyCommands[commands].RawKeycode); // change a modifier release key to releas modifier key
                                else
                                {
                                    pressRaw(KeyCommands[commands].RawKeycode);
                                    releaseRaw(KeyCommands[commands].RawKeycode);
                                }
                                break;
                            }
                        }
                        if (commands == sizeof(KeyCommands) / sizeof(KeyCommands[0]))
                        { // no Command found
                            press('\\');
                        }
                    }
                }
                else  // No in line Key commands
                {
                    utf_code = getUniCode(Line_BufferPtr, &utf_code_len);
                    debugf(" %d len= %d\n", utf_code, utf_code_len);
                    if (utf_code_len == 0) // error in decoding UTF8 so stop the script
                    {
                        running = false;
                        break;
                    }
                    Line_BufferPtr += utf_code_len; // point to the next utf char
                    press(utf_code);
                }
        }
        debugf("End of WriteLine \n");
        return ;
    }

    uint32_t getUniCode(char * buffer, uint8_t *utf_len_return)
    {
        //uint8_t *utf = (uint8_t *)strPtr;
        uint32_t utf_code = 0;
        uint8_t utf_len = 0;
        utf_code = 0;
        if ((buffer[0] & 0x80) == 0x00)
        {
            utf_len = 1;
            utf_code = buffer[0] & 0x7f;
        }
        else
        {
            if (((buffer[0] & 0xE0) == 0xC0) && ((buffer[1] & 0xC0) == 0x80))
            {
                utf_len = 2;
                utf_code = ((buffer[0] & 0x1f) << 6) | (buffer[1] & 0x3f);
            }
            else
            {
                if (((buffer[0] & 0xF0) == 0xE0) && ((buffer[1] & 0xC0) == 0x80) && ((buffer[2] & 0xC0) == 0x80))
                {
                    utf_len = 3;
                    utf_code = ((buffer[0] & 0x0f) << 12) | ((buffer[1] & 0x3f) << 6) | (buffer[2] & 0x3f);
                }
                else
                {
                    if (((buffer[0] & 0xF8) == 0xF0) && ((buffer[1] & 0xC0) == 0x80) && ((buffer[2] & 0xC0) == 0x80) && ((buffer[3] & 0xC0) == 0x80))
                    {
                        utf_len = 4;
                        utf_code = ((buffer[0] & 0x07) << 18) | ((buffer[1] & 0x3f) << 12) | ((buffer[2] & 0x3f) << 6) | (buffer[3] & 0x3f);
                    }
                }
            }
        }
        //debugf("U %4x Len %d\n", *utf_code, utf_len);
        if (utf_len_return) *utf_len_return = utf_len;
        return (utf_code);
    }

    void  LineCommand()
    {
        KeyReport StartKeyReport;
        StartKeyReport = CurrentKeyReport;
        bool add_enter_to_line = true;

        if (strncmp(Line_BufferPtr,"LED ",4)==0)
        {
            int c[3]={0,0,0};
            for (uint8_t i = 0; i < 3; ++i)
            {
                PointToNextParammeter();
                c[i] = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            }
            led::setColor(c[0], c[1], c[2]);
            return;
        } else if (strncmp(Line_BufferPtr, "DEFAULTDELAY ", 13) == 0 || strncmp(Line_BufferPtr, "DEFAULT_DELAY ", 14) == 0)
        {
            PointToNextParammeter();
            defaultDelay = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            return;
        } else if (strncmp(Line_BufferPtr, "KEYDELAY ", 9) == 0 || strncmp(Line_BufferPtr, "KEY_DELAY ", 10) == 0)
        {
            PointToNextParammeter();
            defaultKeyDelay = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            return;
        }
        else if (strncmp(Line_BufferPtr, "MOUSE DELAY ", 12) == 0 || strncmp(Line_BufferPtr, "MOUSE_DELAY ", 12) == 0)
        {
            Line_BufferPtr += 6;
            PointToNextParammeter();
            defaultMouseDelay = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            debugf("defaultMouseDelay = %d\n", defaultMouseDelay);
            return;
        }
        else if (strncmp(Line_BufferPtr, "DELAY ", 6) == 0)
        {
            int time = 0;
            PointToNextParammeter();
            time = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            debugf("Delay Time = %d\n", time );
            uint32_t WaitTime = StartoflineTime + time;
            while (millis() <= WaitTime && running)
            {
                delay(1);
            }
            return;
        }
        else if (strncmp(Line_BufferPtr, "MOUSE CLICK ", 12) == 0)
        {
            uint8_t buttons = 0;
            buttons = mouse_GetButtons(Line_BufferPtr);
            debugf("CLICK Button %02X\n", buttons);
            mouse_click(buttons);
            return;
        }
        else if (strncmp(Line_BufferPtr, "MOUSE PRESS ", 12) == 0)
        {
            uint8_t buttons = 0;
            buttons = mouse_GetButtons(Line_BufferPtr);
            debugf("CLICK Button %02X\n", buttons);
            mouse_press(buttons);
            return;
        }
        else if (strncmp(Line_BufferPtr, "MOUSE RELEASE ", 14) == 0)
        {
            uint8_t buttons = 0;
            buttons = mouse_GetButtons(Line_BufferPtr);
            debugf("CLICK Button %02X\n", buttons);
            mouse_release(buttons);
            return;
        }
        else if (strncmp(Line_BufferPtr, "MOUSE ", 6) == 0)
        {
            int c[4] = {0, 0, 0, 0};
            for (uint8_t i = 0; i < sizeof(c) / sizeof(c[0]); ++i)
            {
                PointToNextParammeter();
                c[i] = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            }
            PointToNextParammeter();
            mouse_move(c[0], c[1], c[2], c[3]);
            return;
        }
        else if (strncmp(Line_BufferPtr, "REM ", 4) == 0)
        {
            // Do nothing
            return;
        } else if (strncmp(Line_BufferPtr, "KEYCODE ", 8) == 0)
        {
            KeyReport k;
            int c[7] = {0, 0, 0,0,0,0,0 };
            for (uint8_t i = 0; i < 7; ++i)
            {
                PointToNextParammeter();
                c[i] = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            }
            k.modifiers = (uint8_t)c[0];
            k.reserved  = 0;
            for (uint8_t i = 0; i<6; ++i) {
                k.keys[i] = c[1 + i];
            }
            CurrentKeyReport = k;
            sendReport(&CurrentKeyReport);
            return;
        }
        else if (strncmp(Line_BufferPtr, "RELEASE ", 8) == 0)
        {
            memset(&CurrentKeyReport, 0, sizeof(CurrentKeyReport));
            return;
        }
        else if (strncmp(Line_BufferPtr, "LOCALE ", 7) == 0)
        {
            PointToNextParammeter();
            for (int Lang = 0; Lang < (sizeof(Local_Keyboards) / sizeof(Local_Keyboards[0])); Lang++)
            {
                debug(Local_Keyboards[Lang].KeyboardName);
                if (strncmp(Local_Keyboards[Lang].KeyboardName, Line_BufferPtr, strlen(Local_Keyboards[Lang].KeyboardName)) == 0)
                {
                    KeyboardUniCodes = Local_Keyboards[Lang].KeyboardUniCodes;
                    debugf("New LOCALE = %s\n", Local_Keyboards[Lang].KeyboardName);
                    break;
                }
            }
            return;
        }
        else if (strncmp(Line_BufferPtr, "STRING ", 7) == 0)
        {
            Line_BufferPtr += 7; // skip the firts space after command;
            add_enter_to_line = false;
        }

        int commands=0;
        char *StartOfLine = Line_BufferPtr;
        if ('\\' == *Line_BufferPtr)
            Line_BufferPtr++;
        for(commands = 0; commands < sizeof(StartOfLineKeys) / sizeof(StartOfLineKeys[0]); commands++)
        {
            if (strncmp(Line_BufferPtr, StartOfLineKeys[commands].StrCommand, strlen(StartOfLineKeys[commands].StrCommand)) == 0)
            {
                char *startoftextline = Line_BufferPtr;
                debugf("Found Command : [%s] ,len=[%d], [%s]\n", StartOfLineKeys[commands].StrCommand, strlen(Line_BufferPtr), Line_BufferPtr);
                Line_BufferPtr += strlen(StartOfLineKeys[commands].StrCommand);
                if (*Line_BufferPtr==' ')Line_BufferPtr++;  // skip the firts space after command;
                    if ((StartOfLineKeys[commands].RawKeycode & 0xf0) == 0xE0) //  a modifier release key
                    {
                        toggelmodifiers(StartOfLineKeys[commands].RawKeycode); // change a modifier release key to releas modifier key
                    }
                    else
                    {
                        pressRaw(StartOfLineKeys[commands].RawKeycode);
                        releaseRaw(StartOfLineKeys[commands].RawKeycode);
                    }
                debugf("Command and string  %d\n", strlen(Line_BufferPtr));    
                if (strlen(Line_BufferPtr) == 0)
                {
                    debug("Restore report false");
                    LineDelay();
                    return;
                }
                add_enter_to_line = false;
                break;
            }
        }  
        if (commands == sizeof(StartOfLineKeys) / sizeof(StartOfLineKeys[0]))
        {
            debugf("No Start of line Command found\n");
            Line_BufferPtr = StartOfLine;
        }
        
        WriteLine();
        if (add_enter_to_line)
        {
            releaseAll();
            press(10);
        }
        CurrentKeyReport = StartKeyReport;
        sendReport(&CurrentKeyReport);
        debugf("Restore KeyReport %02X , %02X %02X %02X %02X %02X %02X \n ", CurrentKeyReport.modifiers, CurrentKeyReport.keys[0], CurrentKeyReport.keys[1], CurrentKeyReport.keys[2], CurrentKeyReport.keys[3], CurrentKeyReport.keys[4], CurrentKeyReport.keys[5]);
        LineDelay();
        return ;
    }

    void LineDelay()
    {
        uint32_t WaitTime = millis() + defaultDelay;
        while (millis() <= WaitTime && running)
        {
            delay(1);
        }
        // debugf("DelayDefault %d", defaultDelay);
        // delay(defaultDelay); /// BUG is running = false; this will not stop the delay.
    }

    void PointToNextParammeter()
    {
        while (*Line_BufferPtr != ' ' && *Line_BufferPtr != '\n' && *Line_BufferPtr != 0)
            Line_BufferPtr++;
        while (*Line_BufferPtr == ' ')
            Line_BufferPtr++;
    }
    int toInt(const char *str, size_t len)
    {
        bool positive = true;
        if (!str || (len == 0))
            return 0;
        if (str[0] == '-')
        {
            positive = false;
            str++;
        }
        int val = 0;
        // HEX
        if ((len > 2) && (str[0] == '0') && (str[1] == 'x'))
        {
            for (size_t i = 2; (i < len) && (str[i] != ' ') && (str[i] != '\n'); ++i)
            {
                uint8_t b = str[i];

                if ((b >= '0') && (b <= '9'))
                    b = b - '0';
                else if ((b >= 'a') && (b <= 'f'))
                    b = b - 'a' + 10;
                else if ((b >= 'A') && (b <= 'F'))
                    b = b - 'A' + 10;

                val = (val << 4) | (b & 0xF);
            }
        }
        // DECIMAL
        else
        {
            for (size_t i = 0; (i < len) && (str[i] != ' ') && (str[i] != '\n'); ++i)
            {
                if(str[0]=='-') positive = false;
                if ((str[i] >= '0') && (str[i] <= '9'))
                {
                    val = val * 10 + (str[i] - '0');
                }
            }
        }
        if(!positive) { val*=-1; str--; }
        //debugf("%d =toInt(%s)\n", val, str);
        return val;
    }

    void press(int Unicode)
    {
        int codes = 0;
        for (codes = 0; KeyboardUniCodes[codes].unicode; codes++)
        {
            if (KeyboardUniCodes[codes].unicode == Unicode)
            {
                bool Releasall = false;
                KeyReport SavedKeyReport = CurrentKeyReport;
                for (int keys = 0; KeyboardUniCodes[codes].RawKeyCodes[keys]; keys++)
                {
                    debugf("[%02x] ", KeyboardUniCodes[codes].RawKeyCodes[keys]);
                    if ((KeyboardUniCodes[codes].RawKeyCodes[keys] & 0xF0) == 0xE0)
                        toggelmodifiers(KeyboardUniCodes[codes].RawKeyCodes[keys]);
                    else 
                    {
                        pressRaw(KeyboardUniCodes[codes].RawKeyCodes[keys]);
                        releaseRaw(KeyboardUniCodes[codes].RawKeyCodes[keys]);
                    }
                }
                CurrentKeyReport = SavedKeyReport;
                debugf("\n");
                break;
            }
            
        }
        if (KeyboardUniCodes[codes].unicode == 0) // The last line in the LOCAL Keyboard_ table
        {   // This will write the UniCode to the Keyboard as ALT+ decimal number
            // But we have to save the CurrentKeyReport
            KeyReport KeyReportSaved=CurrentKeyReport;
            uint8_t Keymask = 0;
            uint8_t n=0;
            uint32_t divider = 10000;
            bool startSending = false;
            debugf("Unicode Not found %d ", Unicode);
            releaseAll();
            while (divider)
            {
                n = Unicode / divider;
                debugf("{%d, %d, %d}", divider, n, Unicode);
                Unicode -= n * divider;
                divider /= 10;
                Keymask = 0;
                if (n > 0 || (Unicode >= 128 && Unicode <= 255 && divider == 100)) // this is needed as between 127 and 255 UniCode and ancii are diffrent. 
                {
                    startSending = true;
                    pressRaw(HID_KEY_ALT_LEFT);
                }
                if (startSending == true)
                {
                    switch (n)
                    {
                    case 0:
                        Keymask = HID_KEY_KEYPAD_0;
                        break;
                    case 1:
                        Keymask = HID_KEY_KEYPAD_1;
                        break;
                    case 2:
                        Keymask = HID_KEY_KEYPAD_2;
                        break;
                    case 3:
                        Keymask = HID_KEY_KEYPAD_3;
                        break;
                    case 4:
                        Keymask = HID_KEY_KEYPAD_4;
                        break;
                    case 5:
                        Keymask = HID_KEY_KEYPAD_5;
                        break;
                    case 6:
                        Keymask = HID_KEY_KEYPAD_6;
                        break;
                    case 7:
                        Keymask = HID_KEY_KEYPAD_7;
                        break;
                    case 8:
                        Keymask = HID_KEY_KEYPAD_8;
                        break;
                    case 9:
                        Keymask = HID_KEY_KEYPAD_9;
                        break;
                    }
                pressRaw(Keymask);
                releaseRaw(Keymask);
                }
            }
            releaseRaw(HID_KEY_ALT_LEFT);
            CurrentKeyReport = KeyReportSaved;
        }
    }

    // Create are own pressRaw releaseRaw as then we can use the CurrentKeyReport
    // and save the status to enter a UniCode
    void pressRaw(uint8_t Key)
    {
        uint8_t i;
        if (Key >= 0xE0 && Key < 0xE8)
        {
            // it's a modifier key
            CurrentKeyReport.modifiers |= (1 << (Key - 0xE0));
        }
        else if (Key && Key < 0xA5)
        {
            // Add Key to the key report only if it's not already present
            // and if there is an empty slot.
            if (CurrentKeyReport.keys[0] != Key && CurrentKeyReport.keys[1] != Key &&
                CurrentKeyReport.keys[2] != Key && CurrentKeyReport.keys[3] != Key &&
                CurrentKeyReport.keys[4] != Key && CurrentKeyReport.keys[5] != Key)
            {
                for (i = 0; i < 6; i++)
                {
                    if (CurrentKeyReport.keys[i] == 0x00)
                    {
                        CurrentKeyReport.keys[i] = Key;
                        break;
                    }
                }
                if (i == 6) return ;
            }
        }
        else
        {   // not a modifier and not a key
            return ;
        }
        sendReport(&CurrentKeyReport);
    }


    void releaseRaw(uint8_t Key)
    {
        uint8_t i;
        if (Key >= 0xE0 && Key < 0xE8)
        {
            // it's a modifier key
            CurrentKeyReport.modifiers &= ~(1 << (Key - 0xE0));
        }
        else if (Key && Key < 0xA5)
        {
            // Test the key report to see if k is present.  Clear it if it exists.
            // Check all positions in case the key is present more than once (which it shouldn't be)
            for (i = 0; i < 6; i++)
            {
                if (0 != Key && CurrentKeyReport.keys[i] == Key)
                {
                    CurrentKeyReport.keys[i] = 0x00;
                }
            }
        }
        else
        {
            // not a modifier and not a key
            return ;
        }
        sendReport(&CurrentKeyReport);
        return ;
    }

    void toggelmodifiers(uint8_t Key)
    {
        uint8_t i;
        if (Key >= 0xE0 && Key < 0xE8)
        {
            // it's a toggelmodifier key
            CurrentKeyReport.modifiers ^= (1 << (Key - 0xE0));
        }
        sendReport(&CurrentKeyReport);
    }

    void releaseAll()
    {
        KeyReport releaseAllKeyReport = {0, 0, {0, 0, 0, 0, 0, 0}};
        CurrentKeyReport = releaseAllKeyReport;
        sendReport(&CurrentKeyReport);
    }

    void sendReport(KeyReport *k)
    {
        if (memcmp(k, &LastSendKeyReport, sizeof(KeyReport)) == 0) // do not send the KeyReport when it is the same as the last one sent and do not wait.
        {
            debugf("Not sendReport:%02x = %02x %02x %02x %02x %02x %02x\n", LastSendKeyReport.modifiers, LastSendKeyReport.keys[0], LastSendKeyReport.keys[1], LastSendKeyReport.keys[2], LastSendKeyReport.keys[3], LastSendKeyReport.keys[4], LastSendKeyReport.keys[5]);
        }
        else
        {
            LastSendKeyReport = *k;
            if (running)
            {
                uint32_t WaitTime = millis() + defaultKeyDelay;
                debugf("sendReport:%02x = %02x %02x %02x %02x %02x %02x\n", LastSendKeyReport.modifiers, LastSendKeyReport.keys[0], LastSendKeyReport.keys[1], LastSendKeyReport.keys[2], LastSendKeyReport.keys[3], LastSendKeyReport.keys[4], LastSendKeyReport.keys[5]);
        #if defined(CONFIG_TINYUSB_ENABLED)
                if(hid.ready())          // will need to created a bug report on this as we get an error in the Errorlog "SendReport(): not ready When the USB is not connected"           
                    UsbKeyboard.sendReport(k);
        #endif
        #if defined(CONFIG_BT_BLE_ENABLED)
                if (BleKeyboard.isConnected())
                {
                    BleKeyboard.sendReport(k);
                }
                else
                {
                    debugln("No BLE connection");
                }
        #endif            
                while (millis() <= WaitTime && running)
                {
                    delay(1);
                }
            }
        }
    }


    void mouse_move(int8_t x, int8_t y, int8_t wheel, int8_t pan)
    {
        if (running)
        {
            uint32_t WaitTime = millis() + defaultMouseDelay;
        #if defined(CONFIG_TINYUSB_ENABLED)
            if (hid.ready())
                UsbMouse.move(x, y, wheel, pan);
        #endif
        #if defined(CONFIG_BT_BLE_ENABLED)
            if (BleKeyboard.isConnected())
                BleMouse.move(x, y, wheel, pan);
        #endif
            while (millis() <= WaitTime && running)
            {
                delay(1);
            }
        }
    }
    void mouse_absmove(int8_t x, int8_t y, int8_t wheel, int8_t pan)
    {
        if (running)
        {
    #if defined(CONFIG_TINYUSB_ENABLED)
        if(hid.ready())
            UsbMouse.move(x, y, wheel, pan);
    #endif
    #if defined(CONFIG_BT_BLE_ENABLED)
        if (BleKeyboard.isConnected())
            BleMouse.move(x, y, wheel, pan);
    #endif
        }
    }
    uint8_t mouse_GetButtons(char *strButtons)
    {
        uint8_t Buttons = 0;
        String Buttonline = String(strButtons); 
        if (Buttonline.indexOf("LEFT") > 0) Buttons |= MOUSE_LEFT;
        if (Buttonline.indexOf("RIGHT") > 0) Buttons |= MOUSE_RIGHT;
        if (Buttonline.indexOf("MIDDLE") > 0) Buttons |= MOUSE_MIDDLE;
        if (Buttonline.indexOf("BACKWARD") > 0) Buttons |= MOUSE_BACKWARD;
        if (Buttonline.indexOf("FORWARD") > 0) Buttons |= MOUSE_FORWARD;
        if (Buttonline.indexOf("ALL") > 0)  Buttons |= (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_BACKWARD | MOUSE_FORWARD);
        return Buttons;
    } 
    void mouse_click(uint8_t b)
    {
        if (running)
        {
            uint32_t WaitTime = millis() + defaultMouseDelay;
        #if defined(CONFIG_TINYUSB_ENABLED)
                    if (hid.ready())
                        UsbMouse.click(b);
        #endif
        #if defined(CONFIG_BT_BLE_ENABLED)
            if (BleKeyboard.isConnected())
                BleMouse.click(b);
        #endif
            while (millis() <= WaitTime && running)
            {
                delay(1);
            }
        }
    }
    void mouse_release(uint8_t b)
    {
        if (running)
        {
            uint32_t WaitTime = millis() + defaultMouseDelay;
        #if defined(CONFIG_TINYUSB_ENABLED)
            if (hid.ready())
                UsbMouse.release(b);
        #endif
        #if defined(CONFIG_BT_BLE_ENABLED)
                if (BleKeyboard.isConnected())
                    BleMouse.release(b);
        #endif
            while (millis() <= WaitTime && running)
            {
                delay(1);
            }
        }
    }
    void mouse_press(uint8_t b)
    {
        if (running)
        {
            uint32_t WaitTime = millis() + defaultMouseDelay;
        #if defined(CONFIG_TINYUSB_ENABLED)
                if (hid.ready())
                    UsbMouse.press(b);
        #endif
        #if defined(CONFIG_BT_BLE_ENABLED)
                if (BleKeyboard.isConnected())
                    BleMouse.press(b);
        #endif
                while (millis() <= WaitTime && running)
                {
                    delay(1);
                }
        }
    }
    void ReleaseKeyboardMouse()
    {
        #if defined(CONFIG_TINYUSB_ENABLED)
        if (hid.ready())
            UsbKeyboard.releaseAll();
        #endif
        #if defined(CONFIG_BT_BLE_ENABLED)
        BleKeyboard.releaseAll();
        BleMouse.release(MOUSE_ALL);
        #endif
    }
}