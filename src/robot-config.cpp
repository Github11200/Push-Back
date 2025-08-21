#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller;

motor FrontRight = motor(PORT18, ratio6_1, false);
motor FrontLeft = motor(PORT12, ratio6_1, true);
motor MiddleRight = motor(PORT7, ratio6_1, true);
motor MiddleLeft = motor(PORT11, ratio6_1, false);
motor BackRight = motor(PORT17, ratio6_1, false);
motor BackLeft = motor(PORT15, ratio6_1, true);

motor_group Left = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor_group Right = motor_group(FrontRight, MiddleRight, BackRight);

void vexcodeInit(void)
{
  // nothing to initialize
}