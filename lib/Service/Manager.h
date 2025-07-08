#ifndef MANAGER_H
#define MANAGER_H

#include <WiFiManager.h>
#include <FS.h>
#include <Arduino.h>
#include <WiFi.h>



class Manager   {
    private:
    WiFiManager wm;  
    String      textPasswordAP  = "123456789";
    bool showSaveConfig = false;
    public :
    void        beginAP           (String &userEmail, String &userPassword, String &passwordAP,bool force);
    void        reconnectWiFi     (bool force);
    void        resetPassowrdAp   (String &passwordAp);
    bool        saveConfig        ();
};
#endif