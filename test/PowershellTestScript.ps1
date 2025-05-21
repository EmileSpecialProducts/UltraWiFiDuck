For ($i = 0; $i -le 50; $i++) { $a = Invoke-WebRequest -URI http://UltraWiFiDuck.local/index.html ; write-host $i $a.StatusCode $a.RawContentLength }


# write is not working any more.
#Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=write led.txt `"LED 10 10 10`nDELAY 1000`nLED 0 0 0`nDELAY 1000`nRESTART`""
#Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=write mouse.txt `"MOUSE 10 0 `nDELAY 1000`nMOUSE -10 0`nDELAY 1000`nRESTART`""
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=run led.txt"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=run mouse.txt"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=status"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=stop mouse.txt"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=stop led.txt"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=stopall"

Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=reset"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=set channel 2"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=set APssid UltraWIFIDuck"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=set APpassword UltraWIFIDuck"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=set ssid UltraWIFIDuck"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=set password UltraWIFIDuck"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=set RGBLedPin 21"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=set autorun /test"

Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=reboot"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=ls"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=ram"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=version"

Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=ls"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=write test1 `"MOUSE 10 0 `nDELAY 1000`nMOUSE -10 0`nDELAY 1000`nRESTART`""
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=ls"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=rename test1 test3"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=remove test3"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=run /llll"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=mem"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=cat test"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=status"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=settings"

##################################################################################################################################
function ESPSPIFFSuploadfile() {
    param (
        [Parameter(Mandatory = $true)][String] $UploadURL, 
        [Parameter(Mandatory = $true)][String] $File, 
        [Parameter(Mandatory = $false)][String] $Destinaionfilename 
    )
    if ([string]::IsNullOrWhiteSpace($Destinaionfilename)) { $Destinaionfilename = "/$(Split-Path $File -leaf)" }     
    
    $FilePath = Get-Item -Path $File;
    $fileBytes = [System.IO.File]::ReadAllBytes($FilePath);
    $fileEnc = [System.Text.Encoding]::GetEncoding('iso-8859-1').GetString($fileBytes);
    $boundary = [System.Guid]::NewGuid().ToString(); 
    $EOL = "`r`n";

    $bodyLines = ( 
        "--$boundary",
        "Content-Disposition: form-data; name=`"data`"; filename=`"$Destinaionfilename`"",
        "Content-Type: application/octet-stream",
        "",
        $fileEnc,
        "--$boundary", 
        "",
        "$EOL" 
    ) -join $EOL
    Invoke-RestMethod -Uri $UploadURL -Method Post -ContentType "multipart/form-data; boundary=`"$boundary`"" -Body $bodyLines 
}

################################################################################################################################
$URI = "http://ultrawifiduck.local"
# Upload a file
ESPSPIFFSuploadfile "$URI/upload" 'index.js' '/index.js'
ESPSPIFFSuploadfile "$URI/upload" 'index.html' '/index.html'
ESPSPIFFSuploadfile "$URI/upload" 'script.js' '/script.js'
ESPSPIFFSuploadfile "$URI/upload" 'help.html' '/help.html'
ESPSPIFFSuploadfile "$URI/upload" 'help.js' '/help.js'
ESPSPIFFSuploadfile "$URI/upload" 'settings.js' '/settings.js'
ESPSPIFFSuploadfile "$URI/upload" 'settings.html' '/settings.html'
ESPSPIFFSuploadfile "$URI/upload" 'style.css' '/style.css'

Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=remove index.js"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=remove index.html"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=remove script.js"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=remove help.html"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=remove setting.js"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=remove setting.html"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/run?cmd=remove style.css"

Invoke-WebRequest -URI "http://UltraWiFiDuck.local/index.html"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/index.js"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/script.js"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/help.html"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/settings.html"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/settings.js"
Invoke-WebRequest -URI "http://UltraWiFiDuck.local/style.css"

For ($i = 0; $i -le 50; $i++) { 
    $URL="http://UltraWiFiDuck.local";
    $file ="index.html"; $a = Invoke-WebRequest -URI "$URL/$file" ; write-host "$file" $i $a.StatusCode $a.RawContentLength 
    $file ="index.js"; $a = Invoke-WebRequest -URI "$URL/$file" ; write-host "$file" $i $a.StatusCode $a.RawContentLength 
    $file ="script.js"; $a = Invoke-WebRequest -URI "$URL/$file" ; write-host "$file" $i $a.StatusCode $a.RawContentLength 
    $file ="help.html"; $a = Invoke-WebRequest -URI "$URL/$file" ; write-host "$file" $i $a.StatusCode $a.RawContentLength 
    $file ="settings.html"; $a = Invoke-WebRequest -URI "$URL/$file" ; write-host "$file" $i $a.StatusCode $a.RawContentLength 
    $file ="settings.js"; $a = Invoke-WebRequest -URI "$URL/$file" ; write-host "$file" $i $a.StatusCode $a.RawContentLength 
    $file ="style.css"; $a = Invoke-WebRequest -URI "$URL/$file" ; write-host "$file" $i $a.StatusCode $a.RawContentLength 
}