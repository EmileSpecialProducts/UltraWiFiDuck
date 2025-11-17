Import("env")
import os
import shutil
from shutil import copyfile

# process release build flags

def PostBuild(source, target, env):
    print("--------- Save Firmware before upload -------------------")
    import datetime
    now = datetime.datetime.now()
    print(now)
    from time import gmtime, strftime
    print(strftime("%Y-%m-%d %H:%M:%S GMT", gmtime()))
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
    # print("ESP32_APP_OFFSET=" + env.get("ESP32_APP_OFFSET"))
    platformpakkages = env.get("PROJECT_PACKAGES_DIR")
    board_boot_mode = env.subst("${__get_board_boot_mode(__env__)}")
    board = env.get("BOARD")
    board_mcu = env.get("BOARD_MCU")
    pioenv=env.get("PIOENV")
    source = env.get("PROJECT_BUILD_DIR") + "/" + pioenv
    flash_image=env.get("FLASH_EXTRA_IMAGES")
    #print("flash_image =",flash_image)
    print("BOARD_MCU " + board_mcu)
    if board_mcu == "esp8266":
        print("CPU is esp8266 " + source )
        destination = os.getcwd() + "/firmware"
        if not os.path.exists(destination):
            os.mkdir(destination)
        destination = (
            destination + "/" + board_mcu
        )  
        if not os.path.exists(destination):
            os.mkdir(destination)
        print("destination = " + destination)
        shutil.copyfile(source + "/firmware.bin", destination + "/firmware.bin")
        partition_file=env.get("LDSCRIPT_PATH")
        print("partition_file " , partition_file)   
        mklittlefs=env.get("PROJECT_CORE_DIR")+"/tools/tool-mklittlefs/mklittlefs.exe"
        print("MKSPIFFSTOOL ",mklittlefs)
        littlefsdir = os.getcwd() + "/payloads"    
        # mklittlefs doc -> https://github.com/jason2866/mklittlefs
        #env.Execute(mklittlefs +" -a -c "+littlefsdir + " -s "+ str(littlefs_size) + " " + destination + "/littlefs.bin")
        # list all the files 
        #env.Execute(mklittlefs +" -l " + destination + "/littlefs.bin") 
        images=env.get("FLASH_EXTRA_IMAGES")
        print("images " , images)
        print("Do not know how to make the littlefs for the 8266 yet!!!!")    
        ################################################################################
    else:
        if "OTA" in pioenv:
            print("Not gererating ESP-Web-tool dowload files")  
        else:
            #for flash_row in flash_image:
            #    print("Offset = ", flash_row[0],int(flash_row[0],0),"File = ",flash_row[1] )
            #print("BOARD_MCU " + board_mcu)
            #print("BOARD_BOOT_MODE " + board_boot_mode)
            #print("BOARD_F_CPU " + env.get("BOARD_F_CPU"))
            #print("BOARD = " + board + " board_mcu = " + board_mcu + " board_boot_mode = " + board_boot_mode)
            ##### Generate the littlefs from littlefs dir 
            mklittlefs=env.get("PROJECT_CORE_DIR")+"/tools/tool-mklittlefs/mklittlefs.exe"
            #print("MKSPIFFSTOOL ",mklittlefs)
            littlefsdir = os.getcwd() + "/payloads"    
            partition=env.get("PARTITIONS_TABLE_CSV")
            print("partition " , partition)    
            import csv
            # get the littlefs_size form the PARTITIONS_TABLE_CSV 
            littlefs_size=0
            littlefs_offset="?"
            app0_size=0
            app0_offset="?"
            endofmemmory=0
            with open(partition) as csv_file:
                csv_reader = csv.reader(csv_file, delimiter=',')
                for row in csv_reader:
                    # row[0] = Name, row[1]= Type, row[2]= SubType, row[3]= Offset, row[4]= Size  
                    print(f'{row[0]: <16} {row[1]: <16} {row[2]: <16} {row[3]: <16} {row[4]: <16}')
                    if row[3].startswith("0x") and row[4].startswith("0x") and endofmemmory < (int(row[3], 0) + int(row[4], 0)) :
                        endofmemmory = (int(row[3], 0) + int(row[4], 0))
                    if row[0] == "spiffs" : 
                        littlefs_size =  int(row[4], 0)
                        littlefs_offset =int(row[3], 0)
                    if row[0] == "littlefs" : 
                        littlefs_size =  int(row[4], 0)
                        littlefs_offset =int(row[3], 0)  
                    if row[0] == "app0" : 
                        app0_size =  int(row[4], 0)
                        app0_offset =int(row[3], 0)  
            #print("endofmemmory = ", endofmemmory , " ", int( (endofmemmory+0x80000) / 0x100000))
            flashsize = str(int( (endofmemmory+0x80000) / 0x100000)) + "MB" 
            print("flashsize = ",flashsize)            
            #print("littlefs size = ",littlefs_size ," Offset = ", littlefs_offset)
            destination = os.getcwd() + "/firmware" 
            if not os.path.exists(destination):
                os.mkdir(destination)
            destination = (
                destination + "/" + board_mcu + "_" + flashsize + "_" + board_boot_mode
            )  
            if not os.path.exists(destination):
                os.mkdir(destination)
            print("destination = " + destination)            
            for flash_row in flash_image:
                if flash_row[1].endswith("bootloader.bin"):
                    shutil.copyfile(flash_row[1], destination + "/bootloader.bin")
                if flash_row[1].endswith("partitions.bin"):
                    shutil.copyfile(flash_row[1], destination + "/partitions.bin")
                if flash_row[1].endswith("boot_app0.bin"):
                    shutil.copyfile(flash_row[1], destination + "/boot_app0.bin")
                print("flash_row Offset = ", flash_row[0],int(flash_row[0],0),"File = ",flash_row[1] )
            shutil.copyfile(source + "/firmware.bin", destination + "/firmware.bin")
            print("firmware  Offset = ", hex(app0_offset) ,app0_offset,"File = ",source + "/firmware.bin" )
            print("littlefs  Offset = ", hex(littlefs_offset) ,littlefs_offset,"File = ",destination + "/littlefs.bin" )
            # mklittlefs doc -> https://github.com/jason2866/mklittlefs
            env.Execute(mklittlefs +" -a -c "+littlefsdir + " -s "+ str(littlefs_size) + " " + destination + "/littlefs.bin")
            # list all the files 
            # env.Execute(mklittlefs +" -l " + destination + "/littlefs.bin")    
            ################################################################################

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
