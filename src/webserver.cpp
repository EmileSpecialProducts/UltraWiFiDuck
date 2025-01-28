/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#include "webserver.h"

#include <WiFi.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#ifdef OTA_UPDATE
#include <ArduinoOTA.h>
#endif
#include "config.h"
#include "debug.h"
#include "cli.h"
#include "settings.h"

#include "webfiles.h"

void reply(AsyncWebServerRequest *request, int code, const char *type, const uint8_t *data, size_t len)
{
    AsyncWebServerResponse *response =
        request->beginResponse(code, type, data, len);

    // response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Content-Encoding", "7zip");
    request->send(response);
}

namespace webserver
{
    // ===== PRIVATE ===== //
    AsyncWebServer server(80);
    AsyncWebSocket ws("/ws");
    AsyncEventSource events("/events");

    AsyncWebSocketClient *currentClient{nullptr};

    DNSServer dnsServer;

    IPAddress apIP(192, 168, 4, 1);

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

                debugf("Message from %u [%llu byte]=%s", client->id(), info->len, msg);

                currentClient = client;
                cli::parse(msg, [](const char *str)
                           {
                    webserver::send(str);
                    debugf("%s\n", str); }, false);
                currentClient = nullptr;
            }
        }
    }

    // ===== PUBLIC ===== //
    void begin()
    {
        bool Conected = false;
        // Access Point
        WiFi.hostname(HOSTNAME);
        if (strlen(settings::getSSID()) > 0 && ( strlen(settings::getPassword()) >= 8 || strlen(settings::getPassword()) == 0))
        {
            debugf("Connecting to  \"%s\":\"%s\"\n", settings::getSSID(), settings::getPassword());
            WiFi.begin(settings::getSSID(), settings::getPassword());
            for (uint8_t i = 0; i < 20 && !Conected; i++)
            { // wait 10 seconds
                if (WiFi.status() != WL_CONNECTED)
                    delay(500);
                else
                    Conected = true;
            }
            if (!Conected)
                debugf("Connecting to  \"%s\":\"%s\" Failed\n", settings::getSSID(), settings::getPassword());
        }
        if (!Conected)
        {
            // WiFi.mode(WIFI_AP_STA);
            WiFi.softAP(settings::getAPSSID(), settings::getAPPassword(), settings::getAPChannelNum());
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
            debugf("Started Access Point \"%s\":\"%s\"\n", settings::getAPSSID(), settings::getAPPassword());

            dnsServer.setTTL(300);
            dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
            dnsServer.start(53, URL, apIP);

        }
        // Webserver
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->redirect("/index.html"); });

        server.onNotFound([](AsyncWebServerRequest *request)
                          { request->redirect("/error404.html"); });

        server.on("/run", [](AsyncWebServerRequest *request)
                  {
            String message;

            if (request->hasParam("cmd")) {
                message = request->getParam("cmd")->value();
            }

            request->send(200, "text/plain", "Run: " + message);

            cli::parse(message.c_str(), [](const char* str) {
                debugf("%s\n", str);
            }, false); });

        WEBSERVER_CALLBACK;
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
            else if (error == OTA_END_ERROR) events.send("End Failed", "ota"); });
        ArduinoOTA.setHostname(HOSTNAME);
        ArduinoOTA.begin();

        events.onConnect([](AsyncEventSourceClient *client)
                         { client->send("hello!", NULL, esp_timer_get_time(), 1000); });
        server.addHandler(&events);
#endif

        MDNS.addService("http", "tcp", 80);

        // Websocket
        ws.onEvent(wsEvent);
        server.addHandler(&ws);

        // Start Server
        server.begin();
        debugln("Started Webserver");
    }

    void update()
    {
#ifdef OTA_UPDATE
        ArduinoOTA.handle();
#endif

        dnsServer.processNextRequest();
    }

    void send(const char *str)
    {
        if (currentClient)
            currentClient->text(str);
    }
}