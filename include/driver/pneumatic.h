#ifndef PNEUMATICS_H
#define PNEUMATICS_H

#include "vex.h"

class Pneumatic {
private:
  vex::digital_out &piston;

public:
  void toggle();
  Pneumatic(vex::digital_out &piston_in);
};

#endif