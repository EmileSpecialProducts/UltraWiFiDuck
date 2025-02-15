#pragma once
// https://learn.microsoft.com/en-us/globalization/windows-keyboard-layouts
// https://kbdlayout.info/
#include "locale\Local_KeyBoard.h"

UnicodeToKeyCode_t Keyboard_US_INT[] =
    {
        {'\b', {HID_KEY_BACKSPACE, 0}}, // BS Backspace
        {'\t', {HID_KEY_TAB, 0}},       // BS TAB Tab
        {'\n', {HID_KEY_ENTER, 0}},     // LF Enter
        {'\e', {HID_KEY_ESCAPE, 0}},    // Escape key
        {' ', {HID_KEY_SPACE, 0}},
        {'!', {HID_KEY_SHIFT_LEFT, HID_KEY_1, 0}},
        {'"', {HID_KEY_SHIFT_LEFT, HID_KEY_APOSTROPHE, 0}},
        {'#', {HID_KEY_SHIFT_LEFT, HID_KEY_3, 0}},
        {'$', {HID_KEY_SHIFT_LEFT, HID_KEY_4, 0}},
        {'%', {HID_KEY_SHIFT_LEFT, HID_KEY_5, 0}},
        {'&', {HID_KEY_SHIFT_LEFT, HID_KEY_7, 0}},
        {'\'', {HID_KEY_APOSTROPHE, 0}},
        {'(', {HID_KEY_SHIFT_LEFT, HID_KEY_9, 0}},
        {')', {HID_KEY_SHIFT_LEFT, HID_KEY_0, 0}},
        {'*', {HID_KEY_SHIFT_LEFT, HID_KEY_8, 0}},
        {'+', {HID_KEY_SHIFT_LEFT, HID_KEY_EQUAL, 0}},
        {',', {HID_KEY_COMMA, 0}},
        {'-', {HID_KEY_MINUS, 0}},
        {'.', {HID_KEY_PERIOD, 0}},
        {'/', {HID_KEY_SLASH, 0}},
        {'0', {HID_KEY_0, 0}},
        {'1', {HID_KEY_1, 0}},
        {'2', {HID_KEY_2, 0}},
        {'3', {HID_KEY_3, 0}},
        {'4', {HID_KEY_4, 0}},
        {'5', {HID_KEY_5, 0}},
        {'6', {HID_KEY_6, 0}},
        {'7', {HID_KEY_7, 0}},
        {'8', {HID_KEY_8, 0}},
        {'9', {HID_KEY_9, 0}},
        {':', {HID_KEY_SHIFT_LEFT, HID_KEY_SEMICOLON, 0}},
        {';', {HID_KEY_SEMICOLON, 0}},
        {'<', {HID_KEY_SHIFT_LEFT, HID_KEY_COMMA, 0}},
        {'=', {HID_KEY_EQUAL, 0}},
        {'>', {HID_KEY_SHIFT_LEFT, HID_KEY_PERIOD, 0}},
        {'?', {HID_KEY_SHIFT_LEFT, HID_KEY_BRACKET_LEFT, 0}},
        {'@', {HID_KEY_SHIFT_LEFT, HID_KEY_2, 0}},
        {'A', {HID_KEY_SHIFT_LEFT, HID_KEY_A, 0}},
        {'B', {HID_KEY_SHIFT_LEFT, HID_KEY_B, 0}},
        {'C', {HID_KEY_SHIFT_LEFT, HID_KEY_C, 0}},
        {'D', {HID_KEY_SHIFT_LEFT, HID_KEY_D, 0}},
        {'E', {HID_KEY_SHIFT_LEFT, HID_KEY_E, 0}},
        {'F', {HID_KEY_SHIFT_LEFT, HID_KEY_F, 0}},
        {'G', {HID_KEY_SHIFT_LEFT, HID_KEY_G, 0}},
        {'H', {HID_KEY_SHIFT_LEFT, HID_KEY_H, 0}},
        {'I', {HID_KEY_SHIFT_LEFT, HID_KEY_I, 0}},
        {'J', {HID_KEY_SHIFT_LEFT, HID_KEY_J, 0}},
        {'K', {HID_KEY_SHIFT_LEFT, HID_KEY_K, 0}},
        {'L', {HID_KEY_SHIFT_LEFT, HID_KEY_L, 0}},
        {'M', {HID_KEY_SHIFT_LEFT, HID_KEY_M, 0}},
        {'N', {HID_KEY_SHIFT_LEFT, HID_KEY_N, 0}},
        {'O', {HID_KEY_SHIFT_LEFT, HID_KEY_O, 0}},
        {'P', {HID_KEY_SHIFT_LEFT, HID_KEY_P, 0}},
        {'Q', {HID_KEY_SHIFT_LEFT, HID_KEY_Q, 0}},
        {'R', {HID_KEY_SHIFT_LEFT, HID_KEY_R, 0}},
        {'S', {HID_KEY_SHIFT_LEFT, HID_KEY_S, 0}},
        {'T', {HID_KEY_SHIFT_LEFT, HID_KEY_T, 0}},
        {'U', {HID_KEY_SHIFT_LEFT, HID_KEY_U, 0}},
        {'V', {HID_KEY_SHIFT_LEFT, HID_KEY_V, 0}},
        {'W', {HID_KEY_SHIFT_LEFT, HID_KEY_W, 0}},
        {'X', {HID_KEY_SHIFT_LEFT, HID_KEY_X, 0}},
        {'Y', {HID_KEY_SHIFT_LEFT, HID_KEY_Y, 0}},
        {'Z', {HID_KEY_SHIFT_LEFT, HID_KEY_Z, 0}},
        {'[', {HID_KEY_BRACKET_LEFT, 0}},
        {'\\', {HID_KEY_BACKSLASH, 0}},
        {']', {HID_KEY_BRACKET_RIGHT, 0}},
        {'^', {HID_KEY_SHIFT_LEFT, HID_KEY_6, 0}},
        {'_', {HID_KEY_SHIFT_LEFT, HID_KEY_MINUS, 0}},
        {'`', {HID_KEY_GRAVE, 0}},
        {'a', {HID_KEY_A, 0}},
        {'b', {HID_KEY_B, 0}},
        {'c', {HID_KEY_C, 0}},
        {'d', {HID_KEY_D, 0}},
        {'e', {HID_KEY_E, 0}},
        {'f', {HID_KEY_F, 0}},
        {'g', {HID_KEY_G, 0}},
        {'h', {HID_KEY_H, 0}},
        {'i', {HID_KEY_I, 0}},
        {'j', {HID_KEY_J, 0}},
        {'k', {HID_KEY_K, 0}},
        {'l', {HID_KEY_L, 0}},
        {'m', {HID_KEY_M, 0}},
        {'n', {HID_KEY_N, 0}},
        {'o', {HID_KEY_O, 0}},
        {'p', {HID_KEY_P, 0}},
        {'q', {HID_KEY_Q, 0}},
        {'r', {HID_KEY_R, 0}},
        {'s', {HID_KEY_S, 0}},
        {'t', {HID_KEY_T, 0}},
        {'u', {HID_KEY_U, 0}},
        {'v', {HID_KEY_V, 0}},
        {'w', {HID_KEY_W, 0}},
        {'x', {HID_KEY_X, 0}},
        {'y', {HID_KEY_Y, 0}},
        {'z', {HID_KEY_Z, 0}},
        {'{', {HID_KEY_SHIFT_LEFT, HID_KEY_BRACKET_LEFT, 0}},
        {',', {HID_KEY_SHIFT_LEFT, HID_KEY_BACKSLASH, 0}},
        {'}', {HID_KEY_SHIFT_LEFT, HID_KEY_BRACKET_RIGHT, 0}},
        {'~', {HID_KEY_SHIFT_LEFT, HID_KEY_GRAVE, 0}},
        {'|', {HID_KEY_SHIFT_LEFT, HID_KEY_BACKSLASH, 0}},
        {127, {HID_KEY_DELETE, 0}},
        {0x2019, {HID_KEY_ALT_RIGHT, HID_KEY_0, 0}}, // '’'
        {0xa1, {HID_KEY_ALT_RIGHT, HID_KEY_1, 0}},   // '¡'
        {0xb2, {HID_KEY_ALT_RIGHT, HID_KEY_2, 0}},   // '²'
        {0xb3, {HID_KEY_ALT_RIGHT, HID_KEY_3, 0}},   // '³'
        {0xa4, {HID_KEY_ALT_RIGHT, HID_KEY_4, 0}},   // '¤'
        {0x20CA, {HID_KEY_ALT_RIGHT, HID_KEY_5, 0}}, // '€'
        {0xBC, {HID_KEY_ALT_RIGHT, HID_KEY_6, 0}},   // '¼'
        {0xBD, {HID_KEY_ALT_RIGHT, HID_KEY_7, 0}},   // '½'
        {0xBE, {HID_KEY_ALT_RIGHT, HID_KEY_8, 0}},   // '¾'
        {0x2018, {HID_KEY_ALT_RIGHT, HID_KEY_9, 0}}, // '‘'

        {0xA5, {HID_KEY_ALT_RIGHT, HID_KEY_MINUS, 0}},         // '¥'
        {0xD7, {HID_KEY_ALT_RIGHT, HID_KEY_EQUAL, 0}},         // '×'
        {0xE4, {HID_KEY_ALT_RIGHT, HID_KEY_Q, 0}},             // 'ä'
        {0xE5, {HID_KEY_ALT_RIGHT, HID_KEY_W, 0}},             // 'å'
        {0xE9, {HID_KEY_ALT_RIGHT, HID_KEY_E, 0}},             // 'é'
        {0xAE, {HID_KEY_ALT_RIGHT, HID_KEY_R, 0}},             // '®'
        {0xFE, {HID_KEY_ALT_RIGHT, HID_KEY_T, 0}},             // 'þ'
        {0xFC, {HID_KEY_ALT_RIGHT, HID_KEY_Y, 0}},             // 'ü'
        {0xFA, {HID_KEY_ALT_RIGHT, HID_KEY_U, 0}},             // 'ú'
        {0xED, {HID_KEY_ALT_RIGHT, HID_KEY_I, 0}},             // 'í'
        {0xF3, {HID_KEY_ALT_RIGHT, HID_KEY_O, 0}},             // 'ó'
        {0xF6, {HID_KEY_ALT_RIGHT, HID_KEY_P, 0}},             // 'ö'
        {0xAB, {HID_KEY_ALT_RIGHT, HID_KEY_BRACKET_LEFT, 0}},  // '«'
        {0xBB, {HID_KEY_ALT_RIGHT, HID_KEY_BRACKET_RIGHT, 0}}, // '»'
        {0xE1, {HID_KEY_ALT_RIGHT, HID_KEY_A, 0}},             // 'á'
        {0xDF, {HID_KEY_ALT_RIGHT, HID_KEY_S, 0}},             // 'ß'
        {0xF0, {HID_KEY_ALT_RIGHT, HID_KEY_D, 0}},             // 'ð'
        {0xF8, {HID_KEY_ALT_RIGHT, HID_KEY_L, 0}},             // 'ø'
        {0xB6, {HID_KEY_ALT_RIGHT, HID_KEY_SEMICOLON, 0}},     // '¶'
        {0xB4, {HID_KEY_ALT_RIGHT, HID_KEY_APOSTROPHE, 0}},    // '´'
        {0xAC, {HID_KEY_ALT_RIGHT, HID_KEY_BACKSLASH, 0}},     // '¬'

        {0xE6, {HID_KEY_ALT_RIGHT, HID_KEY_Z, 0}},     // 'æ'
        {0xA9, {HID_KEY_ALT_RIGHT, HID_KEY_C, 0}},     // '©'
        {0xF1, {HID_KEY_ALT_RIGHT, HID_KEY_N, 0}},     // 'ñ'
        {0x6D, {HID_KEY_ALT_RIGHT, HID_KEY_M, 0}},     // '®'
        {0xE7, {HID_KEY_ALT_RIGHT, HID_KEY_COMMA, 0}}, // 'ç'
        {0xBF, {HID_KEY_ALT_RIGHT, HID_KEY_SLASH, 0}}, // '¿'
        {0, {0, 0}}                                    // UniCode 0 is the last one in the list

};
