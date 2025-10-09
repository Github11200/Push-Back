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
  void toggle() { piston->set(!piston->value()); };
  inline void on() { piston->set(true); };
  inline void off() { piston->set(false); };
  Pneumatic(Port port);
};

extern Pneumatic willyNilly;
extern Pneumatic winger;
extern Pneumatic sloper;
extern Pneumatic blocker;

#endif