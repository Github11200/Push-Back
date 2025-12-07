#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller;

motor FrontRight = motor(PORT15, ratio6_1, false); // Done
motor FrontLeft = motor(PORT18, ratio6_1, true);   // Done
motor MiddleRight = motor(PORT20, ratio6_1, true); // Done
motor MiddleLeft = motor(PORT16, ratio6_1, false); // Done
motor BackRight = motor(PORT17, ratio6_1, false);  // Done
motor BackLeft = motor(PORT13, ratio6_1, true);    // Done

motor TopIntake = motor(PORT10, ratio6_1, false);  // Done
motor BottomIntake = motor(PORT2, ratio6_1, true); // Done

vex::distance frontDistance = vex::distance(PORT1); // Done
vex::distance rightDistance = vex::distance(PORT6); // Done
vex::distance leftDistance = vex::distance(PORT5);  // Done
// vex::distance backDistance = vex::distance(PORT14); //

motor_group Left = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor_group Right = motor_group(FrontRight, MiddleRight, BackRight);

vex::controller::button IntakeButton = Controller.ButtonL1;
vex::controller::button OuttakeButton = Controller.ButtonR1;
vex::controller::button WillyNillyButton = Controller.ButtonB;
vex::controller::button FingerButton = Controller.ButtonDown;
vex::controller::button HighGoalScoreButton = Controller.ButtonR2;
vex::controller::button MiddleGoalScoreButton = Controller.ButtonL2;
vex::controller::button MiddleGoalSlowScoreButton = Controller.ButtonY;

bool stopPlease = false;

void vexcodeInit(void)
{
  // nothing to initialize
}