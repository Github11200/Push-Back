#ifndef JOYSTICKS_H
#define JOYSTICKS_H

#include "vex.h"
#include "../utils/utils.h"

class Joysticks
{
private:
  void control(double power, double turning);
  void curve(double input, double curveValue);

public:
  void arcade();
  void tank();
};

#endif