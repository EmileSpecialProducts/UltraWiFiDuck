const uint8_t credits_html[] = R"rawliteral(
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

  <meta name="description" content="Ultra WiFi Duck">
  <title>Ultra WiFi Duck | About</title>

  <link rel="stylesheet" type="text/css" href="style.css">
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
  <div id="status"></div>
  <main>
    <section>
      <h1>Disclaimer</h1>
      <p>
        This tool is intended to be used for testing, training, and educational purposes only.<br>
        Never use it to do harm or create damage!<br>
        <br>
        The continuation of this project counts on you!
      </p>
    </section>
    <section>
      <h1>License</h1>
      <p>
        MIT License<br>
        Copyright (c) 2021 Spacehuhn Technologies<br>
        <br>
        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:<br>
        <br>
        The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.<br>
        <br>
        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
      </p>
    </section>
    <section>
      <h1>Credits</h1>
      <p>
        Other software used for this project:<br>
        - <a href="https://www.arduino.cc" target="_blank">Arduino</a><br>
        - <a href="https://github.com/adafruit/Adafruit_NeoPixel" target="_blank">Neopixel Library</a><br>
        - <a href="https://github.com/spacehuhn/hardware/tree/master/wifiduck" target="_blank">AVR, ESP8266 & SAMD Arduino Core</a><br>
        - <a href="https://github.com/me-no-dev/ESPAsyncTCP" target="_blank">ESPAsyncTCP</a><br>
        - <a href="https://github.com/me-no-dev/ESPAsyncWebServer" target="_blank">ESPAsyncWebServer</a><br>
        - <a href="https://github.com/spacehuhn/SimpleCLI" target="_blank">SimpleCLI</a>
      </p>
    </section>
    <section>
      <h1>Thanks</h1>
      <p>
        Thanks to everyone that helped making this project reality, especially:<br>
        - <a href="https://github.com/EmileSpecialProducts" target="_blank">EmileSpecialProducts</a> adding the Web Software Instalation,Bluetooth, GPIO Scripts, Mouse, MultieScriptS, Custom HTML Pages,Powershell<br>
        - <a href="https://deantonious.es" target="_blank">deantonious</a> for helping to design and improve the user experience<br>
        - <a href="youtube.com/seytonic" target="_blank">Seytonic</a> for educating people about the topic<br>
        - <a href="https://dstike.com/" target="_blank">Travis Lin</a> for creating, selling and financially supporting us with custom made hardware<br>
        - and YOU for using it!
      </p>
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