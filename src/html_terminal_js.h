const uint8_t terminal_js[] = R"rawliteral(
/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */
// ===== WebSocket Actions ===== //
function ws_connected() { }

// ===== Startup ===== //
function send_input_command()
{
    var input = E("input").value;
    E("output").innerHTML += "# " + input + "<br>";

    E("reconnect").onclick = ws_init;

    ws_send(input, function (msg) {
        log(msg);
        E("output").innerHTML += msg.replace(/\n/g, "<br>");
        E("output").scrollTop = E("output").scrollHeight;
    });
}
window.addEventListener("load", function () {
    E("send").onclick = send_input_command;
    E("input").addEventListener("keyup", ({key}) =>  {
        console.log("Key = " + key);
        if (key === 'Enter' ) {
            send_input_command();
        }
    });  

    E("clear").onclick = function () {
        E("output").innerHTML = "";
    };

    ws_init();
}, false);


)rawliteral";
