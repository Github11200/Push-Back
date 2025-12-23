#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller;

motor FrontRight = motor(PORT19, ratio6_1, false); // Done
motor FrontLeft = motor(PORT12, ratio6_1, true);   // Done
motor MiddleRight = motor(PORT18, ratio6_1, true); // Done
motor MiddleLeft = motor(PORT13, ratio6_1, false); // Done
motor BackRight = motor(PORT20, ratio6_1, false);  // Done
motor BackLeft = motor(PORT11, ratio6_1, true);    // Done

motor IntakeLeft = motor(PORT10, ratio6_1, false); // Done
motor IntakeRight = motor(PORT3, ratio6_1, false); // Done

vex::distance frontDistance = vex::distance(PORT1); // Done
vex::distance rightDistance = vex::distance(PORT9); // Done
vex::distance leftDistance = vex::distance(PORT2);  // Done

vex::rotation ForwardTracker = vex::rotation(PORT6);
vex::rotation SidewaysTracker = vex::rotation(PORT5, true);

vex::inertial Inertial = vex::inertial(PORT1);

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