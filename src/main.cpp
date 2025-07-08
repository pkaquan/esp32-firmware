#include <Service.h>
#include <Device.h>
#include <Security.h>


Sensor sensor (4,DHT22,34);
ControlDevice control (18,17,16,19,23);
Display display (21,22);
Service service;
Manager wm;
FileSave fileSave;

QueueHandle_t queueDataFirestore;
QueueHandle_t queueRelay;
QueueHandle_t queueDataSensor;


String userEmail = "";
String userPassword = "";
String passwordAP = "";
String newPassword = "";

uint8_t isSwitch = 0b00000000;



typedef struct 
{
    int mq2Value;
    int humidityValue;
    int temperatureValue ;
}TakeDataSensor;


typedef struct {
    bool state;
    int hour;
    int minute;
    int time;
    int speed;
}TakeDataFirestore;

void taskTakeDataSensor (void *prm){
    TakeDataSensor sensor_data;
    while (1){
        sensor_data.mq2Value = sensor.mq2();
        sensor_data.humidityValue = sensor.dhtHumidity();
        sensor_data.temperatureValue = sensor.dhtTemperature();        
        xQueueSend (queueDataSensor,&sensor_data,portMAX_DELAY);
        vTaskDelay (pdMS_TO_TICKS(2000));
    }
};

void taskDataFirestore (void *prm){
    TakeDataFirestore data;
    while (1){
        data.state = service.getBool ("Pump State");
        data.hour = service.getInt ("Hour");
        data.minute = service.getInt ("Minute");
        data.time = service.getInt ("Pump Time");
        data.speed = service.getInt ("Pump Speed");
        xQueueSend (queueDataFirestore, &data,portMAX_DELAY);
        vTaskDelay (pdMS_TO_TICKS(5000));
    }
}


void sendDataonDevice (void *prm) {
    TakeDataSensor data;
    while (1) {
        if (xQueueReceive (queueDataSensor, &data, portMAX_DELAY) == pdPASS){
            service.setIntValue ("Temperature",data.temperatureValue);
            service.setIntValue ("Humidity",data.humidityValue);
            service.setIntValue ("MQ2",data.mq2Value);        
            control.buzzerDevice (data.mq2Value);
            display.dhtDisplay (data.temperatureValue, data.humidityValue);
        }
    }
}

void taskSendSwithDevice (void *prm){
    while (1){
        for (int i = 0; i< 8;i++){
            char text[20];
            snprintf (text,sizeof(text),"Device Control %d", i+1);
            bool listDevice = service.getBool (text);
            bitWrite (isSwitch,i,listDevice);
        }
        control.switchDevice(isSwitch);
        vTaskDelay (pdMS_TO_TICKS(20000));
    }
}

void taskControlMotor (void *prm){
    TakeDataFirestore data;
    while (1){
        if (xQueueReceive(queueDataFirestore,&data,portMAX_DELAY) == pdPASS){
            control.pwmDevice(data.state,data.hour,data.minute,data.time,data.speed);
        }
    }
}



void setup (){
    Serial.begin (115200);

    //Connect WiFi and Store in memory
    bool force = false;
    bool littleSetup = fileSave.loadConfigFile(userEmail,userPassword,passwordAP);
    if (!littleSetup){
        force = true;
    } 
    wm.beginAP (userEmail,userPassword,passwordAP,force);
    if (wm.saveConfig()){
        fileSave.saveConfigFile(userEmail,userPassword,passwordAP);
    }

    // Connect to account of Firebase
    service.begin (userEmail,userPassword);
    service.serviceFirebase();

    // Initialize the devices
    display.initDisplay();
    sensor.begin();
    control.bginUDP();
    control.initDevice ();

    // Creat Queue
    queueDataFirestore = xQueueCreate (32,sizeof (TakeDataFirestore));
    queueDataSensor    = xQueueCreate (32,sizeof(TakeDataSensor));

    // Task Scheduling
    xTaskCreate (taskDataFirestore,   "Data Firestore",      12288, NULL, 2, NULL);  
    xTaskCreate (taskTakeDataSensor,  "Data Sensor",         8192,  NULL, 2, NULL);  
    xTaskCreate (sendDataonDevice,    "Send Data on Device", 12288, NULL, 2, NULL);  
    xTaskCreate (taskSendSwithDevice, "Switch Device",       16384, NULL, 2, NULL);  
    xTaskCreate (taskControlMotor,    "Control Motor",       8192,  NULL, 2, NULL);   
}
void loop (){
}
