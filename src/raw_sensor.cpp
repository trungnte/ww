#include <Arduino.h>

#include "base_analog_sensor.h"

#define DEBUG_WINDSHIELD_WIPER

#ifdef DEBUG_WINDSHIELD_WIPER
#define DEBUG_WW_PORT Serial.print
#else
#define DEBUG_WW_PORT
#endif

class RawSensor: public BaseAnalogSensor
{
  public:
    RawSensor(): BaseAnalogSensor()
    {
        DEBUG_WW_PORT("Constructor RawSensor\n");
    }

    void snsInit(uint8_t pin) 
    {
        _pin = pin;
        _ready = true;
    }

    void snsTickLoop() 
    {
        // TODO:
        _readRawData();
    }

    String snsDescription()
    {
        return "RawSensor";
    }

    // void snsSetInterval(uint16_t intervalMs) 
    // {
    //     _interval = intervalMs;
    // }

    // void snsNOSample(uint8_t nSample) 
    // {
    //     _numSample = nSample;
    // }

    int snsGetValue()
    {
        return _avgValue;
    }

  protected:
    
    void _readRawData()
    {
        // read and calc
        int rawValue = 0;
        unsigned long now = millis();
        if(!_ready)
        {
            return;
        }

        if((now - _prevTime2Read) >= BASE_SENSOR_INTERVAL)
        {
            rawValue = analogRead(_pin);

            _aRawData[_index++] = rawValue;
            _index = _index%_numSample;
            if(_index == 0)
            {
                int sum = 0;
                for(uint8_t i = 0; i < _numSample; i++)
                {
                    sum += _aRawData[i];
                }
                _avgValue = sum/_numSample;

                // // Serial.print("ADC: ");
                // Serial.print(_avgValue);
                // Serial.print(" ");
            }
            _prevTime2Read = now;

            if(_index >= 5)
            {
                if(!_ledState)  
                {
                    _ledState = 1;
                    digitalWrite(LED_BUILTIN, HIGH);
                }
                else
                {
                    _ledState = 0;
                    digitalWrite(LED_BUILTIN, LOW);
                }
            }
        }

    }

  private:
    uint8_t _pin;
    uint8_t _index = 0;
    int _aRawData[BASE_SENSOR_NUMBER_SAMPLE];
    int _avgValue = 0;
    
    unsigned long _prevTime2Read = 0;

    uint8_t _ledState = 0;
};

RawSensor RainSensor, UserMode, SpeedSensor;
