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
    </head>
    <body>
        <nav>
            <ul class="menu">
                <li><a href="index.html">WiFi Duck</a></li>
                <li><a href="settings.html">Settings</a></li>
                <li><a href="terminal.html">Terminal</a></li>
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
                            <td>Types the following string</td>
                        </tr>
                        <tr>
                            <td><code>REPEAT</code> or <code>REPLAY</code></td>
                            <td><code>REPEAT 3</code></td>
                            <td>Repeats the last command n times</td>
                        </tr>
                        <tr>
                            <td><code>LOCALE</code></td>
                            <td><code>LOCALE DE</code></td>
                            <td>Sets the keyboard layout. Available: <code>DE</code>, <code>GB</code>, <code>US</code>, <code>ES</code>, <code>FR</code>, <code>DK</code>, <code>RU</code>, <code>BE</code>, <code>PT</code>, <code>IT</code>, <code>SK</code>, <code>CZ</code>, <code>SI</code>, <code>BG</code>, <code>CA-FR</code>, <code>CH-DE</code>, <code>CH-FR</code>, <code>HU</code>
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
                            You can connect a led strip up to 144 RGB leds
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
                            <td><code>a</code> - <code>z</code></td>
                        </tr>
                        <tr>
                            <td><code>A</code> - <code>Z</code></td>
                        </tr>
                        <tr>
                            <td><code>0</code> - <code>9</code></td>
                        </tr>
                        <tr>
                            <td><code>F1</code> - <code>F12</code></td>
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
                            <td><code>CTRL</code> or <code>CONTROL</code></td>
                        </tr>
                        <tr>
                            <td><code>SHIFT</code></td>
                        </tr>
                        <tr>
                            <td><code>ALT</code></td>
                        </tr>
                        <tr>
                            <td><code>WINDOWS</code> or <code>GUI</code></td>
                        </tr>
                    </tbody>
                </table>
                <h3>Other Keys</h3>
                <table>
                    <thead>
                        <tr>
                            <th>Key</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td><code>ENTER</code></td>
                        </tr>
                        <tr>
                            <td><code>MENU</code> or <code>APP</code></td>
                        </tr>
                        <tr>
                            <td><code>DELETE</code></td>
                        </tr>
                        <tr>
                            <td><code>HOME</code></td>
                        </tr>
                        <tr>
                            <td><code>INSERT</code></td>
                        </tr>
                        <tr>
                            <td><code>PAGEUP</code></td>
                        </tr>
                        <tr>
                            <td><code>PAGEDOWN</code></td>
                        </tr>
                        <tr>
                            <td><code>UP</code> or <code>UPARROW</code></td>
                        </tr>
                        <tr>
                            <td><code>DOWN</code> or <code>DOWNARROW</code></td>
                        </tr>
                        <tr>
                            <td><code>LEFT</code> or <code>LEFTARROW</code></td>
                        </tr>
                        <tr>
                            <td><code>RIGHT</code> or <code>RIGHTARROW</code></td>
                        </tr>
                        <tr>
                            <td><code>TAB</code></td>
                        </tr>
                        <tr>
                            <td><code>END</code></td>
                        </tr>
                        <tr>
                            <td><code>ESC</code> or <code>ESCAPE</code></td>
                        </tr>
                        <tr>
                            <td><code>SPACE</code></td>
                        </tr>
                        <tr>
                            <td><code>PAUSE or BREAK</code></td>
                        </tr>
                        <tr>
                            <td><code>CAPSLOCK</code></td>
                        </tr>
                        <tr>
                            <td><code>NUMLOCK</code></td>
                        </tr>
                        <tr>
                            <td><code>PRINTSCREEN</code></td>
                        </tr>
                        <tr>
                            <td><code>SCROLLLOCK</code></td>
                        </tr>
                    </tbody>
                </table>
                <h3>Numpad Keys</h3>
                <table>
                    <thead>
                        <tr>
                            <th>Key</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td><code>NUM_0</code> - <code>NUM_9</code></td>
                        </tr>
                        <tr>
                            <td><code>NUM_ASTERIX</code></td>
                        </tr>
                        <tr>
                            <td><code>NUM_ENTER</code></td>
                        </tr>
                        <tr>
                            <td><code>NUM_MINUS</code></td>
                        </tr>
                        <tr>
                            <td><code>NUM_DOT</code></td>
                        </tr>
                        <tr>
                            <td><code>NUM_PLUS</code></td>
                        </tr>
                    </tbody>
                </table>
            </section>
        </main>
        <footer>
				This Fork 
				<a href="https://github.com/EmileSpecialProducts/UltraWifiDuck" target="_blank">Source</a>
				you can find.
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
