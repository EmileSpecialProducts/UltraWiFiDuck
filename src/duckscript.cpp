/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#include "duckscript.hpp"

#if defined(CONFIG_TINYUSB_ENABLED)

USBHIDMouse UsbMouse;
USBHIDKeyboard UsbKeyboard;
USBHIDGamepad UsbGamepad;
USBHIDConsumerControl UsbConsumerControl; 
USBHIDSystemControl UsbSystemControl;
USBHID hid;
#endif

#if defined(CONFIG_BT_BLE_ENABLED)


BLEHostConfiguration bleHostConfig; 
KeyboardDevice* bleKeyboard;
MouseDevice* bleMouse;
BleCompositeHID compositeHID((CUSTOM_USB_PRODUCT " BLE"), (CUSTOM_USB_MANUFACTURER), 100); 
#endif

#include "led.h"
#include "Local_KeyBoard.h"

struct KeyCommand
{
    char StrCommand[15];
    uint8_t RawKeycode;
};

const KeyCommand KeyCommands[] =
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
    {"WINDOWS", HID_KEY_GUI_LEFT}
};

struct Control_Command
{
    char StrCommand[15];
    uint16_t RawKeycode;
};

const Control_Command Control_Commands[] =
{
    {"OSPOWER",CONSUMER_CONTROL_POWER},// Not working on Windows 
    {"OSSLEEP",CONSUMER_CONTROL_SLEEP},// Not working on Windows 
    {"MUTE",CONSUMER_CONTROL_MUTE},
    {"VOLUMEUP",CONSUMER_CONTROL_VOLUME_INCREMENT},
    {"VOLUMEDOWN",CONSUMER_CONTROL_VOLUME_DECREMENT},
    {"VOLUME+",CONSUMER_CONTROL_VOLUME_INCREMENT},
    {"VOLUME-",CONSUMER_CONTROL_VOLUME_DECREMENT},
    {"CALC",CONSUMER_CONTROL_CALCULATOR},
    {"BRIGHT+",CONSUMER_CONTROL_BRIGHTNESS_INCREMENT},
    {"BRIGHT-",CONSUMER_CONTROL_BRIGHTNESS_DECREMENT},
    {"WWW",CONSUMER_CONTROL_HOME}        
};

const Control_Command System_Commands[] =
{
    {"POWER",SYSTEM_CONTROL_POWER_OFF},    
    {"SLEEP",SYSTEM_CONTROL_STANDBY },     
    {"WAKE" ,SYSTEM_CONTROL_WAKE_HOST}    
};

/*
const uint16_t bltControl_Commands[] =
{ // the Control Commands keys are defined in the BleComboKeyboard.cpp file.
    CONSUMER_CONTROL_SCAN_NEXT,             //   USAGE (Scan Next Track)     ; bit 0: 1
    CONSUMER_CONTROL_SCAN_PREVIOUS ,        //   USAGE (Scan Previous Track) ; bit 1: 2
    CONSUMER_CONTROL_STOP ,                 //   USAGE (Stop)                ; bit 2: 4
    CONSUMER_CONTROL_PLAY_PAUSE ,           //   USAGE (Play/Pause)          ; bit 3: 8
    CONSUMER_CONTROL_MUTE,                  //   USAGE (Mute)                ; bit 4: 16
    CONSUMER_CONTROL_VOLUME_INCREMENT,      //   USAGE (Volume Increment)    ; bit 5: 32
    CONSUMER_CONTROL_VOLUME_DECREMENT,      //   USAGE (Volume Decrement)    ; bit 6: 64
    CONSUMER_CONTROL_HOME,                  //   Usage (WWW Home)            ; bit 7: 128
    CONSUMER_CONTROL_LOCAL_BROWSER,         //   Usage (My Computer) ; bit 0: 1
    CONSUMER_CONTROL_CALCULATOR,            //   Usage (Calculator)  ; bit 1: 2
    CONSUMER_CONTROL_BOOKMARKS  ,           //   Usage (WWW fav)     ; bit 2: 4
    CONSUMER_CONTROL_SEARCH  ,              //   Usage (WWW search)  ; bit 3: 8
    CONSUMER_CONTROL_BR_STOP,               //   Usage (WWW stop)    ; bit 4: 16
    CONSUMER_CONTROL_BACK,                  //   Usage (WWW back)    ; bit 5: 32
    CONSUMER_CONTROL_CONFIGURATION,         //   Usage (Media sel)   ; bit 6: 64
    CONSUMER_CONTROL_EMAIL_READER           //   Usage (Mail)        ; bit 7: 128
};
*/
const uint16_t bltControl_Commands[] =
{ // the Control Commands keys are defined in the KeyboardDescriptors.h file.
    0xB0,                                   //   USAGE (Play)
    0xB1,                                   //   USAGE (Pause)
    CONSUMER_CONTROL_RECORD,                //   USAGE (Record)
    CONSUMER_CONTROL_FAST_FORWARD,          //   USAGE (Fast Forward)
    CONSUMER_CONTROL_REWIND,                //   USAGE (Rewind)
    CONSUMER_CONTROL_SCAN_NEXT,             //   USAGE (Scan Next Track)      
    CONSUMER_CONTROL_SCAN_PREVIOUS,         //   USAGE (Scan Previous Track)  
    CONSUMER_CONTROL_STOP ,                 //   USAGE (Stop)                
    CONSUMER_CONTROL_EJECT,                 //   USAGE (Eject)    
    0xB9,                                   //   USAGE (Random Play)         
    0xBC,                                   //   USAGE (Repeat)
    CONSUMER_CONTROL_PLAY_PAUSE,            //   USAGE (Play/Pause)          
    CONSUMER_CONTROL_MUTE,                  //   USAGE (Mute)                
    CONSUMER_CONTROL_VOLUME_INCREMENT,      //   USAGE (Volume Increment)    
    CONSUMER_CONTROL_VOLUME_DECREMENT,      //   USAGE (Volume Decrement)    
    CONSUMER_CONTROL_HOME,                  //   Usage (WWW Home)
    CONSUMER_CONTROL_LOCAL_BROWSER,         //   Usage (My Computer) 
    CONSUMER_CONTROL_CALCULATOR,            //   Usage (Calculator)  
    CONSUMER_CONTROL_BOOKMARKS,             //   Usage (WWW fav)     
    CONSUMER_CONTROL_SEARCH,                //   Usage (WWW search)  
    CONSUMER_CONTROL_BR_STOP,               //   Usage (WWW stop)    
    CONSUMER_CONTROL_BACK,                  //   Usage (WWW back)    
    CONSUMER_CONTROL_CONFIGURATION,         //   Usage (Media sel)   
    CONSUMER_CONTROL_EMAIL_READER,          //   Usage (Mail)        
};
const struct KeyCommand StartOfLineKeys[] = {
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

const Keyboards_t Local_Keyboards[] =
    {
        {"US-INT", Keyboard_US_INT},
        {"US", Keyboard_US},
        {"BG", Keyboard_BG},
        {"DE", Keyboard_DE},
        {"FR", Keyboard_French},
        {"NONE", Keyboard_NONE}
    };

DuckScript DuckScripts[DUCKSCRIPTLEN];

    DuckScript::DuckScript()
    {    
        KeyboardUniCodes = GetLocalKeyboard(settings::getLocalName());
        debugf("DuckScript Constructor\n");
    } //  constructor to initilize

    void DuckScript::Runfile(String fileName)
    {
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
        }
        else
        {
            return;
        }
        while (running)
        {
            if (!file)
            {
                debugln("Running File error");
                stop();
                return;
            }

            if (!file.available())
            {
                debugln("Reached end of file");
                stop();
                return;
            }
            Line_Buffer_i = 0;
            eol = false; // End of line

            StartKeyReport = CurrentKeyReport;
            StartoflineTime = millis();
            memset(Line_Buffer, 0, BUFFER_SIZE);
            // Read a utf8 line into the buffer https://www.fileformat.info/info/unicode/utf8.htm
            while (file.available() && !eol && Line_Buffer_i < BUFFER_SIZE)
            {
                if ('\n' == (Line_Buffer[Line_Buffer_i] = file.read()))
                {
                    eol = true;
                    Line_Buffer[Line_Buffer_i] = 0;
                }
                else
                {
                    ++Line_Buffer_i;
                }
            }
            running_line++;
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
            if (strncmp(Line_BufferPtr, "RESTART", 7) == 0)
            { // Restart the script
                file.seek(0);
                running_line = 0;
            }
            else
            {
                LineCommand();
            }
        }
        if (file)
            file.close();
        ReleaseKeyboardMouse();
        debugln("End of Script");
    }

    void DuckScript::stop()
    {
        if (running)
        {
            if (file)
                debugf("Stop Script [%s] at  Line = %d \n", FixPath(file.name()).c_str(), running_line);
            else
                debugln("Stop Script No file");
            running = false;
        }
        else
            debugf("Script was already Stoped\n");
        if (file)
            file.close();
        ReleaseKeyboardMouse();
    }

    bool DuckScript::isRunning()
    {
        return running;
    }

    

    String DuckScript::currentScript()
    {
        if (!running)
            return String("");
        return FixPath(file.name()); //  +" Line = " + String(running_line);
    }

    void DuckScript::WriteLine()
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
                        debugln("No KeyCommand found");
                        for (commands = 0; commands < sizeof(Control_Commands) / sizeof(Control_Commands[0]); commands++)
                        {
                            if (strncmp(Line_BufferPtr, Control_Commands[commands].StrCommand, strlen(Control_Commands[commands].StrCommand)) == 0)
                            {
                                debugf("Found Control_Command : %s\n", Control_Commands[commands].StrCommand);
                                Line_BufferPtr += strlen(Control_Commands[commands].StrCommand);
                                pressMedia(Control_Commands[commands].RawKeycode);
                                break;
                            }
                        }
                        if (commands == sizeof(Control_Commands) / sizeof(Control_Commands[0])){
                            debugf("No Control_Commands found [%s]\n",Line_BufferPtr);
                            for (commands = 0; commands < sizeof(System_Commands) / sizeof(System_Commands[0]); commands++)
                            {
                                if (strncmp(Line_BufferPtr, System_Commands[commands].StrCommand, strlen(System_Commands[commands].StrCommand)) == 0)
                                {
                                    debugf("Found System_Commands : %s\n", System_Commands[commands].StrCommand);
                                    Line_BufferPtr += strlen(System_Commands[commands].StrCommand);
#ifdef CONFIG_TINYUSB_HID_ENABLED
                                    UsbSystemControl.press(System_Commands[commands].RawKeycode);
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
                                    ; 
#endif
                                    break;
                                }
                            }
                            if (commands == sizeof(System_Commands) / sizeof(System_Commands[0])){
                                    press('\\');
                            }       
                        }
                    }
                }
            }
            else // No in line Key commands
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
        return;
    }

    uint32_t DuckScript::getUniCode(char *buffer, uint8_t *utf_len_return)
    {
        // uint8_t *utf = (uint8_t *)strPtr;
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
        // debugf("U %4x Len %d\n", *utf_code, utf_len);
        if (utf_len_return)
            *utf_len_return = utf_len;
        return (utf_code);
    }

    const UnicodeToKeyCode_t *DuckScript::GetLocalKeyboard(char *BufferPtr)
    {
        debugf("GetLocalKeyboard (%s)\n",BufferPtr);
        const UnicodeToKeyCode_t *LKeyboardUniCodes= Keyboard_US_INT;
        for (int Lang = 0; Lang < (sizeof(Local_Keyboards) / sizeof(Local_Keyboards[0])); Lang++)
        {
            debugf("%s %p\n",Local_Keyboards[Lang].KeyboardName,(void *) (Local_Keyboards[Lang].KeyboardUniCodes));
            if (strncmp(Local_Keyboards[Lang].KeyboardName, BufferPtr, strlen(Local_Keyboards[Lang].KeyboardName)) == 0)
            {
                LKeyboardUniCodes = Local_Keyboards[Lang].KeyboardUniCodes;
                debugf("New LOCALE = %s\n", Local_Keyboards[Lang].KeyboardName,(void *)LKeyboardUniCodes);
                break;
            }
        }
        debugf("LP=%p\n",(void *) (LKeyboardUniCodes));
        return LKeyboardUniCodes;
    }

    void DuckScript::LineCommand()
    {
        KeyReport StartKeyReport;
        StartKeyReport = CurrentKeyReport;
        bool add_enter_to_line = true;

        if (strncmp(Line_BufferPtr, "LED ", 4) == 0)
        {
            int c[5] = {0, 0, 0, 0, 0};
            for (uint8_t i = 0; i < 5; ++i)
            {
                PointToNextParammeter();
                c[i] = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            }
            led::setColor(c[0], c[1], c[2], c[3], c[4]);
            return;
        }
        else if (strncmp(Line_BufferPtr, "DEFAULTDELAY ", 13) == 0 || strncmp(Line_BufferPtr, "DEFAULT_DELAY ", 14) == 0)
        {
            PointToNextParammeter();
            defaultDelay = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            return;
        }
        else if (strncmp(Line_BufferPtr, "KEYDELAY ", 9) == 0 || strncmp(Line_BufferPtr, "KEY_DELAY ", 10) == 0)
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
            debugf("Delay Time = %d\n", time);
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
        else if (strncmp(Line_BufferPtr, "MOUSE ", 6) == 0 || strncmp(Line_BufferPtr, "MOVE ", 5) == 0)
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
        }
        else if (strncmp(Line_BufferPtr, "KEYCODE ", 8) == 0)
        {
            KeyReport k;
            int c[7] = {0, 0, 0, 0, 0, 0, 0};
            for (uint8_t i = 0; i < 7; ++i)
            {
                PointToNextParammeter();
                c[i] = toInt(Line_BufferPtr, strlen(Line_BufferPtr));
            }
            k.modifiers = (uint8_t)c[0];
            k.reserved = 0;
            for (uint8_t i = 0; i < 6; ++i)
            {
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
            KeyboardUniCodes = GetLocalKeyboard(Line_BufferPtr);
            return;
        }
        else if (strncmp(Line_BufferPtr, "STRING ", 7) == 0)
        {
            Line_BufferPtr += 7; // skip the firts space after command;
            add_enter_to_line = false;
        }

        int commands = 0;
        char *StartOfLine = Line_BufferPtr;
        if ('\\' == *Line_BufferPtr)
            Line_BufferPtr++;
        for (commands = 0; commands < sizeof(StartOfLineKeys) / sizeof(StartOfLineKeys[0]); commands++)
        {
            if (strncmp(Line_BufferPtr, StartOfLineKeys[commands].StrCommand, strlen(StartOfLineKeys[commands].StrCommand)) == 0)
            {
                char *startoftextline = Line_BufferPtr;
                debugf("Found Command : [%s] ,len=[%d], [%s]\n", StartOfLineKeys[commands].StrCommand, strlen(Line_BufferPtr), Line_BufferPtr);
                Line_BufferPtr += strlen(StartOfLineKeys[commands].StrCommand);
                if (*Line_BufferPtr == ' ')
                    Line_BufferPtr++;                                      // skip the firts space after command;
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
        return;
    }

    void DuckScript::LineDelay()
    {
        uint32_t WaitTime = millis() + defaultDelay;
        while (millis() <= WaitTime && running)
        {
            delay(1);
        }
    }

    void DuckScript::PointToNextParammeter()
    {
        while (*Line_BufferPtr != ' ' && *Line_BufferPtr != '\n' && *Line_BufferPtr != 0)
            Line_BufferPtr++;
        while (*Line_BufferPtr == ' ')
            Line_BufferPtr++;
    }

    int DuckScript::toInt(const char *str, size_t len)
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
                if (str[0] == '-')
                    positive = false;
                if ((str[i] >= '0') && (str[i] <= '9'))
                {
                    val = val * 10 + (str[i] - '0');
                }
            }
        }
        if (!positive)
        {
            val *= -1;
            str--;
        }
        // debugf("%d =toInt(%s)\n", val, str);
        return val;
    }

    void DuckScript::press(int Unicode)
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
        {   
            // To enter a UniCode there ar diffrent way to do this
            // Mode 1 : <ALT>decimalnumber<ALTup>
            // Mode 2 : for  ChromeOS, macOS, Linux  <Ctrl><SHIF><U><Releas-all>HEXUnicode<enter>
            
            // This will write the UniCode to the Keyboard as ALT+0 decimal number
            // But we have to save the CurrentKeyReport
            KeyReport KeyReportSaved = CurrentKeyReport;
            uint8_t Keymask = 0;
            uint8_t n = 0;
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

    void DuckScript::pressMedia(uint16_t Media)
    {
        if (running)
        {
            uint32_t WaitTime = millis() + defaultKeyDelay;
            debugf("sendMediaReport: %04x\n",Media);
#if defined(CONFIG_TINYUSB_ENABLED)
            if (hid.ready()) // will need to created a bug report on this as we get an error in the Errorlog "SendReport(): not ready When the USB is not connected"
            {       
                UsbConsumerControl.press(Media);
                UsbConsumerControl.release();
            }
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
            for(uint8_t f=0;f<sizeof(bltControl_Commands)/sizeof(bltControl_Commands[0]);f++)
            {
                
                if (Media == bltControl_Commands[f])
                {
                    debugf("BLE Media = %04x Bit=%d MAP=%04x\n",Media,f,(((uint32_t)0x01)<<f));
                    if(compositeHID.isConnected())
                    {

                        KeyboardMediaInputReport _mediaKeyReport;
                        _mediaKeyReport =(KeyboardMediaInputReport ) (((uint32_t)0x01)<<f);
                        bleKeyboard->setMediaKeyReport(&_mediaKeyReport);
                    }
                    else
                    {
                        debugln("No BLE connection");
                    }
                }
            }
#endif
            while (millis() <= WaitTime && running)
            {
                delay(1);
            }
        }
    }
    // Create are own pressRaw releaseRaw as then we can use the CurrentKeyReport
    // and save the status to enter a UniCode
    void DuckScript::pressRaw(uint8_t Key)
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
                if (i == 6)
                    return;
            }
        }
        else
        { // not a modifier and not a key
            return;
        }
        sendReport(&CurrentKeyReport);
    }

    void DuckScript::releaseRaw(uint8_t Key)
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
            return;
        }
        sendReport(&CurrentKeyReport);
        return;
    }

    void DuckScript::toggelmodifiers(uint8_t Key)
    {
        uint8_t i;
        if (Key >= 0xE0 && Key < 0xE8)
        {
            // it's a toggelmodifier key
            CurrentKeyReport.modifiers ^= (1 << (Key - 0xE0));
        }
        sendReport(&CurrentKeyReport);
    }

    void DuckScript::releaseAll()
    {
        KeyReport releaseAllKeyReport = {0, 0, {0, 0, 0, 0, 0, 0}};
        CurrentKeyReport = releaseAllKeyReport;
        sendReport(&CurrentKeyReport);
    }

    void DuckScript::sendReport(KeyReport *k)
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
                if (hid.ready()) // will need to created a bug report on this as we get an error in the Errorlog "SendReport(): not ready When the USB is not connected"
                    UsbKeyboard.sendReport(k);
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
                if(compositeHID.isConnected())
                {
                    bleKeyboard->setKeyReport((KeyboardInputReport *)k);
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

    void DuckScript::mouse_move(int8_t x, int8_t y, int8_t wheel, int8_t pan)
    {
        if (running)
        {
            uint32_t WaitTime = millis() + defaultMouseDelay;
#if defined(CONFIG_TINYUSB_ENABLED)
            if (hid.ready())
                UsbMouse.move(x, y, wheel, pan);
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
            if(compositeHID.isConnected())
            { 
                debugf("blemove %d %d %d %d\n",x, y, wheel, pan);
                bleMouse->mouseMove(x, y, wheel, pan);
            }
            else
                debugln("ble Not connected");
#endif
            while (millis() <= WaitTime && running)
            {
                delay(1);
            }
        }
    }

    void DuckScript::mouse_absmove(int8_t x, int8_t y, int8_t wheel, int8_t pan)
    {
        if (running)
        {
#if defined(CONFIG_TINYUSB_ENABLED)
            if (hid.ready())
                UsbMouse.move(x, y, wheel, pan);
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
            if(compositeHID.isConnected())
                bleMouse->mouseMove(x, y, wheel, pan);
#endif
        }
    }

    uint8_t DuckScript::mouse_GetButtons(char *strButtons)
    {
        uint8_t Buttons = 0;
        String Buttonline = String(strButtons);
        if (Buttonline.indexOf("LEFT") > 0)
            Buttons |= MOUSE_LEFT;
        if (Buttonline.indexOf("RIGHT") > 0)
            Buttons |= MOUSE_RIGHT;
        if (Buttonline.indexOf("MIDDLE") > 0)
            Buttons |= MOUSE_MIDDLE;
        if (Buttonline.indexOf("BACKWARD") > 0)
            Buttons |= MOUSE_BACKWARD;
        if (Buttonline.indexOf("FORWARD") > 0)
            Buttons |= MOUSE_FORWARD;
        if (Buttonline.indexOf("ALL") > 0)
            Buttons |= (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_BACKWARD | MOUSE_FORWARD);
        return Buttons;
    }

    void DuckScript::mouse_click(uint8_t b)
    {
        if (running)
        {
            uint32_t WaitTime = millis() + defaultMouseDelay;
#if defined(CONFIG_TINYUSB_ENABLED)
            if (hid.ready())
                UsbMouse.click(b);
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
            if(compositeHID.isConnected())
                bleMouse->mouseClick(b);
#endif
            while (millis() <= WaitTime && running)
            {
                delay(1);
            }
        }
    }

    void DuckScript::mouse_release(uint8_t b)
    {
        if (running)
        {
            uint32_t WaitTime = millis() + defaultMouseDelay;
#if defined(CONFIG_TINYUSB_ENABLED)
            if (hid.ready())
                UsbMouse.release(b);
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
            if(compositeHID.isConnected())
                bleMouse->mouseRelease(b);
#endif
            while (millis() <= WaitTime && running)
            {
                delay(1);
            }
        }
    }

    void DuckScript::mouse_press(uint8_t b)
    {
        if (running)
        {
            uint32_t WaitTime = millis() + defaultMouseDelay;
#if defined(CONFIG_TINYUSB_ENABLED)
            if (hid.ready())
                UsbMouse.press(b);
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
            if(compositeHID.isConnected())
                bleMouse->mousePress(b);
#endif
            while (millis() <= WaitTime && running)
            {
                delay(1);
            }
        }
    }

    void DuckScript::ReleaseKeyboardMouse()
    {
#if defined(CONFIG_TINYUSB_ENABLED)
        if (hid.ready())
            UsbKeyboard.releaseAll();
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
        if(compositeHID.isConnected())
        {
            bleKeyboard->resetKeys();
            bleMouse->mouseRelease(MOUSE_ALL);
        }
#endif
    }

    void duckscript_begin()
    {
#if defined(CONFIG_TINYUSB_ENABLED)
        USB.productName((CUSTOM_USB_PRODUCT" USB"));
        USB.VID(CUSTOM_USB_VID);
        USB.PID(CUSTOM_USB_PID);
        USB.manufacturerName(CUSTOM_USB_MANUFACTURER);
        USB.begin();
        UsbKeyboard.begin();
        UsbMouse.begin();
        UsbGamepad.begin();
        UsbConsumerControl.begin(); 
        UsbSystemControl.begin();       
#endif
#if defined(CONFIG_BT_BLE_ENABLED)
    // Set up keyboard
    KeyboardConfiguration bleKeyboardConfig;
    bleKeyboardConfig.setUseMediaKeys(true);  // Media keys are not enabled by default
    bleKeyboardConfig.setAutoReport(true);
    bleKeyboard = new KeyboardDevice(bleKeyboardConfig);

    // Set up mouse
    MouseConfiguration bleMouseConfig;
    bleMouseConfig.setAutoReport(true);
    bleMouse = new MouseDevice(bleMouseConfig);

     // Add both devices to the composite HID device to manage them
    compositeHID.addDevice(bleKeyboard);
    compositeHID.addDevice(bleMouse);

    // Start the composite HID device to broadcast HID reports
    compositeHID.begin();

#endif
    }

    struct TaskParameters {
        int ScripNo;
        char fileName[32];
    };
    
    void duckscripts_task(TaskParameters *TParameter)
    {
        debugf("duckscripts_task %d,%s\n", TParameter->ScripNo, TParameter->fileName);
        DuckScripts[TParameter->ScripNo].Runfile(TParameter->fileName);
        vTaskDelete(NULL); // Delete this task when done
    }
    
    void duckscripts_run(char *filename)
    {
        int Task = 0;
        bool RunTask = true;
        while (Task < DUCKSCRIPTLEN)
        {
            if (DuckScripts[Task].currentScript()==FixPath(String(filename)))
            {
                RunTask = false;
                debugf("Script is already running\n");
                break;
            }        
            Task++;
        }   
        if(RunTask)
        {
            static TaskParameters TParameters;
            strncpy(TParameters.fileName ,filename,sizeof(TParameters.fileName));
            Task = 0;
            while (Task < DUCKSCRIPTLEN)
            {
                if (!DuckScripts[Task].isRunning())
                {
                    TParameters.ScripNo = Task;
                    debugf("duckscripts_run %d,%s\n", TParameters.ScripNo, TParameters.fileName);
                    xTaskCreate(
                        (TaskFunction_t)duckscripts_task, // Function that should be executed
                        "runDuckScriptTask",              // Name of the task
                        4096,                             // Stack size in words
                        &TParameters,                     // Pointer to the Parameter to pass to the task
                        1,                                // Priority
                        NULL                              // Task handle
                    );
                    break;
                }
                Task++;
            }
        }
    }

    void duckscripts_stop(char *filename)
    {
        int Task = 0;
        debugf("duckscripts_stop(%s)\n", filename);
        String file_name = FixPath(String(filename));    
        for (DuckScript duckscript : DuckScripts)
        {
            if(duckscript.isRunning())
                debugln("running [" +duckscript.currentScript() +"] [" +file_name+"]");
            if (duckscript.currentScript() == file_name)
            {
                debugf("duckscripts_stoping %s\n", duckscript.currentScript());
                duckscript.stop();
                break;
            }       
        }
    }

    void duckscripts_stopall()
    {
        for (DuckScript duckscript : DuckScripts)
        {
            if (duckscript.isRunning() )
            {
                debugf("duckscripts_stoping %s\n", duckscript.currentScript());
                duckscript.stop();
            }
        }
    }

    String FixPath(String Path)
    {
        if (Path.startsWith("/"))
            return (Path);
        return ("/" + Path);
    }
