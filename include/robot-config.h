#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "subsystems/pneumatic.h"

using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller;

extern motor FrontRight;
extern motor FrontLeft;
extern motor MiddleRight;
extern motor MiddleLeft;
extern motor BackRight;
extern motor BackLeft;

extern motor IntakeLeft;
extern motor IntakeRight;

extern vex::distance frontDistance;
extern vex::distance rightDistance;
extern vex::distance leftDistance;

extern vex::rotation ForwardTracker;
extern vex::rotation SidewaysTracker;

extern vex::inertial Inertial;

extern vex::motor_group Left;
extern vex::motor_group Right;

extern vex::controller::button IntakeButton;
extern vex::controller::button OuttakeButton;
extern vex::controller::button OuttakeWithHoodUpButton;
extern vex::controller::button WillyNillyButton;
extern vex::controller::button FingerButton;
extern vex::controller::button BlockerButton;
extern vex::controller::button HighGoalScoreButton;
extern vex::controller::button MiddleGoalScoreButton;
extern vex::controller::button MiddleGoalSlowScoreButton;

extern bool stopPlease;

void vexcodeInit(void);

#endif