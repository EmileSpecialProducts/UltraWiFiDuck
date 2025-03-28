const uint8_t script_js[] = R"rawliteral(
/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

function E(id) {
    return document.getElementById(id);
}

function download_txt(fileName, fileContent) {
    var element = document.createElement('a');
    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(fileContent));
    element.setAttribute('download', fileName);

    element.style.display = 'none';
    document.body.appendChild(element);

    element.click();

    document.body.removeChild(element);
}

function fixFileName(fileName) {
    if (fileName.length > 0) {
        if (fileName[0] != '/') {
            fileName = '/' + fileName;
        }

        fileName = fileName.replace(/ /g, '\-');
    }
    return fileName;
}
function UpdateVersion() {
    fetch("/run?cmd=version")
        .then(response => response.text())
        .then(content => {
            // console.log(content);
            E("version").innerHTML = content;
        })
        .catch(error => {
            console.error('Error:', error);
        });
}


)rawliteral";