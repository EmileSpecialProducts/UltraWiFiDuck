const uint8_t index_js[] = R"rawliteral(
/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */
// ========== Global Variables ========== //

// ! List of files returned by "ls" command
var file_list = "";
var status_list = "";

// ! Variable to save interval for updating status continously
var status_interval = undefined;

// ! Unsaved content in the editor
var unsaved_changed = false;

// ! Flag if editor has loaded a file yet
var file_opened = false;

// ========== Global Functions ========== //

// ===== Value Getters ===== //
function get_new_filename() {
    return fixFileName(E("newFile").value);
}

function get_editor_filename() {
    return fixFileName(E("editorFile").value);
}

function set_editor_filename(filename) {
    return E("editorFile").value = filename;
}

function get_editor_content() {
    var content = E("editor").value;

    if (!content.endsWith("\n"))
        content = content + "\n";

    return content;
}

var StatusUpdateRunning = false;
function updatestatus()
{
    if (!StatusUpdateRunning)
        Teststatus();
}
function Teststatus()
{
    var isrunning = false;
    fetch("/run?cmd=status")
        .then(response => response.text())
        .then(content => {
            //E("editor").value = content;
            //console.log(content);
            status_list = content;
            
            var table = document.getElementById('file_id');
                for (var r = 0, n = table.rows.length; r < n; r++) {
                    table.rows[r].cells[3].innerHTML = "";
                }
           
            var lines = status_list.split(/\n/);
            for (var i = 0; i < lines.length; i++) {
                var data = lines[i].split(" ");
                var Status = data[0];
                var fileName = data[1];
                var Line = data[2];
                //console.log("Status: " + Status + " fileName: " + fileName + " Line: " + Line);
                if (Status == "running" &&!(Line === undefined) && !(fileName === undefined)) {
                    E("File" + fileName).innerHTML = "Running @ Line = " + Line;
                    isrunning = true; 
                }
            }
            if (isrunning)
            {
                StatusUpdateRunning = true;
                setTimeout(Teststatus, 500);
            }
            else
            {
                StatusUpdateRunning = false;
            }
        })
        .catch(error => {
            console.error('Error:', error);
        });
}
// ! Updates file list and memory usage
function update_file_list() {
    fetch("/run?cmd=ls")
        .then(response => response.text())
        .then(content => {
            //console.log(content);
            file_list = content;

            var lines = file_list.split(/\n/);
            var tableHTML = "<thead>\n";

            tableHTML += "<tr>\n";
            tableHTML += "<th>File</th>\n";
            tableHTML += "<th>Byte</th>\n";
            tableHTML += "<th>Actions</th>\n";
            tableHTML += "<th>Status</th>\n";
            tableHTML += "</tr>\n";
            tableHTML += "</thead>\n";
            tableHTML += "<tbody id=\"file_id\">\n";

            for (var i = 0; i < lines.length; i++) {
                var data = lines[i].split(" ");
                var fileName = data[0];
                var fileSize = data[1];

                if (fileName.length > 0) {
                    if (i == 0 && !file_opened) {
                        read(fileName);
                    }
                    tableHTML += "<tr>\n";
                    tableHTML += "<td onclick=\"read('" + fileName + "')\">" + fileName + "</td>\n";
                    tableHTML += "<td onclick=\"read('" + fileName + "')\">" + fileSize + "</td>\n";
                    tableHTML += "<td>\n";
                    tableHTML += "<button class=\"primary\" onclick=\"read('" + fileName + "')\">Edit</button>\n";
                    tableHTML += "<button class=\"success\" onclick=\"run('" + fileName + "')\">Run</button>\n";
                    tableHTML += "<button class=\"warn\" onclick=\"stop('" + fileName + "')\">Stop</button>\n";
                    tableHTML += "<button class=\"danger\" onclick=\"remove('" + fileName + "')\">Delete</button>\n";
                    tableHTML += "</td>\n";
                    tableHTML += "<td id=\"File/"+ fileName +"\">\n";
                    tableHTML += "</td>\n";
                    tableHTML += "</tr>\n";
                }
            }
            tableHTML += "</tbody>\n";
            E("scriptTable").innerHTML = tableHTML;
            updatestatus();
        })
        .catch(error => {
            console.error('Error:', error);
        });
    
    fetch("/run?cmd=mem")
        .then(response => response.text())
        .then(content => {
            //console.log(content);
            var lines = content.split(/\n/);

            if (lines.length == 1) {
                console.error("Malformed response:");
                console.error(content);
                return;
            }

            var byte = lines[0].split(" ")[0];
            var used = lines[1].split(" ")[0];
            var free = lines[2].split(" ")[0];

            var percent = Math.floor(byte / 100);
            var freepercent = Math.floor(free / percent);

            E("freeMemory").innerHTML = Math.floor(used / 1024) + " Kbytes used, " + Math.floor(free / 1024) + " Kbytes free,  (" + freepercent + "% free)";

        })
        .catch(error => {
            console.error('Error:', error);
        });
}

// ! Format LittleFS
function format() {
    if (confirm("Format LittleFS? This will delete all scripts!")) {
        fetch("/run?cmd=format" )
            .then(response => response.text())
            .then(content => {
                //E("editor").value = content;
                console.log(content);
            })
            .catch(error => {
                console.error('Error:', error);
            });
        alert("Formatting will take a minute.\nYou have to reconnect afterwards.");
    }
}

// ! Run script
function run(fileName) {
    fetch("/run?cmd=run " + fixFileName(fileName) + "")
        .then(response => response.text())
        .then(content => {
            //E("editor").value = content;
            // console.log(content);
            setTimeout(updatestatus, 500);
        })
        .catch(error => {
            console.error('Error:', error);
        });
   
}

// ! Stop running specific script
function stop(fileName) {
    fetch("/run?cmd=stop " + fixFileName(fileName) +"" )
        .then(response => response.text())
        .then(content => {
            //E("editor").value = content;
            //console.log(content);
            setTimeout(updatestatus, 500);
        })
        .catch(error => {
            console.error('Error:', error);
        });
}

// ! Stop running all scripts
function stopAll() {
    fetch("/run?cmd=stopall")
        .then(response => response.text())
        .then(content => {
            //E("editor").value = content;
            //console.log(content);
        })
        .catch(error => {
            console.error('Error:', error);
        });
}


// ! Open file
function read(fileName) {
    fileName = fixFileName(fileName);
    set_editor_filename(fileName);
    fetch(fileName)
        .then(response => response.text())
        .then(content => {
            E("editor").value = content;
            //console.log(content);
        })
        .catch(error => {
            console.error('Error:', error);
        });
    file_opened = true;
}

// ! Create a new file
function create(fileName) {
    fileName = fixFileName(fileName);
    console.log("create " + fileName);
    if (file_list.includes(fileName.substring(1) +" ")) {
        set_editor_filename(fileName);
        read(fileName);
        console.log("create ReadFile:" + fileName);
    } else {
        write(fileName, "");
        set_editor_filename(fileName);
        E("editor").value = "";
    }
}

// ! Delete a file
function remove(fileName) {
    if (confirm("This will delete File" + fileName)) {
        fetch("/run?cmd=remove " + fileName)
            .then(response => response.text())
            .then(content => {
                console.log("Remove " + content);
            })
            .catch(error => {
                console.error('Error:', error);
            });
        update_file_list();
        unsaved_changed = true;
    }
}

function autorun(fileName) {
    fetch("/run?cmd=set autorun " + fileName)
        .then(response => response.text())
        .then(content => {
            console.log("set autorun " + content);
        })
        .catch(error => {
            console.error('Error:', error);
        });


}

// ! Write content to file
function write(fileName, content) {
    fileName = fixFileName(fileName);
    console.log("Write content.length= " + content.length)
    if (content.length == 0) { // As we can not send a file that has 0 length 
        fetch("/run?cmd=create " + fileName)
            .then(response => response.text())
            .then(content => {
                console.log("create: " + content);
            })
            .catch(error => {
                console.error('Error:', error);
            });
    }
    else {
        const formData = new FormData();
        const blob = new Blob([content], { type: 'application/octet-stream' });
        formData.append('file', blob, fileName);
        const request = new XMLHttpRequest();
        request.open('POST', '/upload');
        request.send(formData);
    }
    update_file_list();
}

// ! Save file that is currently open in the editor
function save() {
    write(get_editor_filename(), get_editor_content());
    unsaved_changed = false;
    E("editorinfo").innerHTML = "saved";
    update_file_list();
}


// ========== Startup ========== //
window.addEventListener("load", function () {
    E("scriptsReload").onclick = update_file_list;
    E("format").onclick = format;
    E("stopall").onclick = stopAll;

    E("editorReload").onclick = function () {
        read(get_editor_filename());
    };

    E("editorSave").onclick = save;

    E("editorDelete").onclick = function () {
        if (confirm("Delete " + get_editor_filename() + "?")) {
            remove(get_editor_filename());
        }
    };

    E("editorDownload").onclick = function () {
        download_txt(get_editor_filename(), get_editor_content());
    };

    E("editorStop").onclick = function () {
        stop(get_editor_filename());
        //stop();
    }

    E("editorRun").onclick = function () {
        if (unsaved_changed) {
            save();
        }
        run(get_editor_filename());
    };

    E("editor").onkeyup = function () {
        unsaved_changed = true;
        E("editorinfo").innerHTML = "unsaved changes";
    }

    E("editorAutorun").onclick = function () {
        if (confirm("Run this script automatically on startup?\nYou can disable it in the settings."))
            autorun(get_editor_filename());
    }


    UpdateVersion();
    update_file_list();
    document.addEventListener('keydown', e => {
        if (e.ctrlKey && e.key === 's') {
            // Prevent the Save dialog to open
            e.preventDefault();
            save();
            //console.log('CTRL + S');
        }
    });
    updatestatus();
}, false);
)rawliteral";