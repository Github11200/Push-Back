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

vex::distance frontDistance = vex::distance(PORT2);
vex::distance rightDistance = vex::distance(PORT3);
vex::distance leftDistance = vex::distance(PORT4);

motor_group Left = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor_group Right = motor_group(FrontRight, MiddleRight, BackRight);

digital_out willyNilly = digital_out(Brain.ThreeWirePort.A);
digital_out winger = digital_out(Brain.ThreeWirePort.B);
digital_out sloper = digital_out(Brain.ThreeWirePort.C);
digital_out blocker = digital_out(Brain.ThreeWirePort.D);

bool stopPlease = false;

void vexcodeInit(void)
{
  // nothing to initialize
}