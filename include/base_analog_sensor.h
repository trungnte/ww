
#ifndef _WW_BASE_ANALOG_SENSOR_H__
#define _WW_BASE_ANALOG_SENSOR_H__

#define BASE_SENSOR_INTERVAL            100 // ms
#define BASE_SENSOR_NUMBER_SAMPLE       10

class BaseAnalogSensor{
  public:
    // Constructor
    BaseAnalogSensor(){}
    // Destructor      
    ~BaseAnalogSensor(){}

    // Initialization method
    virtual void snsInit(uint8_t pin) {}

    // Loop-like method -> read value and update 
    virtual void snsTickLoop() {}

    // Descriptive name of the sensor
    virtual String snsDescription() = 0;

    // Set interval read value
    // virtual void snsSetInterval(uint16_t intervalMs) {}

    // Set number of sample
    // virtual void snsNOSample(uint8_t nSample) {}

    // Get value
    virtual int snsGetValue() = 0;

    // Return ready status (true for ready)
    bool ready() { return _ready; }
    
  protected:
    // interval
    uint16_t _interval = BASE_SENSOR_INTERVAL; // ms
    // number of sample
    uint8_t _numSample = BASE_SENSOR_NUMBER_SAMPLE;
    // ready
    bool _ready = false;

};


#endif //_WW_BASE_ANALOG_SENSOR_H__