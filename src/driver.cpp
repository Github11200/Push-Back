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

void Driver::pistonPressing(Pneumatic &piston, vex::controller::button pistonButton)
{
  while (pistonButton.pressing())
  {
    piston.on();
    wait(200, msec);
  }
  piston.off();
}

void Driver::buttonsLoopCallback()
{
  if (IntakeButton.pressing())
    intake.spinFullIntake(vex::directionType::fwd);
  if (OuttakeButton.pressing())
    intake.spinFullIntake(vex::directionType::rev);
  if (!IntakeButton.pressing() && !OuttakeButton.pressing())
    intake.stopFullIntake();

  pistonPressing(willyNilly, WillyNillyButton);
  pistonPressing(finger, FingerButton);
  pistonPressing(sloper, SloperButton);
  pistonPressing(blocker, BlockerButton);
}