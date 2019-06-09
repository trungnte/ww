#include <Arduino.h>

#include "fsm.h"

#define DEBUG_WINDSHIELD_WIPER

#ifdef DEBUG_WINDSHIELD_WIPER
#define DEBUG_WW_PORT Serial.print
#else
#define DEBUG_WW_PORT
#endif

// Test State pattern
class Machine
{
  class State *current;
  public:
    Machine();
    void setCurrent(State *s)
    {
        current = s;
    }
    void on();
    void off();
};

class State
{
  public:
    virtual void on(Machine *m)
    {
        DEBUG_WW_PORT("   already ON\n");
    }
    virtual void off(Machine *m)
    {
        DEBUG_WW_PORT("   already OFF\n");
    }
};

void Machine::on()
{
  current->on(this);
}

void Machine::off()
{
  current->off(this);
}

class ON: public State
{
  public:
    ON()
    {
        DEBUG_WW_PORT("   ON-ctor ");
    };
    ~ON()
    {
        DEBUG_WW_PORT("   dtor-ON\n");
    };
    void off(Machine *m);
};

class OFF: public State
{
  public:
    OFF()
    {
        DEBUG_WW_PORT("   OFF-ctor ");
    };
    ~OFF()
    {
        DEBUG_WW_PORT("   dtor-OFF\n");
    };
    void on(Machine *m)
    {
        DEBUG_WW_PORT("   going from OFF to ON");
        m->setCurrent(new ON());
        delete this;
    }
};

void ON::off(Machine *m)
{
  DEBUG_WW_PORT("   going from ON to OFF");
  m->setCurrent(new OFF());
  delete this;
}

Machine::Machine()
{
  current = new OFF();
  DEBUG_WW_PORT("\n");
}
Machine fsm;
void TestFsm(int i)
{
    // void(Machine:: *ptrs[])() = 
    // {
    //     Machine::off, Machine::on
    // };
    
    // (fsm. *ptrs[i])();
    switch(i)
    {
        case 0:
            fsm.off();
            break;
        case 1:
            fsm.on();
            break;
        default:
            break;
    }
}