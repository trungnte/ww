
#ifndef _FSM_WINDSHIELD_WIPER_H__
#define _FSM_WINDSHIELD_WIPER_H__

#define DEBUG_WINDSHIELD_WIPER

#ifdef DEBUG_WINDSHIELD_WIPER
#define DEBUG_WW_PORT Serial.print
#else
#define DEBUG_WW_PORT
#endif

#define FSM_TIME_TO_CHECK_SENSOR    500


typedef enum __RelayLevel{
    E_RELAY_LEVEL_OFF = 0,
    E_RELAY_LEVEL_LOW,
    E_RELAY_LEVEL_HIGH,
    E_RELAY_LEVEL_MAX
}E_RELAYLEVEL_t;


class WindshieldWiper{
  class State *current;
  public:
    WindshieldWiper();
    virtual ~WindshieldWiper();
    void setCurrent(State *s);
    void triggerRelay();
};

class State{
  public:
    virtual void triggerRelay(WindshieldWiper *ww)
    {
        DEBUG_WW_PORT("-> Virtual triggerRelay\n");
    };
};
class OffRelayState: public State{
  public:
    OffRelayState();
    virtual ~OffRelayState();
    void triggerRelay(WindshieldWiper *ww);
};

class LowRelayState: public State
{
  public:
    LowRelayState();
    virtual ~LowRelayState();
    void triggerRelay(WindshieldWiper *ww);
};

class HighRelayState: public State
{
  public:
    HighRelayState();
    virtual ~HighRelayState();
    void triggerRelay(WindshieldWiper *ww);
};

// extern WindshieldWiper windshieldWiper;

void fsmMainLoop();

// void TestFsm(int i);


#endif //_FSM_WINDSHIELD_WIPER_H__