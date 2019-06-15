#include <Arduino.h>
#include "raw_sensor.h"
#include "sensor_update.h"


// dirty fix
#include "relay.h"

int getUserMode()
{
    // UserMode.snsGetValue();
    int usermode =  digitalRead(USER_MODE_PIN);
    if(usermode){
        return E_USER_MODE_AUTO;
    }
    return E_USER_MODE_OFF;
}

int getRainData()
{
    // return RainSensor.snsGetValue();
    // wet -> ~300
    // lightweight ~600
    // dry 900
    int rainData = RainSensor.snsGetValue();
    Serial.print(rainData);
    Serial.print(" ");
    if(rainData <= 500)
    {
        return E_RAIN_LEVEL_HEAVY;
    }
    else if(rainData <= 800)
    {
        return E_RAIN_LEVEL_LIGHTWEIGHT;
    }
    return E_RAIN_LEVEL_DRY;
}

int getSpeedData()
{
    // return SpeedSensor.snsGetValue();
    // return E_SPEED_LEVEL_HIGH;
    int speed = digitalRead(SPEED_MODE_PIN);
    if(speed)
    {
        return E_SPEED_LEVEL_HIGH;
    }
    return E_SPEED_LEVEL_LOW;
}

