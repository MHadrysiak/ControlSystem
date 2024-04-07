#include <Arduino.h>
#include "../include/tasks.h"
#include <freertos/task.h>

extern bool ifSensor;
extern bool obstacle, deviceConnected;
extern QueueHandle_t sensorQueue;
extern SemaphoreHandle_t mutex;
extern QueueHandle_t motorQueue;
void sensorHandler(void *arg){
    int distance;
    int time = 0;
    int t = 0;
    bool first = true;
    int prev_distance;

    while(1){
        if(ifSensor && deviceConnected){
            time = pulseIn(SENSOR, HIGH);
            if(time == 0){
                distance = -1;
                Serial.println(distance);
                obstacle = false;
            }else if(time > 1850){
                distance = -1;
                Serial.println(distance);
                obstacle = false;
            }else{
                distance = (time - 1000) * 3 / 4;       
                if(distance < 0)  distance = 0;  
                if(distance > 0){
                    obstacle = true;
                    if(prev_distance != -1){
                        if(prev_distance - 10 > distance){
                            std::string stop = "STOP";
                            xQueueSend(motorQueue, &stop, portMAX_DELAY);
                        }
                    }
                }else{
                    obstacle = false;
                }
                if(prev_distance != distance){
                    xQueueSend(sensorQueue, &distance, portMAX_DELAY);
                }
                Serial.println(distance);
                prev_distance = distance;
            }
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }else{
            vTaskDelay(250 / portTICK_PERIOD_MS);
        }       
    }
}


