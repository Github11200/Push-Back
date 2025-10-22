#ifndef DRIVER_H
#define DRIVER_H

#include "subsystems/intake.h"
#include "subsystems/joysticks.h"
#include "subsystems/pneumatic.h"
#include "vex.h"

class Driver
{
private:
  Joysticks joysticks;
  Intake intake;

  void pistonPressing(Pneumatic &piston, vex::controller::button pistonButton);
  void pistonToggle(Pneumatic &piston, vex::controller::button pistonButton);

public:
  void startJoysticksThread();
  void startPistonsThread();
  void buttonsLoopCallback();
  void pistonsLoopCallback();
};

#endif