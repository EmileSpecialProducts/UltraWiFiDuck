# Ultra WiFi Duck

<p align="center">
<img alt="WiFi Duck Logo" src="web/Under-Construction.png" width="640">
</p>

This project Ultra WiFi Duck and utilizes the native USB/Bluetooth function of ESP32, ESP S2/S3/C3 chip. 
ESP32 S2/S3 can emulate USB devices the ESP32, S3/C3 support Bluetooth . 
It also supports mouse emulation.
It also can be connected to you Wifi network or generate its own access point or connect to you Wifi.

## Install / Flash the ESP32-S2/S3/C3
You can install the software from your browser you will not need knowledge of the ESP programming environment No software development IDE needed 
The install from the [Web Page](https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html) https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html 

You will need to select the Flash size 4/8/16Mb. The ESP32-S2-mini has 4Mb But you will have **2Mb** for scripts, 
But will recommend a ESP32-S3 that has a USB/Bluetooth and COM port for software installation and RGB led.    
You can also add a 2812b led strip up to 144 Leds, and config the GPIO pin from the GUI Settings Page.
## Supported devices 
| Device | USB| Bluetooth | Description |
| ------- | -------| ------- | ----------- |
| `ESP32-S3` | `Yes`| `Yes` | Best device for the job |
| `ESP32-S2` | `Yes`| `No` |  |
| `ESP32-C3` | `No` | `Yes`|  |
| `ESP32` | `No` | `Yes`| Not working yet but compiles  |
| `ESP32-C6` | `No` | `Yes`| Not yet supported as platformIO does not support the device |

---

- [Ultra WiFi Duck](#Ultra-wifi-duck)
  - [About](#about)
  - [Install](#Install)
  - [Usage](#usage)
  - [Scripting](#scripting)
    - [Basics](#basics)
    - [Functions](#functions)
    - [Standard Keys](#standard-keys)
    - [Modifier Keys](#modifier-keys)
    - [Other Keys](#other-keys)
    - [Numpad Keys](#numpad-keys)
    - [Examples](#examples)
  - [CLI Commands](#cli-commands)
    - [General](#general)
    - [LittleFS File Management](#LittleFS-file-management)
  - [How to Debug](#how-to-debug)
  - [Development](#development)
    - [Edit Web Files](#edit-web-files)
    - [Change Keyboard Identifier](#change-keyboard-identifier)
    - [Translate Keyboard Layout](#translate-keyboard-layout)
  - [Disclaimer](#disclaimer)
  - [License](#license)
  - [Credits](#credits)
  - [Support original wifiduck](#support-original-wifiduck)

## About

Ultra WiFi Duck: This open-source project aims to provide a user-friendly tool to learn about keystroke injection attacks and Mouse emulation.  

By emulating a USB/Bluetooth keyboard and mouse, tools like this can gain full access to any computer with a USB/Bluetooth port in a matter of seconds!  
This is made possible by the fact that keyboards are trusted by computers. You can have full control over a computer with just a keyboard.  
A UltraWiFiDuck pretends to be a keyboard to the computer to send keystrokes. 
But unlike a human, it can type hundreds of characters per second. 
By using a simple scripting language, it's easy to make UltraWiFiDuck type whatever you want. 

With the Ultra WiFi Duck, you can simply connect via WiFi to manage all scripts, or connect to your WiFi network
from within a web interface. This means that, unlike other tools, you don't need to install an app, log in, compile or copy scripts to an SD card.  

## Usage

<p align="center">
  <a href="https://www.youtube.com/watch?v=sSJuGXd8QRk">
    <img alt="WiFi Duck Video Thumbnail" src="https://raw.githubusercontent.com/spacehuhn/WiFiDuck/master/img/showcase.gif" width="400">
    <br>
    <b>Watch the full video</b>
  </a>
</p>
1. Install the software on this [Web Page](https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html) 
2. Connect to the open WiFi network `wifiduck` 
3. Open a browser and visit `192.168.4.1`
4. You can add it to your network by the setting page
5. Write, save and run your first Ducky Script

**Help I forgot the password:**

Just flach the ESP from th  [Web Page](https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html).  
If you have further questions, check out the [issue section](https://github.com/EmileSpecialProducts/UltraWiFiDuck/issues).   

## Scripting

### Basics

Key on one line are pressed and released one by one and an <Enter> at the end of the line
Commands are at the begin of a line and are in CAPITOL
To write text, that does not need a enter use the STRING function.


| Example | Explanation |
| ------- | ----------- |
| WINDOWS r | Press the Windows key and then press the r key and release it |
| STRING WINDOWS r | Write WINDOWS r |

### Functions

| Command | Example | Description |
| ------- | ------- | ----------- |
| `REM` | `REM Hello World!` |Comment |
| `DEFAULTDELAY` or `DEFAULT_DELAY` | `DEFAULTDELAY 200` | Time in ms between every command |
| `DELAY` | `DELAY 1000` | Delay in ms |
| `STRING` | `STRING Hello World!` | Types the following string |
| `LOCALE` | `LOCALE DE` | Sets the keyboard layout. [List](#translate-keyboard-layout) |
| `KEYCODE` | `KEYCODE 0x02 0x04` | Types a specific key code (modifier, key1[, ..., key6]) in decimal or hexadecimal |
| `LED` | `LED 40 20 10` |Changes the color of the LED in decimal RGB values (0-255) up to 144 Leds |
| `MOUSE CLICK`| This is give a mouse click|
| `MOUSE 10 10 `| This is move the mouse x y weel pan |
### Standard Keys

| Key |
| --- |
| `a` - `z` |
| `A` - `Z` |
| `0` - `9` |
| `\F1` - `\F24` |
| `\NUM_0` - `\NUM_9` `\NUM_ASTERIX` `\NUM_ENTER` `\NUM_MINUS` `\NUM_DOT` `\NUM_PLUS`  |
| `\MENU` `\APP` `\DELETE` `\HOME` `\ENTER` `\n` `\INSERT` `\PAGEUP` `\PAGEDOWN` `\ARROWUP` `\ARROWDOWN` `\ARROWLEFT` `\ARROWRIGHT`| 
| `\ARROW_U` `\ARROW_D` `\ARROW_L` `\ARROW_R` `\TAB` `\t` `\END` `\ESC` `\ESCAPE` `\SPACE` `\PAUSE` `\BREAK` `\CAPSLOCK` `\NUMLOCK` `\PRINTSCREEN` |
| `\SCROLLLOCK`  `\\` |

### Modifier Keys

| Key |
| --- |
| `\CTRL` `\CONTROL` `\CONTROLLEFT` `\CONTROLRICHT` |
| `\SHIFT` `\SHIFTLEFT` `\SHIFTRICHT` |
| `\ALT` `\ALTLEFT` `\ALTRICHT`|
| `\WINDOWS` `\GUI` `\GUILEFT` `\GUIRICHT` `\WINDOWSLEFT` `\WINDOWSRICHT`|

### Examples

You can find example script in the `payloads` folder 
```
REM Hello World for Windows PCs
DEFAULTDELAY 200
GUI r
STRING notepad
\ENTER
STRING Hello World!
```

```
REM This will lock a PC and display a full screen lock screen 
GUI r
DELAY 1000
STRING https://emilespecialproducts.github.io/UltraWifiDuck/web/lock.htm
\ENTER
DELAY 1000
\F11
```

## CLI Commands

The command line interface or CLI is accessible using a [serial](https://webserial.io/) connection to the ESP (115200 baud, Newline ending) or via the web interface at `192.168.4.1/terminal.html`.  

### General

| Command | Description | Example |
| ------- | ----------- | ------- |
| help | Returns all available commands | `help` |
| ram | Returns available memory in bytes | `ram` |
| version | Returns version number | `version` |
| settings | Returns list of settings | `settings` |
| set -n/ame <value> -v/alue <value> | Sets value of a specific setting | `set ssid "why fight duck"` |
| reset | Resets all settings to their default values | `reset` |
| status | Returns status of i2c connection with Atmega32u4 | `status` |
| run <...> | Starts executing a Ducky script | `run example.txt` |
| stop <...> | Stops executing a Ducky script | `stop example.txt` |

### LittleFS File Management

| Command | Description | Example |
| ------- | ----------- | ------- |
| mem | Returns available, used and free memory of LittleFS in bytes | `mem` |
| format | Formats LittleFS | `format` |
| ls <...> | Returns list of files | `ls /` |
| create <...> | Creates file | `create example.duck` |
| remove <...> | Deletes file | `remove example.duck` |
| cat <...> | Returns content of file | `cat example.duck` |
| rename -fileA,a <value> -fileB,b <value> | Renames file | `rename example.duck example.txt` |
| write -f/ile <value> -c/ontent <value> | Writes (appends) data to file | `write example.txt "Hello World!"` |
| stream <...> | Opens file stream | `stream example.txt` |
| close | Closes file stream | `close` |
| read | Read and return the result from file stream | `read` |

If a stream is open, everything you type (except messages containing exactly `close` or `read`) will be written to the file until you type `close`!  

## How to Debug

You can debug the software when using the OTA version as this will also print all the debug information to the serial port

## Development
To develop you can best use the "esp32-s3-devkitc-8MB-OTA" as this will support USB and Bluetooth 
### Edit Web Files

The file html_xxxxx.h are the webpages that you can edit.
aScript in the background.  

### Translate Keyboard Layout

Currently supported keyboard layouts:
NONE, US , US-INT, BG  

But you can enter the UFT8 characters and they will be typed using the <Alt> and Unicode on the numberpad

LOCALE DE
STRING !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_abcdefghijklmnopqrstuvwxyz{|}~²³äöüÄÖÜß€°§`
ENTER

## Disclaimer

This tool is intended to be used for testing, training, and educational purposes only.  
Never use it to do harm or create damage!  

The continuation of this project counts on you!  

## License

This software is licensed under the MIT License.
See the [license file](LICENSE) for details.  

## Credits

Software libraries used in this project:
  - [Arduino](https://www.arduino.cc)
  - [Neopixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
  - [Dotstar Library](https://github.com/adafruit/Adafruit_DotStar)
  - [AVR, ESP8266 & SAMD Arduino Core](https://github.com/spacehuhn/hardware/tree/master/wifiduck)
  - [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)
  - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
  - [SimpleCLI](https://github.com/spacehuhn/SimpleCLI)

## Original wifiduck
As this is a Fork from [spacehuhn.com](https://spacehuhn.com) [github](https://github.com/spacehuhntech/WiFiDuck)

