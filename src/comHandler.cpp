#include <Arduino.h>
#include "../include/tasks.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <ESP32_blelib.hh>

extern QueueHandle_t motorQueue;
extern QueueHandle_t comQueue;
extern QueueHandle_t ledQueue;
extern QueueHandle_t sensorQueue;
std::string data;
extern bool ifSensor, obstacle;
int measured_data = 0;
void comHandler(void *arg){
    int respond = 0;
    pinMode(LED, OUTPUT);
    // pinMode(15, OUTPUT);
    // pinMode(2, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
    ESP32_blelib::init(&pCharacteristicTX,&pCharacteristicRX);
    // std::string prefix = "T";
    while(1){
        if(xQueueReceive(comQueue, &data, pdMS_TO_TICKS(100)) == pdPASS){
            if(data.rfind("M",0) == 0) xQueueSend(motorQueue, &data, portMAX_DELAY);
            if(data.rfind("T",0) == 0) xQueueSend(motorQueue, &data, portMAX_DELAY);
            if(data == "SENSOR_ON") ifSensor = true;
            if(data == "SENSOR_OFF"){
                ifSensor = false;
                obstacle = false;
            } 
            if(data.rfind("L",0) == 0) xQueueSend(ledQueue, &data, portMAX_DELAY);
            // pCharacteristicTX.setValue(data);
            // pCharacteristicTX.notify();
        }
        if(xQueueReceive(sensorQueue, &measured_data, pdMS_TO_TICKS(100)) == pdPASS){
            pCharacteristicTX.setValue(measured_data);
            pCharacteristicTX.notify();
            Serial.println(measured_data);
        }
    }
}