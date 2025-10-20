#ifndef JOYSTICKS_H
#define JOYSTICKS_H

#include "vex.h"
#include "../utils/utils.h"

class Joysticks
{
private:
  void control(double power, double turning);
  double curve(double input, double curveValue);

public:
  void arcade();
  void tank();
};

#endif