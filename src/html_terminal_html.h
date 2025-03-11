const uint8_t terminal_html[] = R"rawliteral(
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
        <title>WiFi Duck | Terminal</title>

        <link rel="stylesheet" type="text/css" href="style.css">
        <script src="script.js"></script>
        <script src="terminal.js"></script>
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
		<div id="status"></div>
		<main>
			<section>
				<h2>Terminal</h2>
				<div class="row">
					<input list="commands" type="text" class="smooth" id="input">
                      <datalist id="commands">
                        <option value="help">
                        <option value="ram">
                        <option value="version">
                        <option value="settings">
                        <option value="set">
                        <option value="reset">
                        <option value="reboot">
                        <option value="status">
                        <option value="ls">
                        <option value="mem">
                        <option value="cat">
                        <option value="run">
                        <option value="stop">
                        <option value="create">
                        <option value="remove">
                        <option value="rename">
                        <option value="write">
                        <option value="format">
                        <option value="stream">
                        <option value="close">
                        <option value="read">
                    </datalist>
					<button class="primary" id="send">send</button>
					<button class="warn" id="clear">clear</button>
					<button class="white" id="reconnect">reconnect</button>
				</div>
				<div class="row">
					<div id="output" class="terminal"></div>
				</div>
			</section>
		</main>
        <footer>
            This Fork 
            <a href="https://github.com/EmileSpecialProducts/UltraWiFiDuck" target="_blank">Source</a>
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
