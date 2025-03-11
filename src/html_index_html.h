const uint8_t index_html[] = R"rawliteral(
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
        <title>WiFi Duck</title>

        <link rel="stylesheet" type="text/css" href="style.css">
        <script src="script.js"></script>
        <script src="index.js"></script>
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
                <h1>Status</h1>
                <div class="row">
                    <p><b>Storage: </b><span id="freeMemory">-</span></p>
                    <button class="danger" id="format">format</button>
                    <button class="warn" id="stop">stop</button>
                    <button class="white" id="reconnect">reconnect</button>
                </div>
            </section>
            <section>
                <h1>Scripts <a class="reload" id="scriptsReload">&#x21bb;</a></h1>
                <table class="table" id="scriptTable"></table>
                <div class="row">
                    <input placeholder="Filename /<name>" type="text" class="smooth" value="/" id="newFile"/>
                    <button class="success" onclick="create(get_new_filename())">create</button>
                </div>
            </section>
            <section>
                <h1>Editor <a class="reload" id="editorReload">&#x21bb;</a></h1>
                <div class="row">
                    <input placeholder="Filename /<name>" type="text" class="smooth" value="/" id="editorFile">
                    <button class="danger" id="editorDelete">delete</button>
                    <button class="primary" id="editorDownload">download</button>
                    <button class="primary" id="editorAutorun">Enable autorun</button>
                </div>
                <div class="row">
                    <textarea class="smooth" id="editor"></textarea>
                </div>
                <div class="row">
                    <div class="debugger">
                        Output: <span id="editorinfo">saved</span>
                    </div>
                </div>
                <div class="row">
                    <div id="editor-primary-buttons">
                        <button class="success" id="editorSave">save</button>
                        <button class="warn" id="editorRun">run</button>
                        <button class="danger" id="editorStop">stop</button>
                    </div>
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
