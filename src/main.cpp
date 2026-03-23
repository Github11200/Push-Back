/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       patel                                                     */
/*    Created:      5/24/2025, 10:01:32 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "chassis.h"
#include "pursuit.h"
#include "testing/tests.h"
#include "utils/logger.h"
#include "autons.h"
#include "driver.h"
#include "types/params.h"
#include "config.h"

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
Chassis chassis;
Autons autons(std::make_unique<Chassis>());

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
  // Testing::runAllTests();
  autons.prepareAuton();
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
  if (!ForwardTracker.installed())
  {
    cout << "Forward tracker not installed!" << endl;
    return;
  }
  autons.runAuton(AutonName::LOW);
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
  CurvedMotionProfile motionProfile;
  Vector2D<double> points[4] = {
      Vector2D<double>(13, 36), Vector2D<double>(13, 60),
      Vector2D<double>(36, 36), Vector2D<double>(36, 60)};
  motionProfile.curve = CubicBezier(points);
  motionProfile.distanceBetweenPoints = 0.5;
  motionProfile.initialVelocity = 0;
  motionProfile.finalVelocity = 0;
  motionProfile.kA = 10;
  motionProfile.maximumAcceleration = 2;
  motionProfile.maximumVelocity = 100;

  RamseteParams params;
  params.beta = 0.1;
  params.zeta = 0.1;

  chassis.curvedMotionProfile(motionProfile, params, 0.5);

  // if (chassis.odometry->isTracking)
  //   chassis.odometry->stopPositionTrackThread();
  Driver driver;
  driver.startJoysticksThread();
  driver.startPistonsThread();

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
    driver.buttonsLoopCallback();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }

  chassis.~Chassis();
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

// 0.07782561
// -3.66028

// 0.129966
// 3.67144

// 0.0709169
// 3.67061