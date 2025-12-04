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
  vex::triport::port *pistonPort;
  vex::digital_out getPiston();
  vex::thread *currentDelayThread;

public:
  inline void toggle() { getPiston().set(!getPiston().value()); };
  inline void on() { getPiston().set(true); };
  inline void off() { getPiston().set(false); };

  void killThread();
  void delayToggle(int milliseconds);

  Pneumatic(Port port);
  ~Pneumatic();
};

extern Pneumatic willyNilly;
extern Pneumatic finger;
extern Pneumatic sloper;
extern Pneumatic blocker;

#endif