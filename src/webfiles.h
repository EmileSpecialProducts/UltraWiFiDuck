#pragma once

#define WEBSERVER_CALLBACK \
server.on("/credits.html", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "text/html", credits_html, sizeof(credits_html)-1);\
});\
server.on("/error404.html", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 404, "text/html", error404_html, sizeof(error404_html)-1);\
});\
server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "text/html", index_html, sizeof(index_html)-1);\
});\
server.on("/help.html", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "text/html", help_html, sizeof(help_html)-1);\
});\
server.on("/index.js", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "application/javascript", index_js, sizeof(index_js)-1);\
});\
server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "application/javascript", script_js, sizeof(script_js)-1);\
});\
server.on("/settings.html", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "text/html", settings_html, sizeof(settings_html)-1);\
});\
server.on("/settings.js", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "application/javascript", settings_js, sizeof(settings_js)-1);\
});\
server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "text/css", style_css, sizeof(style_css)-1);\
});\
server.on("/terminal.html", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "text/html", terminal_html, sizeof(terminal_html)-1);\
});\
server.on("/terminal.js", HTTP_GET, [](AsyncWebServerRequest* request) {\
	reply(request, 200, "application/javascript", terminal_js, sizeof(terminal_js)-1);\
});\
server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)\
		  { reply(request, 200, "image/x-icon", favicon_ico, sizeof(favicon_ico)); });\


#include "html_credits_html.h"
#include "html_error404_html.h"
#include "html_index_html.h"
#include "html_help_html.h"
#include "html_index_js.h"
#include "html_script_js.h"
#include "html_settings_html.h"
#include "html_settings_js.h"
#include "html_style_css.h"
#include "html_terminal_html.h"
#include "html_terminal_js.h"
#include "html_favicon_ico.h"