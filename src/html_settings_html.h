const uint8_t settings_html[] = R"rawliteral(
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

    <meta name="description" content="WiFi Duck">
    <title>WiFi Duck | Settings</title>

    <link rel="stylesheet" type="text/css" href="style.css">
    <script src="script.js"></script>
    <script src="settings.js"></script>
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
            <h1>Settings</h1>
            <p>Reboot the device to apply new settings.</p>
            <table>
                <tr id="edit_HostName">
                    <td>Hostname:</td>
                    <td id="HostName"></td>
                    <td><button class="primary">edit</button></td>
                </tr>
                <tr id="edit_APssid">
                    <td>APSSID:</td>
                    <td id="APssid"></td>
                    <td><button class="primary">edit</button></td>
                </tr>
                <tr id="edit_APpassword">
                    <td>APPassword:</td>
                    <td id="APpassword"></td>
                    <td><button class="primary">edit</button></td>
                </tr>
                <tr id="edit_channel">
                    <td>Channel:</td>
                    <td id="channel"></td>
                    <td><button class="primary">edit</button></td>
                </tr>
                <tr id="edit_ssid">
                    <td>SSID:</td>
                    <td id="ssid"></td>
                    <td><button class="primary">edit</button></td>
                </tr>
                <tr id="edit_password">
                    <td>Password:</td>
                    <td id="password"></td>
                    <td><button class="primary">edit</button></td>
                </tr>
                <tr id="disable_autorun">
                    <td>Autorun Script:</td>
                    <td id="autorun"></td>
                    <td><button class="warn">disable</button></td>
                </tr>
                <tr id="edit_RGBLedPin">
                    <td>RGBLedPin:</td>
                    <td id="RGBLedPin"></td>
                    <td><button class="primary">edit</button></td>
                </tr>
            </table>
            <button class="danger" id="reset">Reset settings</button>
            <button class="danger" id="reboot">Reboot</button>
        </section>
        <section>
            <h1>Update</h1>
            <p>
                Go to <a href="https://emilespecialproducts.github.io/UltraWiFiDuck/upload.html">UltraWifiDuck</a>
                to upload the Softwate.
            </p>
            <p>
                This fork was based on the <a href="https://wifiduck.com">wifiduck.com</a>
                The upload is changed to have more script space<br>
            </p>
        </section>
        <footer>
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