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

void Driver::pistonPressing(digital_out &piston, vex::controller::button pistonButton)
{
  while (pistonButton.pressing())
  {
    piston.set(true);
    wait(200, msec);
  }
  piston.set(false);
}

void Driver::buttonsLoopCallback()
{
  if (IntakeButton.pressing())
    intake.spinFullIntake(vex::directionType::fwd);
  if (OuttakeButton.pressing())
    intake.spinFullIntake(vex::directionType::rev);
  if (!IntakeButton.pressing() && !OuttakeButton.pressing())
    intake.stopFullIntake();

  // finger.on();
  pistonPressing(willyNilly, WillyNillyButton);
  // pistonPressing(finger, FingerButton);
  // pistonPressing(sloper, SloperButton);
  // pistonPressing(blocker, BlockerButton);
}