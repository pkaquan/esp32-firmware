

#include "Firebase.h"
#include "addons/TokenHelper.h"

//Obtain user credentials to connect to Firebase
void Service::begin (String setEmail, String setPassword){
    email = setEmail;
    password = setPassword;
}
 void Service ::serviceFirebase (){
    config.api_key = apiKey;
    auth.user.email = email;
    auth.user.password = password;
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin (&config,&auth);
    Firebase.reconnectWiFi (true);

    Firebase.ready() ;
    documentPath = "/users/";
    documentPath += auth.token.uid.c_str();
 };

//Send an integer value to the cloud
void Service:: setIntValue (String setJsonFirestore, int intValue){
    String path = "fields/";
    path += setJsonFirestore;
    path += "/integerValue";
    json.set(path.c_str(),intValue);
    Firebase.Firestore.patchDocument(&fbdo,projectID,"",documentPath.c_str(),json.raw(),setJsonFirestore.c_str());
}

//Send a boolean value to the cloud
void Service:: setBoolValue (String setJsonFirestore, bool boolValue){
    String path = "fields/";
    path += setJsonFirestore;
    path += "/booleanValue";
    json.set(path.c_str(),boolValue);
    Firebase.Firestore.patchDocument(&fbdo,projectID,"",documentPath.c_str(),json.raw(),setJsonFirestore.c_str());  
}

//Retrieve an integer value from the cloud
bool Service ::getBool (String getJsonFirestore){
    String path = "fields/";
    path += getJsonFirestore;
    path += "/booleanValue";
    bool valueBool; 
    if (Firebase.Firestore.getDocument (&fbdo,projectID,"",documentPath.c_str(),"")){        
        json.setJsonData(fbdo.payload());
        json.get (result,path.c_str());
        if (result.success){
            return  result.boolValue;
            
        }
    }
    return false;
}

//Retrieve a boolean value from the cloud
int Service :: getInt (String getJsonFirestore){
    String path = "fields/";
    path += getJsonFirestore;
    path += "/integerValue";
    int valueInt;
    if (Firebase.Firestore.getDocument (&fbdo,projectID,"",documentPath.c_str(),"")){
        json.setJsonData(fbdo.payload());
        json.get (result,path.c_str());
        if (result.success){
            return result.intValue;
        }
    }
    return 0;
}
