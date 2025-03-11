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
#include "cli.h"
#include "settings.h"

#include "webfiles.h"
bool WiFiConected = false;

void reply(AsyncWebServerRequest *request, int code, const char *type, const uint8_t *data, size_t len)
{
    debugf("reply Len = %d code = %d Type= %s\n ", len, code, type);
        request->send(code, type, data, len);
        /*
        AsyncWebServerResponse *response =
            request->beginResponse(code, type, data, len);

        // response->addHeader("Content-Encoding", "gzip");
        // response->addHeader("Content-Encoding", "7zip");
        request->send(response);
        */
}
namespace webserver
{
    // ===== PRIVATE ===== //
    AsyncWebServer server(80);
    AsyncWebSocket ws("/ws");
    AsyncEventSource events("/events");

    AsyncWebSocketClient *currentClient{nullptr};
    DNSServer dnsServer;
    uint32_t WaitTime=0;

    void wsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
    {
        if (type == WS_EVT_CONNECT)
        {
            debugf("WS Client connected %u\n", client->id());
        }

        else if (type == WS_EVT_DISCONNECT)
        {
            debugf("WS Client disconnected %u\n", client->id());
        }

        else if (type == WS_EVT_ERROR)
        {
            debugf("WS Client %u error(%u): %s\n", client->id(), *((uint16_t *)arg), (char *)data);
        }

        else if (type == WS_EVT_PONG)
        {
            debugf("PONG %u\n", client->id());
        }

        else if (type == WS_EVT_DATA)
        {
            AwsFrameInfo *info = (AwsFrameInfo *)arg;

            if (info->opcode == WS_TEXT)
            {
                char *msg = (char *)data;
                msg[len] = 0;

                //debugf("Message from %u [%llu byte]=%s\n", client->id(), info->len, msg);

                currentClient = client;
                cli::parse(msg, [](const char *str)
                           {
                    webserver::send(str);
                    debugf("send(%s)\n", str); }, false);
                currentClient = nullptr;
            }
        }
    }

    // ===== PUBLIC ===== //
    void begin()
    {
        // Access Point
        WiFi.hostname(HOSTNAME);
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
            // dnsServer.start(53, URL, apIP);

            /* Setup the DNS server redirecting all the domains to the apIP */
            //dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
            //dnsServer->start(DNS_PORT, F("*"), WiFi.softAPIP());
            // This will connect to the UltraWiFiDuck 
            dnsServer.start(53, F("*"), apIP);
        }

        server.onNotFound([](AsyncWebServerRequest *request)
                { 
                    debugf("url NotFound %s , Method =%s\n", request->url().c_str(), request->methodToString());
                    if (LittleFS.exists( request->url()) )
                    {
                        request->send(LittleFS, request->url(), String(), false);
                    }
                    else
                    {
                        if(request->url() == "/favicon.ico" )
                                reply(request, 200, "image/x-icon", favicon_ico, sizeof(favicon_ico));
                        else if (request->url() == "/credits.html")
                                reply(request, 200, "text/html", credits_html, sizeof(credits_html) - 1);
                        else if (request->url() == "/error404.html")
                                reply(request, 404, "text/html", error404_html, sizeof(error404_html) - 1);
                        else if (request->url() == "/index.html")
                                reply(request, 200, "text/html", index_html, sizeof(index_html) - 1);
                        else if (request->url() == "/help.html")
                                reply(request, 200, "text/html", help_html, sizeof(help_html)-1);
                        else if (request->url() == "/index.js")
                                reply(request, 200, "application/javascript", index_js, sizeof(index_js)-1);
                        else if (request->url() == "/script.js")
                                reply(request, 200, "application/javascript", script_js, sizeof(script_js) - 1);
                        else if (request->url() == "/settings.html")
                                reply(request, 200, "text/html", settings_html, sizeof(settings_html)-1);
                        else if (request->url() == "/settings.js")
                                reply(request, 200, "application/javascript", settings_js, sizeof(settings_js)-1);
                        else if (request->url() == "/style.css")
                                reply(request, 200, "text/css", style_css, sizeof(style_css)-1);
                        else if (request->url() == "/terminal.html")
                                reply(request, 200, "text/html", terminal_html, sizeof(terminal_html)-1);
                        else if (request->url() == "/terminal.js")
                                reply(request, 200, "application/javascript", terminal_js, sizeof(terminal_js) - 1);
                        else 
                        {
                            if (WiFiConected)
                            {
                                request->redirect("/error404.html");
                            } else
                            {
                                request->redirect("/index.html");
                            }                            
                        }
                    } 
                });   
        // Webserver
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->redirect("/index.html"); });

        server.on("/run", [](AsyncWebServerRequest *request)
                    {
                        String message="";
                        if (request->hasParam("cmd")) {
                            message = request->getParam("cmd")->value();
                        }
                        request->send(200, "text/plain", "Run: " + message);
                        cli::parse(message.c_str(), [](const char* str) {
                            debugf("RUN:%s\n", str);
                        }, false); 
                    }
                  );

#ifdef OTA_UPDATE
        // Arduino OTA Update
        ArduinoOTA.onStart([]()
                           { events.send("Update Start", "ota"); });
        ArduinoOTA.onEnd([]()
                         { events.send("Update End", "ota"); });
        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                              {
            char p[32];
            sprintf(p, "Progress: %u%%\n", (progress/(total/100)));
            events.send(p, "ota"); });
        ArduinoOTA.onError([](ota_error_t error)
                {
                if (error == OTA_AUTH_ERROR) events.send("Auth Failed", "ota");
                else if (error == OTA_BEGIN_ERROR) events.send("Begin Failed", "ota");
                else if (error == OTA_CONNECT_ERROR) events.send("Connect Failed", "ota");
                else if (error == OTA_RECEIVE_ERROR) events.send("Recieve Failed", "ota");
                else if (error == OTA_END_ERROR) events.send("End Failed", "ota"); 
                }
        );
        ArduinoOTA.setHostname(HOSTNAME);
        ArduinoOTA.begin();
#endif
        events.onConnect([](AsyncEventSourceClient *client)
                         { client->send("hello!", NULL, esp_timer_get_time(), 1000); });
        server.addHandler(&events);

        if (MDNS.begin(HOSTNAME))
        {
            MDNS.addService("http", "tcp", 80);
        }

        // Websocket
        ws.onEvent(wsEvent);
        server.addHandler(&ws);

        // Start Server
        server.begin();
        debug("You can now connect to http://");
        debug(HOSTNAME);
        debug(".local or http://");
        debugln(WiFi.localIP());
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
        ws.cleanupClients();
    }

    void send(const char *str)
    {
        if (currentClient)
            currentClient->text(str);
    }

}