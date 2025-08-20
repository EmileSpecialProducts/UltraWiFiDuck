rem Download File
curl -o index.html http://UltraWiFiDuck.local/index.html

rem this will get the current settings
curl http://UltraWiFiDuck.local/Settings.txt

rem  set the RGBLedPin will be active after reboot
curl "http://UltraWiFiDuck.local/run?cmd=set%20RGBLedPin%209"
curl "http://UltraWiFiDuck.local/run?cmd=set%20RGBLedPin%2048"

rem Upload text to file test123.txt
curl -X POST -F "data=$(printf "GUI r\nnotepad\nHello");filename=test123.txt;type=application/octet-stream" http://UltraWiFiDuck.local/upload

rem Upload text to file test123.txt
printf "LED 10 10 10\n" >test.txt
printf "LED 0 10 0\n" >>test.txt
curl -X POST -F "data=$(cat test.txt);filename=test123.txt;type=application/octet-stream" http://UltraWiFiDuck.local/upload
rem run the test123.txt script
curl -X POST "http://UltraWiFiDuck.local/run?cmd=run%20test123.txt"

rem rename test123.txt to test.txt
curl -X POST "http://UltraWiFiDuck.local/run?cmd=ls"
curl -X POST "http://UltraWiFiDuck.local/run?cmd=rename%20test123.txt%20test.txt"
curl -X POST "http://UltraWiFiDuck.local/run?cmd=ls"


rem Upcurl -X POST -F "data=$(printf "GUI r\nnotepad\nHello");filename=test123.txt;type=application/octet-stream" http://UltraWiFiDuck.local/upload

rem load text to file Slow.txt
printf "DELAY 5000\n" >Slow.txt
printf "DELAY 5000\n" >>Slow.txt
printf "DELAY 5000\n" >>Slow.txt
printf "DELAY 5000\n" >>Slow.txt
printf "DELAY 5000\n" >>Slow.txt
printf "LED 0 10 0\n" >>Slow.txt

rem Upload the file
curl -X POST -F "data=$(cat Slow.txt);filename=slow.txt;type=application/octet-stream" http://UltraWiFiDuck.local/upload
rem run the test123.txt script
curl -X POST "http://UltraWiFiDuck.local/run?cmd=run%20slow.txt"
rem status
curl -X POST "http://UltraWiFiDuck.local/run?cmd=status"
rem this will stop the script slow.txt
curl -X POST "http://UltraWiFiDuck.local/run?cmd=stop%20slow.txt"
rem status
curl -X POST "http://UltraWiFiDuck.local/run?cmd=status"

rem status
curl -X POST "http://UltraWiFiDuck.local/run?cmd=status"
rem ls the files
curl -X POST "http://UltraWiFiDuck.local/run?cmd=ls"
rem get the ram space
curl -X POST "http://UltraWiFiDuck.local/run?cmd=ram"
rem get the Versions
curl -X POST "http://UltraWiFiDuck.local/run?cmd=version"
rem Reboot the ESP32
curl -X POST "http://UltraWiFiDuck.local/run?cmd=reboot"

rem test the responce code
curl -o /dev/null -s -w "%{http_code}\n" -X GET "http://UltraWiFiDuck.local/index.html"

rem this will remove the files from littlefs but the files will load from application flash memory
curl -X POST "http://UltraWiFiDuck.local/run?cmd=remove%20index.js"
curl -X POST "http://UltraWiFiDuck.local/run?cmd=remove%20index.html"
curl -X POST "http://UltraWiFiDuck.local/run?cmd=remove%20script.js"
curl -X POST "http://UltraWiFiDuck.local/run?cmd=remove%20help.html"
curl -X POST "http://UltraWiFiDuck.local/run?cmd=remove%20setting.js"
curl -X POST "http://UltraWiFiDuck.local/run?cmd=remove%20setting.html"
curl -X POST "http://UltraWiFiDuck.local/run?cmd=remove%20style.css"
