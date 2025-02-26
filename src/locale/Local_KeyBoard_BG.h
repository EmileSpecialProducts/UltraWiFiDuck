#pragma once
// https://learn.microsoft.com/en-us/globalization/windows-keyboard-layouts
// https://kbdlayout.info/
// https://learn.microsoft.com/en-us/globalization/keyboards/kbdbgph1
// Bulgarian (Phonetic Traditional) Keyboard 
#include "Local_KeyBoard.h"

UnicodeToKeyCode_t Keyboard_BG[] =
    {
        {'\b', {HID_KEY_BACKSPACE, 0}}, // BS Backspace
        {'\t', {HID_KEY_TAB, 0}},       // BS TAB Tab
        {'\n', {HID_KEY_ENTER, 0}},     // LF Enter
        {'\e', {HID_KEY_ESCAPE, 0}},    // Escape key
        {' ', {HID_KEY_SPACE, 0}},      // Space
        {127, {HID_KEY_DELETE, 0}},     // Delete

        // Top ROW `1234567890-= ( numberts in the US )
        {0x447, {HID_KEY_GRAVE, 0}}, // '`'
        {'1', {HID_KEY_1, 0}},
        {'2', {HID_KEY_2, 0}},
        {'3', {HID_KEY_3, 0}},
        {'4', {HID_KEY_4, 0}},
        {'5', {HID_KEY_5, 0}},
        {'6', {HID_KEY_6, 0}},
        {'7', {HID_KEY_7, 0}},
        {'8', {HID_KEY_8, 0}},
        {'9', {HID_KEY_9, 0}},
        {'0', {HID_KEY_0, 0}},
        {'-', {HID_KEY_MINUS, 0}},
        {'=', {HID_KEY_EQUAL, 0}},
        // Second row qwerty[]\ in US
        {0x44F, {HID_KEY_Q, 0}},
        {0x432, {HID_KEY_W, 0}},
        {0x435, {HID_KEY_E, 0}},
        {0x440, {HID_KEY_R, 0}},
        {0x442, {HID_KEY_T, 0}},
        {0x44A, {HID_KEY_Y, 0}},
        {0x443, {HID_KEY_U, 0}},
        {0x438, {HID_KEY_I, 0}},
        {0x43E, {HID_KEY_O, 0}},
        {0x43F, {HID_KEY_P, 0}},
        {0x448, {HID_KEY_BRACKET_LEFT, 0}},
        {0x449, {HID_KEY_BRACKET_RIGHT, 0}},
        {0x201E, {HID_KEY_BACKSLASH, 0}},
        // thurted row asdfghjkl;' in US
        {0x430, {HID_KEY_A, 0}},
        {0x441, {HID_KEY_S, 0}},
        {0x434, {HID_KEY_D, 0}},
        {0x444, {HID_KEY_F, 0}},
        {0x433, {HID_KEY_G, 0}},
        {0x445, {HID_KEY_H, 0}},
        {0x439, {HID_KEY_J, 0}},
        {0x43A, {HID_KEY_K, 0}},
        {0x43B, {HID_KEY_L, 0}},
        {';', {HID_KEY_SEMICOLON, 0}},
        {'\'', {HID_KEY_APOSTROPHE, 0}},
        // botom row zxcvbnm,./ in the US
        {0x437, {HID_KEY_Z, 0}},
        {0x43C, {HID_KEY_X, 0}},
        {0x446, {HID_KEY_C, 0}},
        {0x436, {HID_KEY_V, 0}},
        {0x431, {HID_KEY_B, 0}},
        {0x43D, {HID_KEY_N, 0}},
        {0x43C, {HID_KEY_M, 0}},
        {',', {HID_KEY_COMMA, 0}},
        {'.', {HID_KEY_PERIOD, 0}},
        {'/', {HID_KEY_SLASH, 0}},

        ///////////////////////////////////////////////// SHIFT
        // Top ROW ( numberts )
        {0x427, {HID_KEY_SHIFT_LEFT, HID_KEY_GRAVE, 0}}, // '`'
        {'!', {HID_KEY_SHIFT_LEFT, HID_KEY_1, 0}},
        {'@', {HID_KEY_SHIFT_LEFT, HID_KEY_2, 0}},
        {0x2116, {HID_KEY_SHIFT_LEFT, HID_KEY_3, 0}},
        {'$', {HID_KEY_SHIFT_LEFT, HID_KEY_4, 0}},
        {'%', {HID_KEY_SHIFT_LEFT, HID_KEY_5, 0}},
        {0x20AC, {HID_KEY_SHIFT_LEFT, HID_KEY_6, 0}},
        {0xA7, {HID_KEY_SHIFT_LEFT, HID_KEY_7, 0}},
        {'*', {HID_KEY_SHIFT_LEFT, HID_KEY_8, 0}},
        {'(', {HID_KEY_SHIFT_LEFT, HID_KEY_9, 0}},
        {')', {HID_KEY_SHIFT_LEFT, HID_KEY_0, 0}},
        {'_', {HID_KEY_SHIFT_LEFT, HID_KEY_MINUS, 0}},
        {'+', {HID_KEY_SHIFT_LEFT, HID_KEY_EQUAL, 0}},
        // Second row qwerty[]\ in US
        {0x42F, {HID_KEY_SHIFT_LEFT, HID_KEY_Q, 0}},
        {0x412, {HID_KEY_SHIFT_LEFT, HID_KEY_W, 0}},
        {0x415, {HID_KEY_SHIFT_LEFT, HID_KEY_E, 0}},
        {0x420, {HID_KEY_SHIFT_LEFT, HID_KEY_R, 0}},
        {0x422, {HID_KEY_SHIFT_LEFT, HID_KEY_T, 0}},
        {0x42A, {HID_KEY_SHIFT_LEFT, HID_KEY_Y, 0}},
        {0x423, {HID_KEY_SHIFT_LEFT, HID_KEY_U, 0}},
        {0x418, {HID_KEY_SHIFT_LEFT, HID_KEY_I, 0}},
        {0x41E, {HID_KEY_SHIFT_LEFT, HID_KEY_O, 0}},
        {0x41F, {HID_KEY_SHIFT_LEFT, HID_KEY_P, 0}},
        {0x428, {HID_KEY_SHIFT_LEFT, HID_KEY_BRACKET_LEFT, 0}},
        {0x429, {HID_KEY_SHIFT_LEFT, HID_KEY_BRACKET_RIGHT, 0}},
        {0x42E, {HID_KEY_SHIFT_LEFT, HID_KEY_BACKSLASH, 0}},
        // thurted row asdfghjkl;' in US
        {0x410, {HID_KEY_SHIFT_LEFT, HID_KEY_A, 0}},
        {0x421, {HID_KEY_SHIFT_LEFT, HID_KEY_S, 0}},
        {0x414, {HID_KEY_SHIFT_LEFT, HID_KEY_D, 0}},
        {0x424, {HID_KEY_SHIFT_LEFT, HID_KEY_F, 0}},
        {0x413, {HID_KEY_SHIFT_LEFT, HID_KEY_G, 0}},
        {0x425, {HID_KEY_SHIFT_LEFT, HID_KEY_H, 0}},
        {0x419, {HID_KEY_SHIFT_LEFT, HID_KEY_J, 0}},
        {0x41A, {HID_KEY_SHIFT_LEFT, HID_KEY_K, 0}},
        {0x41B, {HID_KEY_SHIFT_LEFT, HID_KEY_L, 0}},
        {':', {HID_KEY_SHIFT_LEFT, HID_KEY_SEMICOLON, 0}},
        {'"', {HID_KEY_SHIFT_LEFT, HID_KEY_APOSTROPHE, 0}},
        // botom row zxcvbnm,./ in the US
        {0x417, {HID_KEY_SHIFT_LEFT, HID_KEY_Z, 0}},
        {0x45D, {HID_KEY_SHIFT_LEFT, HID_KEY_X, 0}},
        {0x426, {HID_KEY_SHIFT_LEFT, HID_KEY_C, 0}},
        {0x416, {HID_KEY_SHIFT_LEFT, HID_KEY_V, 0}},
        {0x411, {HID_KEY_SHIFT_LEFT, HID_KEY_B, 0}},
        {0x41D, {HID_KEY_SHIFT_LEFT, HID_KEY_N, 0}},
        {0x41C, {HID_KEY_SHIFT_LEFT, HID_KEY_M, 0}},
        {'<', {HID_KEY_SHIFT_LEFT, HID_KEY_COMMA, 0}},
        {'>', {HID_KEY_SHIFT_LEFT, HID_KEY_PERIOD, 0}},
        {'?', {HID_KEY_SHIFT_LEFT, HID_KEY_SLASH, 0}},

        //{0x42B, {HID_KEY_SHIFT_LEFT, HID_KEY_ALT_RIGHT, HID_KEY_BRACKET_LEFT, 0}}, 'Ы'
        //{0x42D, {HID_KEY_SHIFT_LEFT, HID_KEY_ALT_RIGHT, HID_KEY_BRACKET_RIGHT, 0}}, 'Э'

        {0, {0, 0}} // UniCode 0 is the last one in the list
};
