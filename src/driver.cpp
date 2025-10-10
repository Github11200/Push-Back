#include "../include/driver.h"

using namespace std;
using namespace vex;

Driver::Driver(vex::controller::button intakeButton,
               vex::controller::button outtakeButton,
               vex::controller::button willyNillyButton,
               vex::controller::button fingerButton,
               vex::controller::button sloperButton,
               vex::controller::button blockerButton) : intakeButton(intakeButton),
                                                        outtakeButton(outtakeButton),
                                                        willyNillyButton(willyNillyButton),
                                                        fingerButton(fingerButton),
                                                        sloperButton(sloperButton),
                                                        blockerButton(blockerButton)
{
}

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
    piston.on();
  piston.off();
}

void Driver::buttonsLoopCallback()
{
  if (intakeButton.pressing())
    intake.spinFullIntake(vex::directionType::fwd);
  if (outtakeButton.pressing())
    intake.spinFullIntake(vex::directionType::rev);

  pistonPressing(willyNilly, willyNillyButton);
  pistonPressing(finger, fingerButton);
  pistonPressing(sloper, sloperButton);
  pistonPressing(blocker, blockerButton);
}