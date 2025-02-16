# Ultra WiFi Duck

<p align="center">
<img alt="WiFi Duck Logo" src="web/Under-Construction.png" width="640">
</p>

<p align="center">
<img alt="WiFi Duck Logo" src="img/thumbnail.jpg" width="640">
</p>

This project Ultra WiFi Duck and utilizes the native USB/Bluetooth function of ESP32, ESP S2/S3/C3 chip. 
ESP32 S2/S3 can emulate USB devices the ESP32, S3/C3 support Bluetooth . 
It also supports mouse emulation.
It also can be connected to you Wifi network or generate its own access point or connect to you Wifi.


## Install / Flash the ESP32-S2/S3

You can install the software from your browser you will not need knowledge of the ESP programming environment No software development IDE needed 
The install from the [Web Page](https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html) https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html 


You will need to select the Flash size 4/8/16Mb. The ESP32-S2-mini has 4Mb But you will have **2Mb** for scripts, 

But will recommend a ESP32-S3 that has a USB/Bluetooth and COM port for software installation and RGB led.    

You can also add a 2812b led strip up to 144 Leds, and config the GPIO pin from the GUI Settings Page.
  

---

- [Ultra WiFi Duck](#Ultra-wifi-duck)
  - [About](#about)
  - [Install](#Install)
  - [Usage](#usage)
  - [Flash ESP32 S2/S3](#flash-esp32-s2s3)
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


Ultra WiFi Duck: This open-source project aims to provide a user-friendly tool to learn about keystroke injection attacks and 'BadUSBs'.  

By emulating a USB/Bluetooth keyboard and mouse, tools like this can gain full access to any computer with a USB/Bluetooth port in a matter of seconds!  
This is made possible by the fact that keyboards are trusted by computers. You can have full control over a computer with just a keyboard.  
A BadUSB pretends to be a keyboard to the computer to send keystrokes. 
But unlike a human, it can type hundreds of characters per second. 
By using a simple scripting language, it's easy to make BadUSBs type whatever you want. 

With the Ultra WiFi Duck, you can simply connect via WiFi to manage all scripts, or connect to your WiFi network
from within a web interface. This means that, unlike other BadUSBs, you don't need to install an app, log in, compile or copy scripts to an SD card.  

## Usage

<p align="center">
  <a href="https://www.youtube.com/watch?v=sSJuGXd8QRk">
    <img alt="WiFi Duck Video Thumbnail" src="https://raw.githubusercontent.com/spacehuhn/WiFiDuck/master/img/showcase.gif" width="400">
    <br>
    <b>Watch the full video</b>
  </a>
</p>

1. Plug in your WiFi Duck
2. Connect to the WiFi network `wifiduck` with the password `wifiduck`
3. Open a browser and visit `192.168.4.1`
4. Write, save and run your first Ducky Script
5. [Recommended] Open `Settings` (top right corner) and update SSID and password

**Help I forgot the password:**

Just flach the ESP from th  [Web Page](https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html).  

If you have further questions, check out the [issue section](https://github.com/EmileSpecialProducts/UltraWiFiDuck/issues).   

## Flash ESP32 S2/S3/C3

The install from the [Web Page](https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html) https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html 

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
| `\F1` - `\F12` |

### Modifier Keys

| Key |
| --- |
| `\CTRL` or `\CONTROL` |
| `\SHIFT` |
| `\ALT` |
| `\WINDOWS` or `\GUI` |

### Other Keys

| Key |
| --- |
| `\ENTER` |
| `\MENU` or `\APP`|
| `\DELETE` |
| `\HOME` |
| `\INSERT` |
| `\PAGEUP` |
| `\PAGEDOWN` |
| `ARROWUP` |
| `ARROWDOWN` |
| `ARROWLEFT` |
| `ARROWRIGHT` |
| `TAB` |
| `END` |
| `ESC` or `ESCAPE` |
| `SPACE` |
| `PAUSE or BREAK` |
| `CAPSLOCK` |
| `NUMLOCK` |
| `PRINTSCREEN` |
| `SCROLLLOCK` |

### Numpad Keys

| Key |
| --- |
| `NUM_0` - `NUM_9` |
| `NUM_ASTERIX` |
| `NUM_ENTER` |
| `NUM_MINUS` |
| `NUM_DOT` |
| `NUM_PLUS` |

### Examples

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

The command line interface or CLI is accessible using a serial connection to the ESP (115200 baud, Newline ending) or via the web interface at `192.168.4.1/terminal.html`.  

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

The original debug module doesn't work right now.
To debug, please use `ESP_LOGE` to display information via the COM port

## Development

### Edit Web Files

If you would like to modify the web interface, you can!  
The `web/` folder contains all `.html`, `.css`, `.js` files.  
You can edit and test them locally as long as you're connected to the WiFi Duck
network thanks to the websocket connection handled by JavaScript in the background.  

### Translate Keyboard Layout

Currently supported keyboard layouts:
NONE, US , US-INT, BG  

But you can enter the UFT8 characters and they will be typed using the <Alt> and Unicode on the numberpad

LOCALE DE
STRING !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_abcdefghijklmnopqrstuvwxyz{|}~²³äöüÄÖÜß€°§`
ENTER
```
10. Add a link to your layout to [README](README.md), to [web/index.html](web/index.html) and please feel free to improve this tutorial to help future translators!
11. [Create a Pull Request](https://help.github.com/en/articles/creating-a-pull-request)

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

## Support original wifiduck

Hey, do you like this kind of project?  
It took a huge amount of effort to create!  

To make sure we can keep working on free and open-source projects like this,  
**please consider becoming a [:heart: Sponsor](https://github.com/sponsors/spacehuhntech) or support us via [:coffee: Ko-fi](https://ko-fi.com/spacehuhn).**  

Visit [spacehuhn.com](https://spacehuhn.com) to learn more about us. :chicken:

<a href='https://ko-fi.com/G2G75FA4V' target='_blank'><img height='36' style='border:0px;height:36px;' src='https://cdn.ko-fi.com/cdn/kofi2.png?v=3' border='0' alt='Buy Me a Coffee at ko-fi.com' /></a>
