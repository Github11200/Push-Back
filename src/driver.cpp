#include "driver.h"

using namespace std;
using namespace vex;

void Driver::startJoysticksThread()
{
  static Joysticks staticJoysticks = joysticks;
  thread([]()
         { while (true) {
            staticJoysticks.arcade();
            wait(50, msec);
          } });
}

void Driver::startPistonsThread()
{
  static Driver staticDriver = *this;
  thread([]()
         { while (true) {
            staticDriver.pistonsLoopCallback();
            wait(50, msec);
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
    while (pistonButton.pressing())
    {
      wait(50, msec);
    }
  }
}

void Driver::buttonsLoopCallback()
{
  if (IntakeButton.pressing() || HighGoalScoreButton.pressing() || MiddleGoalScoreButton.pressing())
  {
    intake.spinFullIntake(vex::directionType::fwd);
    // Comment in for skills
    // if (MiddleGoalScoreButton.pressing())
    //   IntakeRear.spin(vex::directionType::fwd, 4, vex::voltageUnits::volt); // BRANDON HERE IS MIDDLE GOAL SPEED
  }
  else if (OuttakeButton.pressing())
  {
    intake.spinFullIntake(vex::directionType::rev);
    // Comment in for skills
    // IntakeFront.spin(vex::directionType::rev, 4, vex::voltageUnits::volt); // BRANDON HERE IS LOW GOAL SPEED
  }
  else
    intake.stopFullIntake();

  if (MiddleGoalScoreButton.pressing() || HoodToggleButton.pressing())
    sloper.off();
  else
    sloper.on();

  if (HighGoalScoreButton.pressing() || MiddleGoalScoreButton.pressing())
    blocker.on();
  else
    blocker.off();

  if (OuttakeButton.pressing())
    razer.on();
  else
    razer.off();
}

void Driver::pistonsLoopCallback()
{
  pistonPressing(willyNilly, WillyNillyButton);
  pistonToggle(finger, FingerButton);
}