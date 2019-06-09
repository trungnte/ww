#include <Arduino.h>
#include "raw_sensor.h"
#include "fsm.h"

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void test_board(){
    // read the analog in value:
    sensorValue = analogRead(analogInPin);
    // map it to the range of the analog out:
    outputValue = map(sensorValue, 0, 1023, 0, 255);
    // change the analog out value:
    analogWrite(analogOutPin, outputValue);

    // print the results to the Serial Monitor:
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("\t output = ");
    Serial.println(outputValue);
}

void setup() {
    // put your setup code here, to run once:
    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    // initialize serial communications at 9600 bps:
    Serial.begin(9600);

    RainSensor.snsInit(A0);
}

void loop() {
    RainSensor.snsTickLoop();
    // Serial.print("ADC: ");
    // Serial.print(RainSensor.snsGetValue());

    // put your main code here, to run repeatedly:
    // turn the LED on (HIGH is the voltage level)
    // digitalWrite(LED_BUILTIN, HIGH);

    // test_board();
    // TestFsm(1);

    // wait for a second
    // delay(1000);

    // turn the LED off by making the voltage LOW
    // digitalWrite(LED_BUILTIN, LOW);

    // test_board();
    // TestFsm(0);

    // wait for a second
    // delay(1000);
}