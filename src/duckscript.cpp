/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#include "duckscript.h"
#include "duckparser.h"


#include "config.h"
#include "debug.h"

#include <FS.h> // File
#include <LittleFS.h>

namespace duckscript {

    File f;

    char * prevMessage    { NULL };
    size_t prevMessageLen { 0 };

    bool running { false };


    static void runTask(void* parameter) {
        String* fileNamePtr = (String*) parameter;
        String fileName = *fileNamePtr;
        delete fileNamePtr;  // Free the heap memory

        if (fileName.length() > 0) {
            debugf("Run file %s\n", fileName.c_str());
            f = LittleFS.open(fileName);
            running = true;
            nextLine();
        }

        vTaskDelete(NULL);  // Delete this task when done
    }

    void run(String fileName) {
        // Create a heap copy of fileName
        String* fileNamePtr = new String(fileName);

        // Create a new task
        xTaskCreate(
                runTask,               // Function that should be executed
                "runDuckScriptTask",   // Name of the task
                4096,                  // Stack size in words
                fileNamePtr,           // Parameter to pass to the task
                1,                     // Priority
                NULL                   // Task handle
        );
    }

    void nextLine() {
        while (running) {
            if (!f) {
                debugln("File error");
                stopAll();
                return;
            }

            if (!f.available()) {
                debugln("Reached end of file");
                stopAll();
                return;
            }

            char buf[BUFFER_SIZE];
            unsigned int buf_i =  0;
            bool eol = false; // End of line

            // Read a line into the buffer
            while (f.available() && !eol && buf_i < BUFFER_SIZE) {
                uint8_t b = f.peek();
                eol = (b == '\n');
                buf[buf_i] = f.read();
                ++buf_i;
            }

            if (!eol) debugln();

            if (strncmp((char*)buf, "REPEAT", _min(buf_i, 6)) == 0 || strncmp((char*)buf, "REPLAY", _min(buf_i, 6)) == 0) {
                // Extract repeat count if available
                char* pch = strtok((char*)buf + 6, " ");
                int repeatCount = atoi(pch);
                if (repeatCount <= 0) {
                    repeatCount = 1;
                }

                // Repeat the previous command
                for (int i = 0; i < repeatCount; ++i) {
                    if (prevMessage) {
                        duckparser::parse(prevMessage, prevMessageLen);
                    }
                }
            } else {
                // Store this as the previous message
                if (prevMessage) free(prevMessage);
                prevMessageLen = buf_i;
                prevMessage = (char*)malloc(prevMessageLen + 1);
                memcpy(prevMessage, buf, buf_i);
                prevMessage[buf_i] = '\0';

                // Process the line here
                duckparser::parse(buf, buf_i);
            }
        }
    }

    void stopAll() {
        if (running) {
            if (f) f.close();
            running = false;
            debugln("Stopped script");
        }
    }

    void stop(String fileName) {
        if (fileName.length() == 0) stopAll();
        else {
            if (running && f && (fileName == currentScript())) {
                f.close();
                running = false;
                debugln("Stopped script");
            }
        }
    }

    bool isRunning() {
        return running;
    }

    String currentScript() {
        if (!running) return String();
        return String(f.name());
    }
}