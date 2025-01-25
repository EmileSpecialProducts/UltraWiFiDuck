const uint8_t settings_js[] = R"rawliteral(
/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */
// ===== WebSocket Actions ===== //
function load_settings() {
  ws_send("settings", function(msg) {
    var lines = msg.split(/\n/); 
    
    var APssid = lines[0].split("=")[1];
    var APpassword = lines[1].split("=")[1];
    var channel = lines[2].split("=")[1];
    var ssid = lines[3].split("=")[1];
    var password = lines[4].split("=")[1];
    var autorun = lines[5].split("=")[1];

    E("APssid").innerHTML = APssid;
    E("APpassword").innerHTML = APpassword;
    E("channel").innerHTML = channel;
    E("ssid").innerHTML = ssid;
    E("password").innerHTML = password;
    E("autorun").innerHTML = autorun;
  });
}

function ws_connected() {
  load_settings();
}


// ===== Startup ===== //
window.addEventListener("load", function() {

  E("edit_APssid").onclick = function () {
    var newAPssid = prompt("APSSID (1-32 chars)", E("APssid").innerHTML);

    if (newAPssid) {
      if (newAPssid.length >= 1 && newAPssid.length <= 32) {
        ws_send("set APssid \"" + newAPssid + "\"", function (msg) {
          load_settings();
        });
      } else {
        alert("ERROR: Invalid length");
      }
    }
  };

  E("edit_APpassword").onclick = function () {
    var newAPpassword = prompt("APPassword (8-64 chars)", E("APpassword").innerHTML);

    if (newAPpassword) {
      if (newAPpassword.length >= 8 && newAPpassword.length <= 64)  {
        ws_send("set APpassword \"" + newAPpassword + "\"", function (msg) {
          load_settings();
        });
      } else {
        alert("ERROR: Invalid length");
      }
    } else
    {
       ws_send("set APpassword \"\"", function (msg) {
          load_settings();
          });
    }
  };

  E("edit_channel").onclick = function() {
    var newchannel = prompt("Channel (1-14)", E("channel").innerHTML);

    if (newchannel) {
      if (parseInt(newchannel) >= 1 && parseInt(newchannel) <= 13) {
        ws_send("set channel " + newchannel, function(msg) {
          load_settings();
        });
      } else {
        alert("ERROR: Invalid channel number");
      }
    }
  };

  E("edit_ssid").onclick = function () {
    var newssid = prompt("SSID (0-32 chars)", E("ssid").innerHTML);

    if (newssid) {
      if (newssid.length >= 0 && newssid.length <= 32) {
        ws_send("set ssid \"" + newssid + "\"", function (msg) {
          load_settings();
        });
      } else {
        alert("ERROR: Invalid length");
      }
    } else
    {
       ws_send("set ssid \"\"", function (msg) {
          load_settings();
          });
    }
  };

  E("edit_password").onclick = function () {
    var newpassword = prompt("Password (8-64 chars)", E("password").innerHTML);

    if (newpassword) {
      if (newpassword.length >= 8 && newpassword.length <= 64)  {
        ws_send("set password \"" + newpassword + "\"", function (msg) {
          load_settings();
        });
      } else {
        alert("ERROR: Invalid length");
      }
    } else
    {
       ws_send("set password \"\"", function (msg) {
          load_settings();
          });
    }
  };

  E("disable_autorun").onclick = function() {
    ws_send("set autorun \"\"", function(msg) {
      load_settings();
    });
  };

  E("reset").onclick = function() {
    if (confirm("Reset all settings to default?")) {
      ws_send("reset", function(msg) {
        load_settings();
      });
    }
  };

  ws_init();
}, false);
)rawliteral";