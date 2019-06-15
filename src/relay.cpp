#include <Arduino.h>
#include "relay.h"
// TODO: Implement class RelayCtl 
static uint8_t _relayStatePrev = 0;

void relayInit(void)
{

    pinMode(USER_MODE_PIN, INPUT_PULLUP);
    pinMode(SPEED_MODE_PIN, INPUT_PULLUP);

    pinMode(RELAY_LOW, OUTPUT);
    pinMode(RELAY_HIGH, OUTPUT);
    _relayStatePrev = 0;
    kickRelays(0);
}



uint8_t kickRelays(uint8_t state)
{
    uint8_t ret = 0, relayLow = 0, relayHigh = 0;
    if(state == 0)
    {
        relayLow = 0;
        relayHigh = 0;
    }
    else if(state == 1)
    {
        relayLow = 1;
        relayHigh = 0;
    }
    else
    {
        relayLow = 0;
        relayHigh = 1;
    }
    
    // first Off all relay
    // tranh sap nguon
    // can de can gat ve cuoi diem dung
    if(state != _relayStatePrev)
    {
        digitalWrite(RELAY_LOW, TURN_OFF);
        digitalWrite(RELAY_HIGH, TURN_OFF);
        delay(1000);
        if(state != 0)
        {
            if(state == 1)
            {
                digitalWrite(RELAY_LOW, TURN_ON);
            }
            else
            {
                digitalWrite(RELAY_HIGH, TURN_ON);
            }
        }
        _relayStatePrev = state;
    }

    ret =  (relayLow ) & 0x0F;
    ret |= ((relayHigh << 4) & 0xF0 );
    return ret;
}