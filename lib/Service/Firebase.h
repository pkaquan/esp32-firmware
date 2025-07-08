#ifndef FIREBASE_H
#define FIREBASE_H

#include <Arduino.h>
#include <Firebase_ESP_Client.h>

class Service {
    private :

    String email = "";
    String password = "";

    const char* projectID = "smart-home-91161";
    const char* apiKey = "AIzaSyANiOSLEb-CWgzLWVJLmrgnRdcwWnAWdwU";
    String documentPath = "";
    String userUID = "";
    
    FirebaseConfig config;
    FirebaseAuth auth;
    FirebaseData fbdo;
    FirebaseJson json;
    FirebaseJsonData result;


    public :
    void begin (String setEmail, String setPasssword);
    void serviceFirebase ();
    void setIntValue (String textJson, int value);
    void setStringValue (String textJson, String value);
    void setBoolValue (String textJson, bool value);
    bool getBool (String textJson);
    String getString (String textJson);
    int getInt (String textJson);
};
#endif
