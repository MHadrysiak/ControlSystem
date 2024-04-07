#include <Arduino.h>
#include "../include/tasks.h"

extern QueueHandle_t pwmQueue;
extern QueueHandle_t respondQueue;
extern int STANDARD_TEMPERATURE;
int output = 0;

// void tempHandler(void *arg){
//     float milliVolt = 0;
//     int temperature = 0;
//     float prev = 0;
//     while(1){
//         output = analogRead(TEMP);
//         milliVolt = output * (ADC_VREF_mV / ADC_RESOLUTION);
//         temperature = (int)milliVolt + 4;
//         if(temperature != prev){
//             if(temperature >= STANDARD_TEMPERATURE){
//                 xQueueSend(pwmQueue, &temperature, portMAX_DELAY);
//                 prev = temperature;
//                 //Serial.println(temperature);
//             }
//             xQueueSend(respondQueue, &temperature, portMAX_DELAY);
//         }
//         //Serial.println(temperature);
//         delay(1000);
//     }
// }