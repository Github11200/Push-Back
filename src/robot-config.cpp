#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller;

motor FrontRight = motor(PORT18, ratio6_1, false); // Done
motor FrontLeft = motor(PORT13, ratio6_1, true);   // Done
motor MiddleRight = motor(PORT20, ratio6_1, true); // Done
motor MiddleLeft = motor(PORT11, ratio6_1, false); // Done
motor BackRight = motor(PORT19, ratio6_1, false);  // Done
motor BackLeft = motor(PORT12, ratio6_1, true);    // Done

motor TopIntake = motor(PORT10, ratio6_1, false);  // Done
motor BottomIntake = motor(PORT1, ratio6_1, true); // Done

vex::distance frontDistance = vex::distance(PORT16); // Done
vex::distance rightDistance = vex::distance(PORT8);  // Done
vex::distance leftDistance = vex::distance(PORT2);   // Done

motor_group Left = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor_group Right = motor_group(FrontRight, MiddleRight, BackRight);

vex::controller::button IntakeButton = Controller.ButtonR1;
vex::controller::button OuttakeButton = Controller.ButtonR2;
vex::controller::button WillyNillyButton = Controller.ButtonA;
vex::controller::button FingerButton = Controller.ButtonB;
vex::controller::button SloperButton = Controller.ButtonX;
vex::controller::button BlockerButton = Controller.ButtonY;

bool stopPlease = false;

void vexcodeInit(void)
{
  // nothing to initialize
}