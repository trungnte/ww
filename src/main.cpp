#include <Arduino.h>
#include "raw_sensor.h"
#include "fsm_ww.h"
#include "relay.h"





void setup() {
    // put your setup code here, to run once:
    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(USER_MODE_PIN, OUTPUT);
    pinMode(SPEED_MODE_PIN, OUTPUT);

    // initialize serial communications at 9600 bps:
    Serial.begin(9600);

    // Rain Sensor
    RainSensor.snsInit(A0);
    // Variable Sensor -> UserMode
    UserMode.snsInit(A1);
    // Speed Sensor
    SpeedSensor.snsInit(A2);
    relayInit();
}

void loop() {
    RainSensor.snsTickLoop();
    UserMode.snsTickLoop();
    SpeedSensor.snsTickLoop();

    fsmMainLoop();
}