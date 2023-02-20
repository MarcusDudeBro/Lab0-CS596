#include <Servo.h>
#include <Arduino.h>

Servo myservo;
uint16_t maxValue;
uint16_t minValue;
float brightness;
int inPin = GPIO_NUM_27;
int outPin = GPIO_NUM_33;
// Tried using GPIO_NUM_37 but didn't work, why?
int ledPin = GPIO_NUM_17;
unsigned long startTime;
float prevTime;

void setup() {
	Serial.begin(9600);
	pinMode(inPin, INPUT);
	pinMode(ledPin, OUTPUT);
	maxValue = 0;
	minValue = INFINITY;
	myservo.attach(outPin);
	startTime = millis();
	prevTime = millis();
}

void loop() {
	uint16_t value = analogRead(inPin);
	if(millis() - startTime < 10000){
		if(value < minValue) minValue = value;
		if(value > maxValue) maxValue = value;
		if(millis()-prevTime >= 2000){
			prevTime = millis();
			digitalWrite(ledPin, LOW);
		} else if (millis()-prevTime >= 1000){
			digitalWrite(ledPin, HIGH);
		}
	} else {
		brightness = float(value - minValue)/(maxValue - minValue);
		if(brightness > 1) brightness = 1.0;
		myservo.write(brightness*179);
		Serial.print(value); Serial.print(" "); Serial.println(brightness);
	}
}