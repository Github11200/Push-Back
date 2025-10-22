#include "../include/driver.h"

using namespace std;
using namespace vex;

void Driver::startJoysticksThread()
{
  static Joysticks staticJoysticks = joysticks;
  thread([]()
         { while (true) {
            staticJoysticks.arcade();
          } });
}

void Driver::startPistonsThread()
{
  static Driver staticDriver = *this;
  thread([]()
         { while (true) {
            staticDriver.pistonsLoopCallback();
          } });
}

void Driver::pistonPressing(Pneumatic &piston, vex::controller::button pistonButton)
{
  while (pistonButton.pressing())
  {
    piston.on();
    wait(200, msec);
  }
  piston.off();
}

void Driver::pistonToggle(Pneumatic &piston, vex::controller::button pistonButton)
{
  if (pistonButton.pressing())
  {
    piston.toggle();
    wait(100, msec);
  }
}

void Driver::buttonsLoopCallback()
{
  if (IntakeButton.pressing())
    intake.spinFullIntake(vex::directionType::fwd);
  if (OuttakeButton.pressing())
    intake.spinFullIntake(vex::directionType::rev);

  if (HighGoalScoreButton.pressing())
  {
    blocker.on();
    wait(50, msec);
    sloper.on();
    wait(50, msec);
    intake.spinFullIntake(vex::directionType::fwd);
  }
  else
    sloper.off();

  if (MiddleGoalScoreButton.pressing())
  {
    blocker.on();
    wait(100, msec);
    intake.spinFullIntake(vex::directionType::fwd);
  }
  else
    blocker.off();

  if (!IntakeButton.pressing() && !HighGoalScoreButton.pressing() && !MiddleGoalScoreButton.pressing() && !OuttakeButton.pressing())
    intake.stopFullIntake();
}

void Driver::pistonsLoopCallback()
{
  pistonPressing(willyNilly, WillyNillyButton);
  pistonToggle(finger, FingerButton);
}