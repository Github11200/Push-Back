#ifndef DRIVER_H
#define DRIVER_H

#include "subsystems/intake.h"
#include "subsystems/joysticks.h"
#include "subsystems/pneumatic.h"

class Driver
{
private:
  Joysticks joysticks;
  Intake intake;

  vex::controller::button intakeButton;
  vex::controller::button outtakeButton;
  vex::controller::button willyNillyButton;
  vex::controller::button fingerButton;
  vex::controller::button sloperButton;
  vex::controller::button blockerButton;

  void pistonPressing(Pneumatic &piston, vex::controller::button pistonButton);

public:
  Driver(vex::controller::button intakeButton,
         vex::controller::button outtakeButton,
         vex::controller::button willyNillyButton,
         vex::controller::button fingerButton,
         vex::controller::button sloperButton,
         vex::controller::button blockerButton);

  void startJoysticksThread();
  void buttonsLoopCallback();
};

#endif