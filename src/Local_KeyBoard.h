#pragma once
#include <Arduino.h>
#include "duckscript.h"

typedef struct UnicodeToKeyCode_t
{
    uint32_t unicode;
    uint8_t RawKeyCodes[4];
} UnicodeToKeyCode_t;

typedef struct Keyboards_t
{
    char KeyboardName[12];
    UnicodeToKeyCode_t *KeyboardUniCodes;
} Keyboards_t;

// https://learn.microsoft.com/en-us/globalization/windows-keyboard-layouts
// https://kbdlayout.info/
#include "locale\local_KeyBoard_BG.h"
#include "locale\local_KeyBoard_US.h"
#include "locale\local_KeyBoard_US-INT.h"
#include "locale\local_KeyBoard_NONE.h"

Keyboards_t Local_Keyboards[] =
{
    {"US-INT", Keyboard_US_INT},
    {"US", Keyboard_US},
    {"BG", Keyboard_BG},
    {"NONE", Keyboard_NONE}
};