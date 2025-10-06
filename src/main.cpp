/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       patel                                                     */
/*    Created:      5/24/2025, 10:01:32 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// TODO: Make sure all the cos, sin and tan functions take parameters in as radians
// TODO: Make sure the Angle struct is always returning in degrees
// TODO: Check that before constraining angles they have been converted to degrees
// TODO: Make sure that when any angles are returned from vector.h or something that they have been constrained from 0 to 360

#include "../include/chassis.h"
#include "../include/pursuit.h"
#include "../include/testing/tests.h"
#include "../include/utils/logger.h"
#include "../include/autons.h"

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
Autons autons;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void)
{
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  autons.prepareAuton(AutonName::TESTING, vex::color::red);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void)
{
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  autons.runAuton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void)
{
  // KILL SWITCH for "safety"
  Controller.ButtonA.pressed([]()
                             { stopPlease = true; });

  // Testing::runAllTests();
  // Chassis *chassis = new Chassis(PORT19, PORT14, PORT13, Left, Right, ((M_PI * 1.98298) / 360.0), -0.640625, 1.625, true);
  // chassis->odometry->startPositionTrackThread(true);

  // chassis->trapezoidalMotionProfile(20, {
  //                                           .maximumVelocity = 27.5,
  //                                           .finalVelocity = 0,
  //                                           .maximumAcceleration = 5,
  //                                           .kA = 0.5,
  //                                       },
  //                                   {.driveKp = 1, .driveKi = 0, .driveKd = 3, .driveMaxVoltage = 12, .driveTimeout = 1000000}, {.turnKp = 0.1, .turnKi = 0, .turnKd = 0.5, .turnTimeout = 100000}, {});

  // User control code here, inside the loop
  while (1)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }

  // chassis->odometry->stopPositionTrackThread();
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
