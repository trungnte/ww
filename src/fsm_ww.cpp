#include <Arduino.h>

#include "fsm_ww.h"
#include "sensor_update.h"
#include "relay.h"


uint8_t autoModeCheckTriggerRelay(void)
{
    uint8_t ret = 0;
    E_RAINLEVEL_t eRainLvl = (E_RAINLEVEL_t)getRainData();
    E_SPEEDLEVEL_t eSpeedLvl = (E_SPEEDLEVEL_t)getSpeedData();
    switch (eRainLvl)
    {
    case E_RAIN_LEVEL_DRY:
        ret = (uint8_t)E_RELAY_LEVEL_OFF;
        break;
    case E_RAIN_LEVEL_LIGHTWEIGHT:
        // if(eSpeedLvl == E_SPEED_LEVEL_LOW)
        // {
        //     ret = (uint8_t)E_RELAY_LEVEL_LOW;
        // }
        // else
        // {
        //     ret = (uint8_t)E_RELAY_LEVEL_HIGH;
        // }
        ret = (uint8_t)E_RELAY_LEVEL_LOW;
        break;
    case E_RAIN_LEVEL_HEAVY:
        ret = (uint8_t)E_RELAY_LEVEL_HIGH;
        // if(eSpeedLvl == E_SPEED_LEVEL_LOW)
        // {
        //     ret = (uint8_t)E_RELAY_LEVEL_HIGH;
        // }
        // else
        // {
        //     ret = (uint8_t)E_RELAY_LEVEL_HIGH;
        // }
        break;
    default:
        ret = (uint8_t)E_RELAY_LEVEL_OFF;
        break;
    }
    return ret;
}

// The WindshieldWiper class acts as a context. It also maintains a
// reference to an instance of one of the state classes that
// represents the current state of the WindshieldWiper.

// class WindshieldWiper
// {
//   class State *current;
//   public:
//     WindshieldWiper();
//     virtual ~WindshieldWiper();
//     void setCurrent(State *s)
//     {
//         current = s;
//     }
//     void triggerRelay();
// };

void WindshieldWiper::setCurrent(State *s)
{
    current = s;
}

WindshieldWiper::WindshieldWiper()
{
    current = new OffRelayState();
}

WindshieldWiper::~WindshieldWiper()
{
    delete current;
}


// ----------------------------------------------------------------------------
// State class: abstract class -> interface
// ----------------------------------------------------------------------------
// The base state class declares methods that all concrete
// states should implement and also provides a backreference to
// the context object associated with the state. States can use
// the backreference to transition the context to another state.

// class State
// {
//   public:
//     // virtual State(){};
//     // virtual ~State(){};
//     virtual void triggerRelay(WindshieldWiper *ww)
//     {
//         DEBUG_WW_PORT("-> Virtual triggerRelay\n");
//     }
// };

void WindshieldWiper::triggerRelay()
{
    current->triggerRelay(this);
}

// Concrete states implement various behaviors associated with a
// state of the context.

OffRelayState::OffRelayState()
{
    // Trigger relay off
    DEBUG_WW_PORT("--> Trigger all Relays OFF!\n");
    kickRelays(0);
    // TODO: Fix me
}

OffRelayState::~OffRelayState()
{
    // Trigger relay off
    DEBUG_WW_PORT("Destructor OffRelayState\n");
    // TODO: Fix me
}



void OffRelayState::triggerRelay(WindshieldWiper *ww)
{
    E_USERMODE_t eUserMode =  (E_USERMODE_t)getUserMode();
    switch(eUserMode)
    {
        case E_USER_MODE_OFF:
            // Turn on all relays
            // ww->setCurrent(new OffRelayState());
            DEBUG_WW_PORT("--> MOff Already OFF!\n");
            break;
        case E_USER_MODE_AUTO:
            // Check rain sensor and speed
            E_RELAYLEVEL_t eRelayState = (E_RELAYLEVEL_t)autoModeCheckTriggerRelay();
            if(eRelayState == E_RELAY_LEVEL_LOW)
            {
                DEBUG_WW_PORT("--> MAuto Change from OFF to LOW!\n");
                ww->setCurrent(new LowRelayState());
                delete this;
            }
            else if(eRelayState == E_RELAY_LEVEL_HIGH)
            {
                DEBUG_WW_PORT("--> MAuto Change from OFF to HIGH!\n");
                ww->setCurrent(new HighRelayState());
                delete this;
            }
            else
            {
                DEBUG_WW_PORT("--> MAuto Already OFF!\n");
            }
            break;
        case E_USER_MODE_LOW:
            DEBUG_WW_PORT("--> MLow Change from OFF to LOW!\n");
            ww->setCurrent(new LowRelayState());
            delete this;
            break;
        case E_USER_MODE_HIGH:
            DEBUG_WW_PORT("--> MHigh Change from OFF to HIGH!\n");
            ww->setCurrent(new HighRelayState());
            delete this;
            break;
        default:
            // new user mode add here
            DEBUG_WW_PORT("--> MOff Already OFF!\n");
            break;
    }
}



///////////////////////////////////////////////////////////////////////////////
// State Relay Low
LowRelayState::LowRelayState()
{
    // Trigger relay off
    DEBUG_WW_PORT("--> Trigger all Relays LOW!\n");

    kickRelays(1);

    // TODO: Fix me
}
LowRelayState::~LowRelayState()
{
    DEBUG_WW_PORT("Destructor LowRelayState\n");
}

void LowRelayState::triggerRelay(WindshieldWiper *ww)
{
    E_USERMODE_t eUserMode =  (E_USERMODE_t)getUserMode();
    switch(eUserMode)
    {
        case E_USER_MODE_OFF:
            DEBUG_WW_PORT("--> MOff Change from LOW to OFF!\n");
            ww->setCurrent(new OffRelayState());
            delete this;
            break;

        case E_USER_MODE_AUTO:
            // Check rain sensor and speed
            E_RELAYLEVEL_t eRelayState = (E_RELAYLEVEL_t)autoModeCheckTriggerRelay();
            if(eRelayState == E_RELAY_LEVEL_LOW)
            {
                DEBUG_WW_PORT("--> MAuto Already LOW!\n");
            }
            else if(eRelayState == E_RELAY_LEVEL_HIGH)
            {
                DEBUG_WW_PORT("--> MAuto Change from LOW to HIGH!\n");
                ww->setCurrent(new HighRelayState());
                delete this;
            }
            else
            {
                DEBUG_WW_PORT("--> MAuto Change from LOW to OFF!\n");
                ww->setCurrent(new OffRelayState());
                delete this;
            }
            break;
        case E_USER_MODE_LOW:
            DEBUG_WW_PORT("--> MLow Already LOW!\n");
            break;
        case E_USER_MODE_HIGH:
            DEBUG_WW_PORT("--> MHigh Change from LOW to HIGH!\n");
            ww->setCurrent(new HighRelayState());
            delete this;
            break;
        default:
            // new user mode add here
            DEBUG_WW_PORT("--> MDefault***** change to OFF!\n");
            ww->setCurrent(new OffRelayState());
            delete this;
            break;
    }
}


///////////////////////////////////////////////////////////////////////////////
// State Relay High

HighRelayState::HighRelayState()
{
    // Trigger relay off
    DEBUG_WW_PORT("--> Trigger all Relays HIGH!\n");
    kickRelays(2);
    // TODO: Fix me
}
HighRelayState::~HighRelayState()
{
    DEBUG_WW_PORT("Destructor HighRelayState\n");
}

void HighRelayState::triggerRelay(WindshieldWiper *ww)
{
    E_USERMODE_t eUserMode =  (E_USERMODE_t)getUserMode();
    switch(eUserMode)
    {
        case E_USER_MODE_OFF:
            DEBUG_WW_PORT("--> MOff Change from HIGH to OFF!\n");
            ww->setCurrent(new OffRelayState());
            delete this;
            break;

        case E_USER_MODE_AUTO:
            // Check rain sensor and speed
            E_RELAYLEVEL_t eRelayState = (E_RELAYLEVEL_t)autoModeCheckTriggerRelay();
            if(eRelayState == E_RELAY_LEVEL_LOW)
            {
                DEBUG_WW_PORT("--> MAuto Change from HIGH to LOW!\n");
                ww->setCurrent(new LowRelayState());
                delete this;
            }
            else if(eRelayState == E_RELAY_LEVEL_HIGH)
            {
                DEBUG_WW_PORT("--> MAuto Already HIGH!\n");
            }
            else
            {
                DEBUG_WW_PORT("--> MAuto Change from HIGH to OFF!\n");
                ww->setCurrent(new OffRelayState());
                delete this;
            }
            break;
        case E_USER_MODE_LOW:
            DEBUG_WW_PORT("--> MLow Change from HIGH to LOW!\n");
            ww->setCurrent(new LowRelayState());
            delete this;
            break;
        case E_USER_MODE_HIGH:
            DEBUG_WW_PORT("--> MHigh Already HIGH!\n");
            break;
        default:
            // new user mode add here
            DEBUG_WW_PORT("--> MDefault***** change to OFF!\n");
            ww->setCurrent(new OffRelayState());
            delete this;
            break;
    }
}


///////////////////////////////////////////////////////////////////////////////
WindshieldWiper windshieldWiper;
static E_USERMODE_t g_eUserModePrev =  (E_USERMODE_t)getUserMode();
static E_RAINLEVEL_t g_eRainLvlPrev = (E_RAINLEVEL_t)getRainData();
static E_SPEEDLEVEL_t g_eSpeedLvlPrev = (E_SPEEDLEVEL_t)getSpeedData();
static unsigned long _prevTime2Read = 0;
void fsmMainLoop()
{

    unsigned long now = millis();
    if((now - _prevTime2Read) >= FSM_TIME_TO_CHECK_SENSOR)
    {
        E_USERMODE_t _eUserModeNow = (E_USERMODE_t)getUserMode();
        E_RAINLEVEL_t _eRainLvlNow = (E_RAINLEVEL_t)getRainData();
        E_SPEEDLEVEL_t _eSpeedLvlNow = (E_SPEEDLEVEL_t)getSpeedData();
        if((_eUserModeNow == g_eUserModePrev) \
            && (_eRainLvlNow == g_eRainLvlPrev) \
            && (_eSpeedLvlNow == g_eSpeedLvlPrev))
        {
            // do nothing
        }
        else
        {
            /* code */

            g_eUserModePrev = _eUserModeNow;
            g_eRainLvlPrev = _eRainLvlNow;
            g_eSpeedLvlPrev = _eSpeedLvlNow;
            windshieldWiper.triggerRelay();
        }
        _prevTime2Read = now; 
    }
}

