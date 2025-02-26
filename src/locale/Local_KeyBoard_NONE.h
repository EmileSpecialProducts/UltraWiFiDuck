#pragma once
#include "Local_KeyBoard.h"

// https://learn.microsoft.com/en-us/globalization/windows-keyboard-layouts
// https://kbdlayout.info/
// This keyboard will not do any key translation and will only use the ALT + Unicode number to enter the keys.
// This can be useful for testing meltable languages

UnicodeToKeyCode_t Keyboard_NONE[] =
{
    {'\b', {HID_KEY_BACKSPACE, 0}}, // BS Backspace
    {'\t', {HID_KEY_TAB, 0}},       // BS TAB Tab
    {'\n', {HID_KEY_ENTER, 0}},     // LF Enter
    {'\e', {HID_KEY_ESCAPE, 0}},    // Escape key
    {' ', {HID_KEY_SPACE, 0}},      // Space
    {127, {HID_KEY_DELETE, 0}},     // Delete
    {0, {0, 0}}          // UniCode 0 is the last one in the list
};
