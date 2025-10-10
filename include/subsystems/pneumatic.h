#ifndef PNEUMATICS_H
#define PNEUMATICS_H

#include "vex.h"

enum Port
{
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  H
};

class Pneumatic
{
private:
  vex::digital_out *piston;

public:
  inline void toggle() { piston->set(!piston->value()); };
  inline void on() { piston->set(true); };
  inline void off() { piston->set(false); };

  void killThread(vex::thread *currentDelayThread);
  void delayToggle(int millseconds);

  Pneumatic(Port port);
};

extern Pneumatic willyNilly;
extern Pneumatic finger;
extern Pneumatic sloper;
extern Pneumatic blocker;

#endif