const uint8_t error404_html[] = R"rawliteral(
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
        <title>WiFi Duck | 404</title>

        <link rel="stylesheet" type="text/css" href="style.css">
        <script src="script.js"></script>
    </head>
    <body>
        <nav>
            <ul class="menu">
                <li><a href="index.html">WiFi Duck</a></li>
                <li><a href="settings.html">Settings</a></li>
                <li><a href="credits.html">About</a></li>
            </ul>
        </nav>
        <div id="status"></div>
        <main>
            <section>

				<h1>404</h1>
				<p>
				Page not found :(
                </p>
                <a class="primary" href="index.html">Back to Homepage</a>
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