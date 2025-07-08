#include "Storage_Json.h"

//Store encrypted data.
void FileSave::saveConfigFile (String jsonEmail, String jsonPassword, String passwordAP){
    String enCryption = aes.encrypt (jsonPassword);
    if (LittleFS.begin(true)||LittleFS.begin(false)){
        File file = LittleFS.open (jsonFile,"w");
        JsonDocument  doc ;
        doc["UserEmail"] = jsonEmail;
        doc["UserPassword"] = enCryption;
        serializeJsonPretty (doc,Serial);
        if (serializeJson(doc, file) == 0) {
            Serial.println("Failed to write to config file");
        }
        file.close();
    }
}

//Retrieve and decrypt data
bool FileSave::loadConfigFile(String& jsonEmail, String &jsonPassword, String passwordAP) {
    if (LittleFS.begin(true)||LittleFS.begin(false)){
        File file = LittleFS.open(jsonFile,"r");
        if (file){
            JsonDocument doc;
            DeserializationError error = deserializeJson (doc,file);
            serializeJsonPretty (doc,Serial);
            if (!error){
                jsonEmail = doc["UserEmail"].as<String>();
                String getJsonPassword = doc["UserPassword"].as<String>();
                jsonPassword = aes.decrypt (getJsonPassword);
                return true;
            } 
        } 
    }
    return false;
}
