#ifndef _WW_RELAY_H__
#define _WW_RELAY_H__

#include <Arduino.h>
// TODO: Implement class RelayCtl 
#define RELAY_LOW           9
#define RELAY_HIGH          10

#define TURN_ON             LOW
#define TURN_OFF            HIGH

// TODO: Implement :D
#define USER_MODE_PIN           7       // 1: Auto 0: Off
#define SPEED_MODE_PIN          6       // 1: High speed, 0: low speed

void relayInit(void);
uint8_t kickRelays(uint8_t state);



#endif //_WW_RELAY_H__