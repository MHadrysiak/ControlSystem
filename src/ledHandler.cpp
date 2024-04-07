#include <Arduino.h>
#include "../include/tasks.h"
#include <EchoServerCallbacks.hh>

int onTime;
int lights = 0;
std::string state;
extern QueueHandle_t ledQueue;
extern bool obstacle, deviceConnected;

void flash(int color){
    digitalWrite(color, HIGH);
    delay(250);
    digitalWrite(color, LOW);
    delay(250);
}

void turnOnLights(){
    digitalWrite(FRONTLIGHT, HIGH);
    digitalWrite(BACKLIGHT, HIGH);
}

void turnOffLights(){
    digitalWrite(FRONTLIGHT, LOW);
    digitalWrite(BACKLIGHT, LOW);
}

void ledHandler(void *arg){
    while(1){
        if(xQueueReceive(ledQueue, &state, pdMS_TO_TICKS(100)) == pdPASS){
            Serial.println(state[0]);
            if(state == "LED_OFF") turnOffLights();
            if(state == "LED_ON") turnOnLights();
        }
        if(obstacle == true){ 
            flash(REDLED);
        }else if(deviceConnected == false){ 
            flash(BLUELED);
            turnOffLights();
        }else{
            flash(REDLED);
            flash(BLUELED);
        }
    }
}