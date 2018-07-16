#include <Arduino.h>
long unsigned int seconds = 0;
long unsigned int minutes = 0;
long unsigned int hours = 0;
unsigned long interval;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //need to increment seconds at 1000 millis()
  if ((millis()-interval) >= 1000){
    seconds = ++;
    interval = millis();
  }
  if (seconds >= 60){
    seconds = 0;
    minutes ++;
  }
  if (seconds >= 3600){
    minutes = 0;
    hours ++;
  }
  if (seconds >= 86400){
    minutes = 0;
    hours = 0;
  }
  Serial.println("Hours: ");
  Serial.println(hours);
  delay(500);
  Serial.println("Minutes: ");
  Serial.println(minutes);
  delay(500);
  Serial.println("Seconds: ");
  Serial.println(seconds);
  delay(500);
}
