
#ifndef _WW_RAW_SENSOR_H__
#define _WW_RAW_SENSOR_H__
#include <Arduino.h>
#include "base_analog_sensor.h"

class RawSensor
{
  public:
    RawSensor();
    void snsInit(uint8_t pin); 
    void snsTickLoop();
    String snsDescription();
    int snsGetValue();

  protected: 
    void _readRawData();
    
  private:
    uint8_t _pin;
    uint8_t _index;
    int _aRawData[BASE_SENSOR_NUMBER_SAMPLE];
    int _avgValue;
    
    unsigned long _prevTime2Read;
};

extern RawSensor RainSensor;

#endif //_WW_RAW_SENSOR_H__