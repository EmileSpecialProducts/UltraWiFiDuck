const uint8_t help_html[] = R"rawliteral(
<!--
    This software is licensed under the MIT License. See the license file for details.
    Source: https://github.com/spacehuhntech/WiFiDuck
-->
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=0.8, minimal-ui">
    <meta name="theme-color" content="#36393E">

    <meta name="description" content="WiFi Duck Help">
    <title>WiFi Duck Help</title>
    <link rel="stylesheet" type="text/css" href="style.css">
    <script src="script.js"></script>
    <script src="help.js"></script>
</head>

<body>
    <nav>
        <ul class="menu">
            <li><a href="index.html">WiFi Duck</a></li>
            <li><a href="settings.html">Settings</a></li>
            <li><a href="help.html">Help</a></li>
            <li><a href="credits.html">About</a></li>
        </ul>
    </nav>
    <main>
        <section>
            <!--<h1>Documentation</h1>-->
            <h2>Scripting</h2>
            <h3>Basics</h3>
            <p>
                Keys are separated by a single space.<br>
                Everything written in a single line gets pressed and released at the same time.<br>
                To write text, use the STRING function.
            </p>
            <table>
                <thead>
                    <tr>
                        <th>Example</th>
                        <th>Explanation</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td>WINDOWS
                            <br> r
                        </td>
                        <td>Type the Windows key and then the r key</td>
                    </tr>
                    <tr>
                        <td>WINDOWS r</td>
                        <td>Press the Windows key and the r key simultaneously</td>
                    </tr>
                    <tr>
                        <td>STRING WINDOWS r</td>
                        <td>Write WINDOWS r</td>
                    </tr>
                </tbody>
            </table>
            <h3>Functions</h3>
            <table id="ducky-functions-table">
                <thead>
                    <tr>
                        <th>Command</th>
                        <th>Example</th>
                        <th>Description</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><code>REM</code></td>
                        <td><code>REM Hello World!</code></td>
                        <td>Comment</td>
                    </tr>
                    <tr>
                        <td><code>DEFAULTDELAY</code> or <code>DEFAULT_DELAY</code></td>
                        <td><code>DEFAULTDELAY 200</code></td>
                        <td>Time in ms between every command</td>
                    </tr>
                    <tr>
                        <td><code>DELAY</code></td>
                        <td><code>DELAY 1000</code></td>
                        <td>Delay in ms</td>
                    </tr>
                    <tr>
                        <td><code>STRING</code></td>
                        <td><code>STRING Hello World!</code></td>
                        <td>Types the following string but no Enter</td>
                    </tr>
                    <tr>
                        <td><code></code></td>
                        <td><code>Hello World!</code></td>
                        <td>Types the following string and will add an Enter</td>
                    </tr>
                    <tr>
                        <td><code>LOCALE</code></td>
                        <td><code>LOCALE US-INT</code></td>
                        <td>Sets the keyboard layout. Available:
                            <code>US</code>,<code>US-INT</code>, <code>FR</code>, <code>DE</code>, <code>BG</code>, <code>ES</code>, <code>NONE</code>,
                        </td>
                    </tr>
                    <tr>
                        <td><code>KEYCODE</code></td>
                        <td><code>KEYCODE 0x02 0x04</code></td>
                        <td>Types a specific key code (modifier, key1[, ..., key6]) in decimal or hexadecimal</td>
                    </tr>
                    <tr>
                        <td><code>LED</code></td>
                        <td><code>LED 255 128 64</code></td>
                        <td>Changes the color of the LEDs in decimal RGB values (0-255)<br>
                            LED 10 10 10 Startled Endled<br>
                            You can connect a led strip up to 144 RGB leds
                        </td>
                    </tr>
                    <tr>
                        <td><code>RESTART</code></td>
                        <td><code>DELAY 10000<br>MOUSE 10 0 <br>RESTART</code></td>
                        <td>This will restart the script and loop this script
                        </td>
                    </tr>
                      <tr>
                        <td><code>ENDSCRIPT</code></td>
                        <td><code>DELAY 1000<br>ENDSCRIPT<br>MOUSE 10 0 <br>RESTART</code></td>
                        <td>This will End the Script at this point 
                        </td>
                    </tr>
                </tbody>
            </table>
            <h3>Standard Keys</h3>
            <table>
                <thead>
                    <tr>
                        <th>Key</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><code>a</code> - <code>z</code> <code>A</code> - <code>Z</code> </td>
                    </tr>
                    <tr>
                        <td><code>0</code> - <code>9</code> <code>\NUM_0</code> - <code>\NUM_9</code>
                            <code>\NUM_ASTERIX</code> <code>\NUM_ENTER</code> <code>\NUM_MINUS</code>
                            <code>\NUM_DOT</code> <code>\NUM_PLUS</code></td>
                    </tr>
                    <tr>
                        <td><code>\MENU</code> <code>\APP</code> <code>\DELETE</code> <code>\HOME</code>
                            <code>\ENTER</code> <code>\n</code> <code>\INSERT</code> <code>\PAGEUP</code>
                            <code>\PAGEDOWN</code> <code>\ARROWUP</code> <code>\ARROWDOWN</code> <code>\ARROWLEFT</code>
                            <code>\ARROWRIGHT</code></td>
                    </tr>
                    <tr>
                        <td><code>\ARROW_U</code> <code>\ARROW_D</code> <code>\ARROW_L</code> <code>\ARROW_R</code>
                            <code>\TAB</code> <code>\t</code> <code>\END</code> <code>\ESC</code> <code>\ESCAPE</code>
                            <code>\SPACE</code> <code>\PAUSE</code> <code>\BREAK</code> 
                            <code>\PRINTSCREEN</code> <code>\SCROLLLOCK</code> <code>\\</code>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <code>\CAPSLOCK</code> <code>\CAPSLOCKON</code> <code>\CAPSLOCKOFF</code>
                            <code>\NUMLOCK</code> <code>\NUMLOCKON</code> <code>\NUMLOCKOFF</code>
                        </td>
                    </tr>

                    <tr>
                        <td><code>\F1</code> - <code>\F24</code></td>
                    </tr>
                </tbody>
            </table>
            <h3>Modifier Keys</h3>
            <table>
                <thead>
                    <tr>
                        <th>Key</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><code>CTRL</code> <code>CONTROL</code> <code>\CONTROLLEFT</code> <code>\CONTROLRICHT</code>
                        </td>
                    </tr>
                    <tr>
                        <td><code>SHIFT</code> <code>\SHIFTLEFT</code> <code>\SHIFTRICHT</code></td>
                    </tr>
                    <tr>
                        <td><code>ALT</code> <code>ALTLEFT</code> <code>ALTRICHT</code></td>
                    </tr>
                    <tr>
                        <td><code>WINDOWS</code> <code>GUI</code> <code>\GUILEFT</code> <code>\GUIRICHT</code>
                            <code>\WINDOWSLEFT</code> <code>\WINDOWSRICHT</code> 
                        </td>
                    </tr>
                </tbody>
            </table>
            <h3>Media Keys</h3>
            <table>
                <thead>
                    <tr>
                        <th>Key</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><code>\MUTE</code> <code>\VOLUMEUP</code> <code>\VOLUMEDOWN</code> <code>\VOLUME+</code> <code>\VOLUME-</code>
                        </td>
                    </tr>
                    <tr>
                        <td><code>\BRIGHT+</code> <code>\BRIGHT-</code></td>
                    </tr>
                    <tr>
                        <td><code>\CALC</code> <code>\WWW</code></td>
                    </tr>
                    <tr>
                        <td>
                            <code>\POWER</code> <code>\SLEEP</code> <code>\WAKE</code>
                        </td>
                    </tr>
                    <tr>
                        <td><code>\OSSLEEP</code> <code>\OSPOWER</code> Will not working on Windows </td>
                    </tr>
                    
                </tbody>
            </table>
            <h3>Mouse</h3>
            <table id="ducky-functions-table">
                <thead>
                    <tr>
                        <th>Command</th>
                        <th>Example</th>
                        <th>Description</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><code>MOUSE </code> or <code>MOVE </code> </td>
                        <td><code>MOUSE 20 -10 </code></td>
                        <td>Moves the mouse 20 to the right and 10 up
                            <br> MOUSE X Y Wheel Pan 
                        </td>
                    </tr>
                    <tr>
                        <td><code>MOUSE CLICK</code></td>
                        <td><code>MOUSE CLICK ALL</code></td>
                        <td>Click the mouse button <br> Options LEFT RIGHT MIDDLE BACKWARD FORWARD ALL </td>
                    </tr>
                    <tr>
                        <td><code>MOUSE PRESS</code> And <code>MOUSE RELEASE</code>  </td>
                        <td><code>MOUSE PRESS ALL</code></td>
                        <td>PRESS/RELEASE the mouse button <br> Options LEFT RIGHT MIDDLE BACKWARD FORWARD ALL </td>
                    </tr>
                    <tr>
                        <td><code>MOUSE DELAY</code> or <code>MOUSE_DELAY</code></td>
                        <td><code>MOUSE DELAY 200</code></td>
                        <td>Time in ms between every mouse command</td>
                    </tr>
                </tbody>
            </table>
            <h3>GPIO pins</h3>
            <table>
                <thead>
                    <tr>
                        <th>The file "gpiolowxx" will be triggerd when the GPIO pin will go low and when relased (high) the file "gpiohixx" will be triggerd <br>
                        So "gpiolow0" is for GPIO0 going low and "gpiohi9" is for GPIO9 going high </th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                    </tr>
                </tbody>
            </table>
        </section>
    </main>
    <footer>
        <p align="center">
        <h4>Buy Me Coffee</h4>
        <a href="https://buymeacoffee.com/emilespecialproducts">
            <img alt="BuymeaCoffee" src="bmc_qr.png">
        </a>
        </p>
        You can find the source of of this software at this github
        <a href="https://github.com/EmileSpecialProducts/UltraWiFiDuck" target="_blank">archive</a>
        .
        <br>
        <span id="version"></span><br>
        <br>
        This is the original
        <a href="https://github.com/spacehuhntech/WiFiDuck" target="_blank">Source</a>
        <br>
        Copyright (c) 2021 Spacehuhn Technologies<br>
        <a href="https://spacehuhn.com" target="_blank">spacehuhn.com</a>
    </footer>
</body>
</html>
)rawliteral";
