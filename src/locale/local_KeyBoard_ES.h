#pragma once
#include "Local_KeyBoard.h"

// https://learn.microsoft.com/en-us/globalization/windows-keyboard-layouts
// https://learn.microsoft.com/en-us/globalization/keyboards/kbdsp

const UnicodeToKeyCode_t Keyboard_ES[] =
    {
        {'\b', {HID_KEY_BACKSPACE, 0}}, // BS Backspace
        {'\t', {HID_KEY_TAB, 0}},       // BS TAB Tab
        {'\n', {HID_KEY_ENTER, 0}},     // LF Enter
        {'\e', {HID_KEY_ESCAPE, 0}},    // Escape key
        {' ', {HID_KEY_SPACE, 0}},      // Space
        {127, {HID_KEY_DELETE, 0}},     // Delete

        // Top row (numbers)
        {0x00BA, {HID_KEY_GRAVE, 0}}, // 'º'
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
        {'\'', {HID_KEY_MINUS, 0}},
        {0x00A1, {HID_KEY_EQUAL, 0}}, // '¡'

        // Second row qwerty[]\
        {'q', {HID_KEY_Q, 0}},
        {'w', {HID_KEY_W, 0}},
        {'e', {HID_KEY_E, 0}},
        {'r', {HID_KEY_R, 0}},
        {'t', {HID_KEY_T, 0}},
        {'y', {HID_KEY_Y, 0}},
        {'u', {HID_KEY_U, 0}},
        {'i', {HID_KEY_I, 0}},
        {'o', {HID_KEY_O, 0}},
        {'p', {HID_KEY_P, 0}},
        {0x00B4, {HID_KEY_BRACKET_LEFT, 0}}, // dead acute
        {'+', {HID_KEY_BRACKET_RIGHT, 0}},
        {0x00E7, {HID_KEY_BACKSLASH, 0}},    // 'ç'

        // Third row asdfghjkl;'
        {'a', {HID_KEY_A, 0}},
        {'s', {HID_KEY_S, 0}},
        {'d', {HID_KEY_D, 0}},
        {'f', {HID_KEY_F, 0}},
        {'g', {HID_KEY_G, 0}},
        {'h', {HID_KEY_H, 0}},
        {'j', {HID_KEY_J, 0}},
        {'k', {HID_KEY_K, 0}},
        {'l', {HID_KEY_L, 0}},
        {0x00F1, {HID_KEY_SEMICOLON, 0}}, // 'ñ'
        {'\'', {HID_KEY_APOSTROPHE, 0}},

        // Bottom row <>zxcvbnm,.-
        {'<', {HID_KEY_NON_US_BACKSLASH, 0}},
        {'z', {HID_KEY_Z, 0}},
        {'x', {HID_KEY_X, 0}},
        {'c', {HID_KEY_C, 0}},
        {'v', {HID_KEY_V, 0}},
        {'b', {HID_KEY_B, 0}},
        {'n', {HID_KEY_N, 0}},
        {'m', {HID_KEY_M, 0}},
        {',', {HID_KEY_COMMA, 0}},
        {'.', {HID_KEY_PERIOD, 0}},
        {'-', {HID_KEY_SLASH, 0}},

        ///////////////////////////////////////////////// SHIFT
        // Top row (numbers)
        {0x00AA, {HID_KEY_SHIFT_LEFT, HID_KEY_GRAVE, 0}}, // 'ª'
        {'!', {HID_KEY_SHIFT_LEFT, HID_KEY_1, 0}},
        {'"', {HID_KEY_SHIFT_LEFT, HID_KEY_2, 0}},
        {0x00B7, {HID_KEY_SHIFT_LEFT, HID_KEY_3, 0}}, // '·'
        {'$', {HID_KEY_SHIFT_LEFT, HID_KEY_4, 0}},
        {'%', {HID_KEY_SHIFT_LEFT, HID_KEY_5, 0}},
        {'&', {HID_KEY_SHIFT_LEFT, HID_KEY_6, 0}},
        {'/', {HID_KEY_SHIFT_LEFT, HID_KEY_7, 0}},
        {'(', {HID_KEY_SHIFT_LEFT, HID_KEY_8, 0}},
        {')', {HID_KEY_SHIFT_LEFT, HID_KEY_9, 0}},
        {'=', {HID_KEY_SHIFT_LEFT, HID_KEY_0, 0}},
        {'?', {HID_KEY_SHIFT_LEFT, HID_KEY_MINUS, 0}},
        {0x00BF, {HID_KEY_SHIFT_LEFT, HID_KEY_EQUAL, 0}}, // '¿'

        // Second row QWERTY[]\
        {'Q', {HID_KEY_SHIFT_LEFT, HID_KEY_Q, 0}},
        {'W', {HID_KEY_SHIFT_LEFT, HID_KEY_W, 0}},
        {'E', {HID_KEY_SHIFT_LEFT, HID_KEY_E, 0}},
        {'R', {HID_KEY_SHIFT_LEFT, HID_KEY_R, 0}},
        {'T', {HID_KEY_SHIFT_LEFT, HID_KEY_T, 0}},
        {'Y', {HID_KEY_SHIFT_LEFT, HID_KEY_Y, 0}},
        {'U', {HID_KEY_SHIFT_LEFT, HID_KEY_U, 0}},
        {'I', {HID_KEY_SHIFT_LEFT, HID_KEY_I, 0}},
        {'O', {HID_KEY_SHIFT_LEFT, HID_KEY_O, 0}},
        {'P', {HID_KEY_SHIFT_LEFT, HID_KEY_P, 0}},
        {0x00A8, {HID_KEY_SHIFT_LEFT, HID_KEY_BRACKET_LEFT, 0}}, // '¨'
        {'*', {HID_KEY_SHIFT_LEFT, HID_KEY_BRACKET_RIGHT, 0}},
        {0x00C7, {HID_KEY_SHIFT_LEFT, HID_KEY_BACKSLASH, 0}},    // 'Ç'

        // Third row ASDFGHJKL:"
        {'A', {HID_KEY_SHIFT_LEFT, HID_KEY_A, 0}},
        {'S', {HID_KEY_SHIFT_LEFT, HID_KEY_S, 0}},
        {'D', {HID_KEY_SHIFT_LEFT, HID_KEY_D, 0}},
        {'F', {HID_KEY_SHIFT_LEFT, HID_KEY_F, 0}},
        {'G', {HID_KEY_SHIFT_LEFT, HID_KEY_G, 0}},
        {'H', {HID_KEY_SHIFT_LEFT, HID_KEY_H, 0}},
        {'J', {HID_KEY_SHIFT_LEFT, HID_KEY_J, 0}},
        {'K', {HID_KEY_SHIFT_LEFT, HID_KEY_K, 0}},
        {'L', {HID_KEY_SHIFT_LEFT, HID_KEY_L, 0}},
        {0x00D1, {HID_KEY_SHIFT_LEFT, HID_KEY_SEMICOLON, 0}}, // 'Ñ'
        {'"', {HID_KEY_SHIFT_LEFT, HID_KEY_APOSTROPHE, 0}},

        // Bottom row <>ZXCVBNM;:_
        {'>', {HID_KEY_SHIFT_LEFT, HID_KEY_NON_US_BACKSLASH, 0}},
        {'Z', {HID_KEY_SHIFT_LEFT, HID_KEY_Z, 0}},
        {'X', {HID_KEY_SHIFT_LEFT, HID_KEY_X, 0}},
        {'C', {HID_KEY_SHIFT_LEFT, HID_KEY_C, 0}},
        {'V', {HID_KEY_SHIFT_LEFT, HID_KEY_V, 0}},
        {'B', {HID_KEY_SHIFT_LEFT, HID_KEY_B, 0}},
        {'N', {HID_KEY_SHIFT_LEFT, HID_KEY_N, 0}},
        {'M', {HID_KEY_SHIFT_LEFT, HID_KEY_M, 0}},
        {';', {HID_KEY_SHIFT_LEFT, HID_KEY_COMMA, 0}},
        {':', {HID_KEY_SHIFT_LEFT, HID_KEY_PERIOD, 0}},
        {'_', {HID_KEY_SHIFT_LEFT, HID_KEY_SLASH, 0}},

        ///////////////////////////////////////////////// ALT GR
        // Top row (numbers)
        {'|', {HID_KEY_ALT_RIGHT, HID_KEY_1, 0}},
        {'@', {HID_KEY_ALT_RIGHT, HID_KEY_2, 0}},
        {'#', {HID_KEY_ALT_RIGHT, HID_KEY_3, 0}},
        {'~', {HID_KEY_ALT_RIGHT, HID_KEY_4, 0}},
        {0x20AC, {HID_KEY_ALT_RIGHT, HID_KEY_5, 0}}, // '€'
        {0x00AC, {HID_KEY_ALT_RIGHT, HID_KEY_6, 0}}, // '¬'
        {'{', {HID_KEY_ALT_RIGHT, HID_KEY_7, 0}},
        {'[', {HID_KEY_ALT_RIGHT, HID_KEY_8, 0}},
        {']', {HID_KEY_ALT_RIGHT, HID_KEY_9, 0}},
        {'}', {HID_KEY_ALT_RIGHT, HID_KEY_0, 0}},
        {'\\', {HID_KEY_ALT_RIGHT, HID_KEY_MINUS, 0}},
        {'^', {HID_KEY_ALT_RIGHT, HID_KEY_EQUAL, 0}},

        // Second row qwerty[]\
        {0x00B4, {HID_KEY_ALT_RIGHT, HID_KEY_BRACKET_LEFT, 0}}, // combining acute
        {'~', {HID_KEY_ALT_RIGHT, HID_KEY_BRACKET_RIGHT, 0}},
        {'|', {HID_KEY_ALT_RIGHT, HID_KEY_NON_US_BACKSLASH, 0}},
        {'@', {HID_KEY_ALT_RIGHT, HID_KEY_Q, 0}},
        {0x20AC, {HID_KEY_ALT_RIGHT, HID_KEY_E, 0}},

        // Bottom row <>zxcvbnm,.-
        {0x00A6, {HID_KEY_ALT_RIGHT, HID_KEY_COMMA, 0}}, // '¦'
        {0x00B5, {HID_KEY_ALT_RIGHT, HID_KEY_M, 0}},     // 'µ'

        {0, {0, 0}} // UniCode 0 is the last one in the list
};
