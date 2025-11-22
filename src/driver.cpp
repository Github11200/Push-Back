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
    wait(400, msec);
  }
}

void Driver::buttonsLoopCallback()
{
  if (IntakeButton.pressing() || HighGoalScoreButton.pressing() || MiddleGoalScoreButton.pressing())
  {
    cout << "intake forward" << endl;
    intake.spinFullIntake(vex::directionType::fwd);
  }
  else if (OuttakeButton.pressing() || OuttakeWithHoodUpButton.pressing())
  {
    cout << "intake reversing" << endl;
    intake.spinFullIntake(vex::directionType::rev);
  }
  else
  {
    cout << "intake stopping" << endl;
    intake.stopFullIntake();
  }

  if (HighGoalScoreButton.pressing() || OuttakeWithHoodUpButton.pressing())
    sloper.on();
  else
    sloper.off();

  if (MiddleGoalScoreButton.pressing())
    blocker.on();
  else
    blocker.off();
}

void Driver::pistonsLoopCallback()
{
  pistonPressing(willyNilly, WillyNillyButton);
  pistonToggle(finger, FingerButton);
}