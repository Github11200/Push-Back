#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller;

motor FrontRight = motor(PORT2, ratio6_1, true);  // DONE
motor FrontLeft = motor(PORT12, ratio6_1, false); // DONE

motor MiddleRight = motor(PORT8, ratio6_1, false); // DONE
motor MiddleLeft = motor(PORT13, ratio6_1, true);  // DONE

motor BackRight = motor(PORT10, ratio6_1, false); // DONE
motor BackLeft = motor(PORT15, ratio6_1, true);   // DONE

motor IntakeFront = motor(PORT18, ratio6_1, false); // DONE
motor IntakeMiddle = motor(PORT3, ratio6_1, false); // DONE

motor IntakeRear = motor(PORT16, ratio6_1, true); // DONE

vex::distance frontDistance = vex::distance(PORT1);
vex::distance rightDistance = vex::distance(PORT9);
vex::distance leftDistance = vex::distance(PORT11);

vex::rotation ForwardTracker = vex::rotation(PORT1, true);    // DONE
vex::rotation SidewaysTracker = vex::rotation(PORT14, false); // DONE

vex::inertial Inertial = vex::inertial(PORT9); // DONE

vex::optical IntakeOptical = vex::optical(PORT2);

motor_group Left = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor_group Right = motor_group(FrontRight, MiddleRight, BackRight);

vex::controller::button IntakeButton = Controller.ButtonL1;
vex::controller::button OuttakeButton = Controller.ButtonDown;
vex::controller::button WillyNillyButton = Controller.ButtonB;
vex::controller::button FingerButton = Controller.ButtonR1;
vex::controller::button HighGoalScoreButton = Controller.ButtonR2;
vex::controller::button MiddleGoalScoreButton = Controller.ButtonL2;
vex::controller::button HoodToggleButton = Controller.ButtonY;

bool stopPlease = false;

void vexcodeInit(void)
{
  // nothing to initialize
}