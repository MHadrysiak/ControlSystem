#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <ESP32_blelib.hh>
#include "../include/tasks.h"
#include "freertos/FreeRTOS.h"

QueueHandle_t comQueue, motorQueue, sensorQueue,ledQueue;
bool ifSensor = false;
bool obstacle = false; 
bool deviceConnected;
int distance;
int t = 0;
// SemaphoreHandle_t mutex;
void setup(){
    Serial.begin(115200);
    
    sensorQueue = xQueueCreate(10, sizeof(int));
    ledQueue = xQueueCreate(10, sizeof(char[15]));
    comQueue = xQueueCreate(40, sizeof(char[15]));
    motorQueue = xQueueCreate(10, sizeof(char[15]));
    // mutex = xSemaphoreCreateMutex();
    pinMode(SENSOR, INPUT);
    xTaskCreatePinnedToCore(motorHandler, "Motor handling task", 8192, NULL, 2, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(ledHandler, "LED handling task", 8192, NULL, 2, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(sensorHandler, "Sensor handling task", 8192, NULL, 7, NULL, APP_CPU_NUM);
    xTaskCreatePinnedToCore(comHandler, "Communication handling task", 8192, NULL, 5, NULL, PRO_CPU_NUM);

}

void loop(){
    vTaskDelete(NULL);
}
