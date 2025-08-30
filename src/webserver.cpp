/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#include "webserver.h"

#include <WiFi.h>
#include <esp_wifi.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#ifdef OTA_UPDATE
#include <ArduinoOTA.h>
#endif
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h> // File
#include <LittleFS.h>

#include "config.h"
#include "debug.h"
#include "commandline.h"
#include "settings.h"

#include "webfiles.h"

bool WiFiConected = false;

void reply(AsyncWebServerRequest *request, int code, const char *type, const uint8_t *data, size_t len)
{
    //debugf("reply Len = %d code = %d Type= %s\n ", len, code, type);  
    request->send(code, type, data, len);
#ifdef _NOT_IN_USE_    
        AsyncWebServerResponse *response =
            request->beginResponse(code, type, data, len);

        // response->addHeader("Content-Encoding", "gzip");
        // response->addHeader("Content-Encoding", "7zip");
        //response->addHeader("Access-Control-Allow-Origin","*");    
        request->send(response);
#endif        
}

namespace webserver
{
    // ===== PRIVATE ===== //
    AsyncWebServer server(80);
    DNSServer dnsServer;
    uint32_t WaitTime=0;
    // ===== PUBLIC ===== //
    void begin()
    {
        // Access Point
        WiFi.hostname(settings::getHostName());
        if (strlen(settings::getSSID()) > 0 && ( strlen(settings::getPassword()) >= 8 || strlen(settings::getPassword()) == 0))
        {
            debugf("Connecting to  \"%s\":\"%s\"\n", settings::getSSID(), settings::getPassword());
            WiFi.begin(settings::getSSID(), settings::getPassword());
            for (uint8_t i = 0; i < 20 && !WiFiConected; i++)
            { // wait 10 seconds
                if (WiFi.status() != WL_CONNECTED)
                    delay(500);
                else
                    WiFiConected = true;
            }
            if (!WiFiConected)
                debugf("Connecting to  \"%s\":\"%s\" Failed\n", settings::getSSID(), settings::getPassword());
#if not defined(CONFIG_SOC_BLE_SUPPORTED)
#if not defined(ESP8266)
            esp_wifi_set_ps(WIFI_PS_NONE); // Esp32 enters the power saving mode by default,
#endif
#endif
        }
        if (!WiFiConected)
        {
            // WiFi.mode(WIFI_AP_STA);
            IPAddress apIP(192, 168, 4, 1);
            WiFi.softAP(settings::getAPSSID(), settings::getAPPassword(), settings::getAPChannelNum());
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
            debugf("Started Access Point \"%s\":\"%s\"\n", settings::getAPSSID(), settings::getAPPassword());

            dnsServer.setTTL(300);
            dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

            /* Setup the DNS server redirecting all the domains to the apIP */
            //dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
            //dnsServer->start(DNS_PORT, F("*"), WiFi.softAPIP());
            // This will connect to the UltraWiFiDuck 
            dnsServer.start(53, F("*"), apIP);
        }

        server.onNotFound([](AsyncWebServerRequest *request)
                { 
                    debugf("url NotFound %s , Method =%s\n", request->url().c_str(), request->methodToString());
                    if (request->method() == HTTP_GET)
                    {
                        if (LittleFS.exists(request->url())) // exists will give a error in the error log see: https://github.com/espressif/arduino-esp32/issues/7615
                        {

                            File Fh = LittleFS.open(request->url());
                            int size = Fh.size();
                            Fh.close(); // open close to clear the error
                            if(size == 0) // we can not send a file with 0 length
                                request->send(200, "text/plain", "");
                            else
                                request->send(LittleFS, request->url(), "");
                        }
                        else
                        {
                        if (request->url() == "/favicon.ico")
                            reply(request, 200, "image/x-icon", favicon_ico, sizeof(favicon_ico));
                        else if (request->url() == "/bmc_qr.png")
                                reply(request, 200, "image/x-icon", bmc_qr_png, sizeof(bmc_qr_png));
                        else if (request->url() == "/credits.html")
                                reply(request, 200, "text/html", credits_html, sizeof(credits_html) - 1);
                        else if (request->url() == "/error404.html")
                                reply(request, 404, "text/html", error404_html, sizeof(error404_html) - 1);
                        else if (request->url() == "/index.html")
                                reply(request, 200, "text/html", index_html, sizeof(index_html) - 1);
                        else if (request->url() == "/help.html")
                                reply(request, 200, "text/html", help_html, sizeof(help_html)-1);
                        else if (request->url() == "/help.js")
                                reply(request, 200, "application/javascript", help_js, sizeof(help_js) - 1);
                        else if (request->url() == "/index.js")
                                reply(request, 200, "application/javascript", index_js, sizeof(index_js) - 1);
                        else if (request->url() == "/script.js")
                                reply(request, 200, "application/javascript", script_js, sizeof(script_js) - 1);
                        else if (request->url() == "/settings.html")
                                reply(request, 200, "text/html", settings_html, sizeof(settings_html)-1);
                        else if (request->url() == "/settings.js")
                                reply(request, 200, "application/javascript", settings_js, sizeof(settings_js)-1);
                        else if (request->url() == "/style.css")
                                reply(request, 200, "text/css", style_css, sizeof(style_css)-1);
                        else 
                            {
                                if (WiFiConected)
                                {
                                    request->redirect("/error404.html");
                                } else
                                {   // if AP connected
                                    request->redirect("/index.html");
                                }                            
                            }
                        }
                    }
                    else if (request->method() == HTTP_POST)
                    {
                        reply(request, 404, "text/html", error404_html, sizeof(error404_html) - 1);
                    }
                });
        // Webserver
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->redirect("/index.html"); });

        server.on("/upload", HTTP_POST, 
                [](AsyncWebServerRequest *request)
                  {
                    debugln("File upload completed " + request->url());
                    //request->send(200, "text/plain; chartset=\"UTF-8\"", "File upload completed");
                    //request->send(200);
                    request->redirect("/"); 
                  }, 
                [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
                  {
                    //debugf("Upload[%s]: start=%u, len=%u, final=%d\n", filename.c_str(), index, len, final);
                    if (!index) {
                    request->_tempFile = LittleFS.open("/"+ filename, "w+");
                    }
                    if (len) request->_tempFile.write(data, len);
                    if (final) {
                    request->_tempFile.close();
                    } 
                  }
            );
        server.on("/run", [](AsyncWebServerRequest *request)
                  {
                      static char buffer[2048];
                      String message = "";
                      if (request->hasParam("cmd"))
                      {
                          message = request->getParam("cmd")->value();
                          Commandline((char *)message.c_str(), buffer,sizeof(buffer));
                          request->send(200, "text/plain", buffer);
                      }
                      else
                      {
                          request->send(200, "text/plain", "No cmd");
                      }
                  });

#ifdef OTA_UPDATE

        // Arduino OTA Update
        ArduinoOTA.onStart([]()
                           { debugln("OTA Update Start"); });
        ArduinoOTA.onEnd([]()
                         { debugln("OTA Update End"); });
        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                              {
            debugf("OTA Progress: %02u%%\n", (progress/(total/100)));
            });
        ArduinoOTA.onError([](ota_error_t error)
                {
                if (error == OTA_AUTH_ERROR) debugln("OTA Auth Failed");
                else if (error == OTA_BEGIN_ERROR) debugln("OTA Begin Failed");
                else if (error == OTA_CONNECT_ERROR) debugln("OTAConnect Failed");
                else if (error == OTA_RECEIVE_ERROR) debugln("OTARecieve Failed");
                else if (error == OTA_END_ERROR) debugln("OTA End Failed"); 
                }
        );
        ArduinoOTA.setHostname(settings::getHostName());
        ArduinoOTA.setPassword("WiFi2Duck");
        ArduinoOTA.begin();
#endif
        if (MDNS.begin(settings::getHostName()))
        {
            MDNS.addService("http", "tcp", 80);
        }
        // Start Server
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*"); 
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, PUT, POST, DELETE, HEAD");
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "content-type");
        server.begin();
        DEBUG_PORT.print("You can now connect to http://");
        DEBUG_PORT.print(settings::getHostName());
        DEBUG_PORT.print(".local or http://");
        DEBUG_PORT.println(WiFi.localIP());
        WaitTime = millis();
    }

    void update()
    {
        if (millis() > (WaitTime + (10 * 1000)) )
        {
            WaitTime = millis();
            // debugf("esp_get_free_heap_size = %d , esp_get_free_internal_heap_size = %d \n", esp_get_free_heap_size(), esp_get_free_internal_heap_size());
        }
#ifdef OTA_UPDATE
        ArduinoOTA.handle();
#endif
        if(WiFi.getMode() & WIFI_MODE_AP)
        {
            dnsServer.processNextRequest();
        }
    }
 }