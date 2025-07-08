#ifndef FILE_SAVE_H
#define FILE_SAVE_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <FS.h>
#include "AESEncrytion.h"

class FileSave {
    private :
    const char* jsonFile = "/configjson";
    bool shouldLoadFile = false;
    AESEncrytion aes;
    public :
    void saveConfigFile (String jsonEmail, String jsonPassword, String passwordAP);
    bool loadConfigFile (String& jsonEmail, String &jsonPassword, String passwordAP);

};
#endif