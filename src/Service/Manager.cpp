#include "Manager.h"

void Manager ::beginAP(String &userEmail, String &userPassword, String &passwordAP, bool force)
{
    WiFi.mode(WIFI_STA);
    wm.resetSettings();
    wm.setSaveConfigCallback([this](){ showSaveConfig = true; });
    wm.setAPCallback([](WiFiManager *wm) {});
    WiFiManagerParameter custom_user_email("key_email", "Tài khoản AnhWan-Home :  ", userEmail.c_str(), 50);
    WiFiManagerParameter custom_user_password("key_password", "Mật khẩu AnhWan-Home : ", userPassword.c_str(), 50, "type=\"password\"");
    WiFiManagerParameter custom_password_ap("key_passwordap", "Đổi mật khẩu thiết bị : ", passwordAP.c_str(), 50, "type=\"password\"");

    wm.addParameter(&custom_user_email);
    wm.addParameter(&custom_user_password);
    wm.addParameter(&custom_password_ap);
    if (force)
    {
        if (!wm.startConfigPortal("AnhWan-Home", textPasswordAP.c_str()))
        {
            delay(3000);
            ESP.restart();
            delay(5000);
        }
    }
    else
    {
        if (!wm.autoConnect("AnhWan-Home", textPasswordAP.c_str()))
        {
            delay(3000);
            ESP.restart();
            delay(5000);
        }
    }

    userEmail = custom_user_email.getValue();
    userPassword = custom_user_password.getValue();
    passwordAP = custom_password_ap.getValue();
}
bool Manager ::saveConfig()
{
    return showSaveConfig;
}