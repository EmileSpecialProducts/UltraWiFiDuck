const uint8_t settings_js[] = R"rawliteral(
/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */
function E(id) {
    return document.getElementById(id);
}

function load_settings() {
    fetch("/run?cmd=settings ")
        .then(response => response.text())
        .then(content => {
            //E("editor").value = content;
            console.log(content);
            var lines = content.split(/\n/);

            var APssid = lines[0].split("=")[1];
            var APpassword = lines[1].split("=")[1];
            var channel = lines[2].split("=")[1];
            var ssid = lines[3].split("=")[1];
            var password = lines[4].split("=")[1];
            var autorun = lines[5].split("=")[1];
            var RGBLedPin = lines[6].split("=")[1];
            var HostName = lines[7].split("=")[1];

            E("APssid").innerHTML = APssid;
            E("APpassword").innerHTML = APpassword;
            E("channel").innerHTML = channel;
            E("ssid").innerHTML = ssid;
            E("password").innerHTML = password;
            E("autorun").innerHTML = autorun;
            E("RGBLedPin").innerHTML = RGBLedPin;
            E("HostName").innerHTML = HostName;
            
        })
        .catch(error => {
            console.error('Error:', error);
        });
        
}



// ===== Startup ===== //
window.addEventListener("load", function () {

  E("edit_HostName").onclick = function () {
        var newHostName = prompt("HostName (1-32 chars)", E("HostName").innerHTML);
        if (newHostName) {
            if (newHostName.length >= 1 && newHostName.length <= 32) {
                fetch("/run?cmd=set HostName " + newHostName )
                    .then(response => response.text())
                    .then(content => {
                        //E("editor").value = content;
                        console.log(content);
                        load_settings();
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
            } else {
                alert("ERROR: Invalid length");
            }
        }
    }

    E("edit_APssid").onclick = function () {
        var newAPssid = prompt("APSSID (1-32 chars)", E("APssid").innerHTML);

        if (newAPssid) {
            if (newAPssid.length >= 1 && newAPssid.length <= 32) {
                fetch("/run?cmd=set APssid " + newAPssid )
                    .then(response => response.text())
                    .then(content => {
                        //E("editor").value = content;
                        console.log(content);
                        load_settings();
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
            } else {
                alert("ERROR: Invalid length");
            }
        }
    }

    E("edit_APpassword").onclick = function () {
        var newAPpassword = prompt("APPassword (8-64 chars)", E("APpassword").innerHTML);
        if (newAPpassword) {
            if (newAPpassword.length >= 8 && newAPpassword.length <= 64) {
                fetch("/run?cmd=set APpassword " + newAPpassword )
                    .then(response => response.text())
                    .then(content => {
                        //E("editor").value = content;
                        console.log(content);
                        load_settings();
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
            } else {
                alert("ERROR: Invalid length");
            }
        } 
    }

    E("edit_channel").onclick = function () {
        var newchannel = prompt("Channel (1-14)", E("channel").innerHTML);
        if (newchannel) {
            if (parseInt(newchannel) >= 1 && parseInt(newchannel) <= 13) {
                fetch("/run?cmd=set channel " + newchannel)
                    .then(response => response.text())
                    .then(content => {
                        //E("editor").value = content;
                        console.log(content);
                        load_settings();
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
            } else {
                alert("ERROR: Invalid channel number");
            }
        }
    }

    E("edit_RGBLedPin").onclick = function () {
        var pin = prompt("RGBLedPin (0-48)", E("RGBLedPin").innerHTML);
        if (pin) {
            if (parseInt(pin) >= 0 && parseInt(pin) <= 48) {
                fetch("/run?cmd=set RGBLedPin " + pin)
                    .then(response => response.text())
                    .then(content => {
                        //E("editor").value = content;
                        console.log(content);
                        load_settings();
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
            } else {
                fetch("/run?cmd=set RGBLedPin ")
                    .then(response => response.text())
                    .then(content => {
                        //E("editor").value = content;
                        console.log(content);
                        load_settings();
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
            }
        } else {
            fetch("/run?cmd=set RGBLedPin ")
                .then(response => response.text())
                .then(content => {
                    //E("editor").value = content;
                    console.log(content);
                    load_settings();
                })
                .catch(error => {
                    console.error('Error:', error);
                });
        }
    }
    E("edit_ssid").onclick = function () {
        var newssid = prompt("SSID (0-32 chars)", E("ssid").innerHTML);
        if (newssid) {
            if (newssid.length >= 0 && newssid.length <= 32) {
                fetch("/run?cmd=set ssid " + newssid)
                    .then(response => response.text())
                    .then(content => {
                        //E("editor").value = content;
                        console.log(content);
                        load_settings();
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
            } else {
                alert("ERROR: Invalid length");
            }
        } 
    }

    E("edit_password").onclick = function () {
        var newpassword = prompt("Password (8-64 chars)", E("password").innerHTML);
        if (newpassword) {
            if (newpassword.length >= 8 && newpassword.length <= 64) {
                fetch("/run?cmd=set password " + newpassword)
                    .then(response => response.text())
                    .then(content => {
                        //E("editor").value = content;
                        console.log(content);
                        load_settings();
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
            } else {
                alert("ERROR: Invalid length");
            }
        } 
    }

    E("disable_autorun").onclick = function () {
        fetch("/run?cmd=set autorun")
            .then(response => response.text())
            .then(content => {
                //E("editor").value = content;
                console.log(content);
                load_settings();
            })
            .catch(error => {
                console.error('Error:', error);
            });
    }

    E("reset").onclick = function () {
        if (confirm("Reset all settings to default?")) {
            fetch("/run?cmd=reset")
                .then(response => response.text())
                .then(content => {
                    //E("editor").value = content;
                    console.log(content);
                    load_settings();
                })
                .catch(error => {
                    console.error('Error:', error);
                });
        }
    }

    function delay(time) {
        return new Promise(resolve => setTimeout(resolve, time));
    }

    E("reboot").onclick = function () {
        if (confirm("Reboot ?")) {
                fetch("/run?cmd=reboot")
                    .then(response => response.text())
                    .then(content => {
                        //E("editor").value = content;
                        console.log(content);
                        delay(10000).then(() => { console.log('ran after 10 seconds passed'); location.reload(); });
                    })
                    .catch(error => {
                        console.error('Error:', error);
                        delay(10000).then(() => { console.log('ran after 10 seconds passed'); location.reload(); });
                    });
            }
        }
    load_settings();
    UpdateVersion();
}, false);
)rawliteral";