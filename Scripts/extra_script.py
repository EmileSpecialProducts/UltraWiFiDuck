Import("env")
import os
import shutil
from shutil import copyfile

# process release build flags

def PostBuild(source, target, env):
    print("--------- Save Firmware before upload -------------------")
    # https://esphome.github.io/esp-web-tools/
    # https://github.com/esphome/esp-web-tools
    # https://www.hackster.io/usini/platformio-esp32-starter-project-with-esp-web-tools-745568
    # https://github.com/usini/esp32_platformio/tree/main
    # pio run -t envdump  // will give all the avalabe environment flags.

    # print("PROJECT_DIR " + env.get("PROJECT_DIR"))
    # print("PROJECT_BUILD_DIR " + env.get("PROJECT_BUILD_DIR"))
    # print("BOARD " + env.get("BOARD"))
    # print("BUILD_TYPE " + env.get("BUILD_TYPE"))
    # print("PROJECT_CONFIG " + env.get("PROJECT_CONFIG")) # pints to the platformio.ini file
    # print("PARTITIONS_TABLE_CSV " + env.get("PARTITIONS_TABLE_CSV"))
    # partitions_csv = env.subst("$PARTITIONS_TABLE_CSV")
    # print(partitions_csv)
    # print("PROJECT_CORE_DIR " + env.get("PROJECT_CORE_DIR"))

    # print("PROJECT_PACKAGES_DIR " + platformpakkages )
    # board_config = env.BoardConfig()
    # print( board_config.get("build.flash_mode", "dio"))

    # print( env.subst("$BOARD_FLASH_MODE"))
    # print(env.subst("$BOARD_CPU_TYPE"))
    # print(env.subst("${__get_board_f_image(__env__)}"))  # 80m
    # print(env.subst("${__get_board_flash_mode(__env__)}"))  # dio
    # print(env.subst("${__get_board_boot_mode(__env__)}"))  #
    # print(env.subst("${__get_board_f_boot(__env__)}"))
    # print(env.subst("${__get_board_memory_type(__env__)}"))  #
    # print(env.subst("${__get_board_f_cpu(__env__)}"))
    # print( board_config.get("build.psram_type", "qspi"))
    # print( board_config.get("build.memory_type", "AAAA"))
    # print( board_config.get("build.cpu_type", "AAAB"))
    # print("UPLOADCMD " + env.get("UPLOADCMD"))
    # print(env.subst("$UPLOADCMD"))
    # Get source dir (.pio/name_env/)
    # source = env.get("PROJECT_BUILD_DIR") + "/" + env.get("PIOENV")

    print("ESP32_APP_OFFSET=" + env.get("ESP32_APP_OFFSET"))

    platformpakkages = env.get("PROJECT_PACKAGES_DIR")
    board_boot_mode = env.subst("${__get_board_boot_mode(__env__)}")
    board = env.get("BOARD")
    board_mcu = env.get("BOARD_MCU")
    pioenv=env.get("PIOENV")
    source = env.get("PROJECT_BUILD_DIR") + "\\" + pioenv
    print("BOARD_MCU " + board_mcu)
    print("BOARD_BOOT_MODE " + board_boot_mode)
    print("BOARD_F_CPU " + env.get("BOARD_F_CPU"))
    print("BOARD = " + board + " board_mcu = " + board_mcu + " board_boot_mode = " + board_boot_mode)
    upload = env.subst("$UPLOADERFLAGS").split()
    nextMB=False
    flashsize="0MB"
    for x in upload:
        # print("Upload :"+x)
        if nextMB:  
            flashsize = x
            nextMB = False
        if x == "--flash_size":
            nextMB=True
    print("flashsize = "+flashsize)
    # Save at destination docs/bins
    destination = os.getcwd() + "\\firmware" 
    if not os.path.exists(destination):
        os.mkdir(destination)
    destination = (
        destination + "\\" + board_mcu + "_" + flashsize + "_" + board_boot_mode
    )  
    if not os.path.exists(destination):
        os.mkdir(destination)

    print("destination = " + destination)

    shutil.copyfile(source + "\\bootloader.bin", destination + "\\bootloader.bin")
    shutil.copyfile(source + "\\partitions.bin", destination + "\\partitions.bin")
    shutil.copyfile(
        platformpakkages
        + "\\framework-arduinoespressif32\\tools\\partitions\\boot_app0.bin",
        destination + "\\boot_app0.bin",
    )
    shutil.copyfile(source + "\\firmware.bin", destination + "\\firmware.bin")
    flash = env.subst("$FLASH_EXTRA_IMAGES")
    # print(flash)
    parts = flash.split()
    print("---------------------------------------------------------")
    print(parts[0] + " " + str(int(parts[0], 16)) + " " + parts[1])
    print(parts[2] + " " + str(int(parts[2], 16)) + " " + parts[3])
    print(parts[4] + " " + str(int(parts[4], 16)) + " " + parts[5])
    print(env.get("ESP32_APP_OFFSET") + " " + str(int(env.get("ESP32_APP_OFFSET"), 16)) + " " +source + "\\firmware.bin")
    print("---------------------------------------------------------")

# env.AddPostAction("buildprog", PostBuild)

env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", PostBuild)

# print("PROGPATH = ${PROGPATH}")
# env.AddPostAction("$PROGPATH", PostBuild)

# print("PROGPATH = ${PROGPATH}")
# print("Current CLI targets", COMMAND_LINE_TARGETS)
# print("Current Build targets", BUILD_TARGETS)


# def post_program_action(source, target, env):
#    print("Program has been built!")
#    program_path = target[0].get_abspath()
#    print("Program path", program_path)
# Use case: sign a firmware, do any manipulations with ELF, etc
# env.Execute(f"sign --elf {program_path}")


# env.AddPostAction("$PROGPATH", post_program_action)

#
# Upload actions
#


# def before_upload(source, target, env):
#    print("before_upload")
#    # do some actions
#    # call Node.JS or other script
#    env.Execute("node --version")


# def after_upload(source, target, env):
#    print("after_upload")
#    # do some actions


# env.AddPreAction("upload", before_upload)
# env.AddPostAction("upload", after_upload)

#
# Custom actions when building program/firmware
#

# env.AddPreAction("buildprog", callback...)
# env.AddPostAction("buildprog", callback...)

#
# Custom actions for specific files/objects
#

# env.AddPreAction("$PROGPATH", callback...)
# env.AddPreAction("$BUILD_DIR/${PROGNAME}.elf", [callback1, callback2,...])
# env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", callback...)

# custom action before building SPIFFS image. For example, compress HTML, etc.
# env.AddPreAction("$BUILD_DIR/spiffs.bin", callback...)

# custom action for project's main.cpp
# env.AddPostAction("$BUILD_DIR/src/main.cpp.o", callback...)

# Custom HEX from ELF
# env.AddPostAction(
#    "$BUILD_DIR/${PROGNAME}.elf",
#    env.VerboseAction(" ".join([
#        "$OBJCOPY", "-O", "ihex", "-R", ".eeprom",
#        "$BUILD_DIR/${PROGNAME}.elf", "$BUILD_DIR/${PROGNAME}.hex"
#    ]), "Building $BUILD_DIR/${PROGNAME}.hex")
# )
