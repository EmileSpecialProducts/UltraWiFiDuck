
#include <FS.h> // File
#include <LittleFS.h>
/*!
   \file esp_duck/cli.cpp
   \brief Command line interface source
   \author Stefan Kremser
   \copyright MIT License
 */

#include "cli.h"

// SimpleCLI library
#include <SimpleCLI.h> // https://github.com/SpacehuhnTech/SimpleCLI

// // Get RAM (heap) usage
// extern "C" {
// #include "user_interface.h"
// }

// Import modules used for different commands
#include "config.h"
#include "debug.h"

#include "duckscript.h"
#include "settings.h"

namespace cli {
    // ===== PRIVATE ===== //
    SimpleCLI cli;           // !< Instance of SimpleCLI library

    PrintFunction printfunc; // !< Function used to print output

    /*!
     * \brief Internal print function
     *
     * Outputs a c-string using the currently set printfunc.
     * Helps to keep code readable.
     * It's only defined in the scope of this file!
     *
     * \param s String to printed
     */
    inline void print(const String& s) {
        if (printfunc) printfunc(s.c_str());
    }

    // ===== PUBLIC ===== //
    void begin() {
        /**
         * \brief Set error callback.
         *
         * Prints 'ERROR: <error-message>'
         * And 'Did you mean "<command-help>"?'
         * if the command name matched, but the arguments didn't
         */
        cli.setOnError([](cmd_error* e) {
            CommandError cmdError(e); // Create wrapper object

            String res = "ERROR: " + cmdError.toString();

            if (cmdError.hasCommand()) {
                res += "\nDid you mean \"";
                res += cmdError.getCommand().toString();
                res += "\"?";
            }

            print(res);
        });

        /**
         * \brief Create help Command
         *
         * Prints all available commands with their arguments
         */
        cli.addCommand("help", [](cmd* c) {
            print(cli.toString());
        });

        /**
         * \brief Create ram command
         *
         * Prints number of free bytes in the RAM
         */
        cli.addCommand("ram", [](cmd* c) {
            size_t freeRam = ESP.getFreeHeap();
            String res     = String(freeRam) + " bytes available";
            print(res);
        });

        /**
         * \brief Create version command
         *
         * Prints the current version number
         */
        cli.addCommand("version", [](cmd* c) {
            String res = "Version " + String(VERSION);
            print(res);
        });

        /**
         * \brief Create settings command
         *
         * Prints all settings with their values
         */
        cli.addCommand("settings", [](cmd* c) {
            settings::load();
            print(settings::toString());
        });

        /**
         * \brief Create set command
         *
         * Updates the value of a setting
         *
         * \param name name of the setting
         * \param vale new value for the setting
         */
        Command cmdSet {
            cli.addCommand("set", [](cmd* c) {
                Command  cmd { c };

                Argument argName { cmd.getArg(0) };
                Argument argValue { cmd.getArg(1) };

                String name { argName.getValue() };
                String value { argValue.getValue() };
                debug( "> set \"" + name + "\" to \"" + value + "\"");
                settings::set(name.c_str(), value.c_str());
                settings::save();
                String response = "> set \"" + name + "\" to \"" + value + "\"";

                print(response);
            })
        };
        cmdSet.addPosArg("n/ame");
        cmdSet.addPosArg("v/alue");

        /**
         * \brief Create reset command
         *
         * Resets all settings and prints out the defaul values
         */
        cli.addCommand("reset", [](cmd* c) {
            settings::reset();
            settings::save();
            print(settings::toString());
        });

        /**
         * \brief Create reboot command
         *
         * this will reboot the ESP device
         */
        cli.addCommand("reboot", [](cmd *c)
                       {
                print("Rebooting");
                ESP.restart(); });

        /**
         * \brief Create status command
         *
         * Prints status of i2c connection to atmega32u4:
         * running <script>
         * connected
         * i2c connection problem
         */
        cli.addCommand("status", [](cmd* c) {
            if (true) {
                if (duckscript::isRunning()) {
                    String s = "running " + duckscript::currentScript();
                    print(s);
                } else {
                    print("Super WiFiDuck -- Ready");
                }
            } else {
                print("Internal connection problem");
            }
        });

        /**
         * \brief Create ls command
         *
         * Prints a list of files inside of a given directory
         *
         * \param * Path to directory
         */
        cli.addSingleArgCmd("ls", [](cmd* c) {
            Command  cmd { c };
            Argument arg { cmd.getArg(0) };
            String res = listDir(arg.getValue());

            print(res);
        });

        /**
         * \brief Create mem command
         *
         * Prints memory usage of LittleFS
         */
        cli.addCommand("mem", [](cmd* c) {
            String s = "";
            s.reserve(64);

            s += String(LittleFS.totalBytes());
            s += " byte\n";
            s += String(LittleFS.usedBytes() );
            s += " byte used\n";
            s += String(LittleFS.totalBytes() - LittleFS.usedBytes() );
            s += " byte free";

            print(s);
        });

        /**
         * \brief Create cat command
         *
         * Prints out a file from the LittleFS
         *
         * \param * Path to file
         */
        cli.addSingleArgCmd("cat", [](cmd* c) {
            Command  cmd { c };
            Argument arg { cmd.getArg(0) };
            String filename = arg.getValue();
            fixPath(filename);

            File f = LittleFS.open(filename);

            int buf_size { 256 };
            char buffer[buf_size];

            while (f && f.available()) {
                for (size_t i = 0; i<buf_size; ++i) {
                    if (!f.available() || (i == buf_size-1)) {
                        buffer[i] = '\0';
                        i         = buf_size;
                    } else {
                        buffer[i] = f.read();
                    }
                }
                print(buffer);
            }
        });

        /**
         * \brief Create run command
         *
         * Starts executing a ducky script
         *
         * \param * Path to script in LittleFS
         */
        cli.addSingleArgCmd("run", [](cmd* c) {
            Command  cmd { c };
            Argument arg { cmd.getArg(0) };

            duckscript::run(arg.getValue());

            String response = "> started \"" + arg.getValue() + "\"";
            print(response);
        });

        /**
         * \brief Create stop command
         *
         * Stops executing a script
         *
         * \param * Path to specific ducky script to stop
         *          If no path is given, stop whatever script is active
         */
        cli.addSingleArgCmd("stop", [](cmd* c) {
            Command  cmd { c };
            Argument arg { cmd.getArg(0) };


            String response = "> stopped " + arg.getValue();
            print(response);
        });

        /**
         * \brief Create create command
         *
         * Creates a file in the LittleFS
         *
         * \param * Path with filename
         */
        cli.addSingleArgCmd("create", [](cmd* c) {
            Command  cmd { c };
            Argument arg { cmd.getArg(0) };
            String filename = arg.getValue();
            fixPath(filename);

            File f= LittleFS.open(filename, "w", true);
            if (f) f.close();

            String response = "> created file \"" + arg.getValue() + "\"";
            print(response);
        });

        /**
         * \brief Create remove command
         *
         * Removes file in LittleFS
         *
         * \param * Path to file
         */
        cli.addSingleArgCmd("remove", [](cmd* c) {
            Command  cmd { c };
            Argument arg { cmd.getArg(0) };
            String filename = arg.getValue();
            fixPath(filename);
            LittleFS.remove(filename);
            String response = "> removed file \"" + arg.getValue() + "\"";
            print(response);
        });

        /**
         * \brief Create rename command
         *
         * Renames a file in LittleFS
         *
         * \param fileA Old path with filename
         * \param fileB New path with filename
         */
        Command cmdRename {
            cli.addCommand("rename", [](cmd* c) {
                Command  cmd { c };

                Argument argA { cmd.getArg(0) };
                Argument argB { cmd.getArg(1) };

                String fileA { argA.getValue() };
                String fileB { argB.getValue() };
                fixPath(fileA);
                fixPath(fileB);
                LittleFS.rename(fileA, fileB);

                String response = "> renamed \"" + fileA + "\" to \"" + fileB + "\"";
                print(response);
            })
        };
        cmdRename.addPosArg("fileA,a");
        cmdRename.addPosArg("fileB,b");

        /**
         * \brief Create write command
         *
         * Appends string to a file in LittleFS
         *
         * \param file    Path to file
         * \param content String to write
         */
        Command cmdWrite {
            cli.addCommand("write", [](cmd* c) {
                Command  cmd { c };

                Argument argFileName { cmd.getArg(0) };
                Argument argContent { cmd.getArg(1) };

                String fileName { argFileName.getValue() };
                String content { argContent.getValue() };
                fixPath(fileName);
                File f = LittleFS.open(fileName, "w", true);
                if (f)
                {
                    f.println(content);
                    f.close();
                    debugln("Wrote file");
                }
                else
                {
                    debugln("File error");
                }

                String response = "> wrote to file \"" + fileName + "\"";
                print(response);
            })
        };
        cmdWrite.addPosArg("f/ile");
        cmdWrite.addPosArg("c/ontent");

        /**
         * \brief Create format command
         *
         * Formats LittleFS
         */
        cli.addCommand("format", [](cmd *c)
            {
            LittleFS.format();
            print("Formatted LittleFS"); });

        /**
         * \brief Create stream command
         *
         * Opens stream to a file in LittleFS.
         * Whatever is parsed to the CLI is written into the strem.
         * Only close and read are commands will be executed.
         *
         * \param * Path to file
         */
        cli.addSingleArgCmd("stream", [](cmd* c) {
            Command  cmd { c };
            Argument arg { cmd.getArg(0) };
            String fileName { arg.getValue() };
            fixPath(fileName);
            streamOpen(fileName);
            String response = "> opened stream \"" + arg.getValue() + "\"";
            print(response);
        });

        /**
         * \brief Create close command
         *
         * Closes file stream
         */
        cli.addCommand("close", [](cmd *c)
                       {
            streamClose();
            print("> closed stream"); });

        /**
         * \brief Create read command
         *
         * Reads from file stream (1024 characters)
         */
        cli.addCommand("read", [](cmd *c)
                       {
            if (streamAvailable()) {
                size_t len = 1024;

                char buffer[len];

                size_t read = streamRead(buffer, len);

                print(buffer);
            } else {
                print("> END");
            } });
    }

    void parse(const char* input, PrintFunction printfunc, bool echo) {
        cli::printfunc = printfunc;

        if (streaming() &&
            (strcmp(input, "close\n") != 0) &&
            (strcmp(input, "read\n") != 0))
        {
            streamWrite(input, strlen(input));
            print("> Written data to file");
        }
        else
        {
            if (echo) {
                String s = "# " + String(input);
                print(s);
            }

            cli.parse(input);
        }
    }
    File streamFile;

    void fixPath(String &path)
    {
        if (!path.startsWith("/"))
        {
            path = "/" + path;
        }
    }

    String listDir(String dirName)
    {

        String res;

        fixPath(dirName);

        File root = LittleFS.open(dirName);

        File file = root.openNextFile();

        while (file)
        {
            res += file.name();
            res += ' ';
            res += file.size();
            res += '\n';
            file = root.openNextFile();
        }
        if (res.length() == 0)  res += "\n";
        
        return res;
    }

    void streamOpen(String fileName)
    {
        streamClose();
        fixPath(fileName);
        streamFile = LittleFS.open(fileName, "r+", true);
        if (!streamFile)
            debugln("ERROR: No stream file open");
        else
            debugln("File opened!");
    }

    void streamWrite(const char *buf, size_t len)
    {
        if (streamFile)
            streamFile.write((uint8_t *)buf, len);
        else
            debugln("ERROR: No stream file open");
    }

    size_t streamRead(char *buf, size_t len)
    {
        if (streamFile)
        {
            size_t i;
            debugln("streamRead  " + String(len));
            for (i = 0; i < len; ++i)
            {
                if (!streamFile.available() || (i == len - 1))
                {
                    buf[i] = '\0';
                    break;
                }
                else
                {
                    buf[i] = streamFile.read();
                }
            }
            debugln("File buf " + String(buf));
            return i;
        }
        else
        {
            debugln("ERROR: streamRead No stream file open");
            return 0;
        }
    }

    size_t streamReadUntil(char *buf, char delimiter, size_t max_len)
    {
        if (streamFile)
        {
            size_t i;
            char c = 'x';

            for (i = 0; i < max_len; ++i)
            {
                if ((c == delimiter) || !streamFile.available() || (i == max_len - 1))
                {
                    buf[i] = '\0';
                    break;
                }
                else
                {
                    c = streamFile.read();
                    buf[i] = c;
                }
            }
            return i;
        }
        else
        {
            debugln("ERROR: No stream file open");
            return 0;
        }
    }

    void streamClose()
    {
        streamFile.close();
    }

    bool streaming()
    {
        return streamFile;
    }

    size_t streamAvailable()
    {
        if (!streamFile)
            return 0;
        return streamFile.available();
    }
}