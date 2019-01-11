#include "Scheduler.h"

const int LED_PIN = 13;
int LED_VALUE = 0;

arc::Scheduler scheduler;

void toggleLed(arc::Scheduler &scheduler){
    LED_VALUE = (LED_VALUE + 1) % 2;
    digitalWrite(LED_PIN, LED_VALUE);
}

void setup(){
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LED_VALUE);
    for(int i=1;i<=10;i+=2){
        scheduler.timeout(500*i, toggleLed);    
        scheduler.timeout(500*(i+1), toggleLed);
    }
    scheduler.every(1000, [](arc::Scheduler& scheduler){
        scheduler.debug(Serial);
    });
}

void loop(){
    scheduler.loop();
}