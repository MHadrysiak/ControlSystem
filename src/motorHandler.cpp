#include <Arduino.h>
#include "../include/tasks.h"

std::string message;
// std::string data;
extern QueueHandle_t comQueue;
extern QueueHandle_t motorQueue;
extern bool obstacle, deviceConnected;
void motorHandler(void *arg){
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
    pinMode(ENABLE_A, OUTPUT);
    pinMode(ENABLE_B, OUTPUT);
    // ledcSetup(CHANNEL, FREQ, RES);
    // ledcAttachPin(ENABLE_A, CHANNEL);
    // ledcAttachPin(ENABLE_B, CHANNEL);
    int flag = 0;
    int dutyCycle = 250;
    while(1){
        if(xQueueReceive(motorQueue, &message, pdMS_TO_TICKS(100)) == pdPASS){
            if(dutyCycle > 250) dutyCycle = 250;
            if(message == "T2"){
                digitalWrite(IN_1, HIGH);
                digitalWrite(IN_2, LOW);
                digitalWrite(ENABLE_A, HIGH);
                // ledcWrite(CHANNEL, 250);
            }else if (message == "T0"){
                digitalWrite(IN_1, LOW);
                digitalWrite(IN_2, LOW);
                // ledcWrite(CHANNEL, 0);
                digitalWrite(ENABLE_A, LOW);
            }else if(message == "T1"){
                digitalWrite(IN_1, LOW);
                digitalWrite(IN_2, HIGH);
                // ledcWrite(CHANNEL, 250);
                digitalWrite(ENABLE_A, HIGH);
            }else if(message == "M1" && obstacle == false){
                digitalWrite(IN_3, HIGH);
                digitalWrite(IN_4, LOW);
                // ledcWrite(CHANNEL, 250);
                digitalWrite(ENABLE_B, HIGH);
            }else if (message == "M0"){
                digitalWrite(IN_3, LOW);
                digitalWrite(IN_4, LOW);
                // ledcWrite(CHANNEL, 0);
                digitalWrite(ENABLE_B, LOW);
            }else if(message == "M2"){
                digitalWrite(IN_3, LOW);
                digitalWrite(IN_4, HIGH);
                // ledcWrite(CHANNEL, 250);
                digitalWrite(ENABLE_B, HIGH);
            }else if(message == "STOP" && deviceConnected){
                digitalWrite(IN_3, LOW);
                digitalWrite(IN_4, HIGH);
                digitalWrite(ENABLE_B, HIGH);
                delay(100);
                digitalWrite(IN_3, LOW);
                digitalWrite(IN_4, LOW); 
                digitalWrite(ENABLE_B, LOW);
            }
        }
        if(!deviceConnected){
                digitalWrite(IN_3, LOW);
                digitalWrite(IN_4, LOW);
                digitalWrite(ENABLE_B, LOW);
                digitalWrite(IN_1, LOW);
                digitalWrite(IN_2, LOW);
                digitalWrite(ENABLE_A, LOW);
        }
    }
}