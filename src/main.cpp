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
  autons.runAuton(AutonName::SKILLS);
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
  // if (chassis.odometry->isTracking)
  //   chassis.odometry->stopPositionTrackThread();
  Driver driver;
  driver.startJoysticksThread();
  driver.startPistonsThread();

  // CurvedMotionProfile motionProfile;
  // Vector2D<double> points[4] = {Vector2D<double>(0, 0), Vector2D<double>(0, 5), Vector2D<double>(10, 5), Vector2D<double>(10, 10)};
  // motionProfile.curve = CubicBezier(points);
  // motionProfile.distanceBetweenPoints = 0.1;
  // motionProfile.finalVelocity = 0;
  // motionProfile.kA = 10;
  // motionProfile.maximumAcceleration = 100;
  // motionProfile.maximumVelocity = 100;

  // RamseteParams params;
  // params.beta = 0.1;
  // params.zeta = 0.1;
  // chassis.curvedMotionProfile(motionProfile, params, 100);

  // cout << Config::kForwardTrackerDistance << endl;
  // autons.prepareAuton();
  // chassis.odometry->setPosition(0, 0, 0);
  // chassis.odometry->startPositionTrackThread(false);
  // wait(3, sec);
  // autons.runAuton(AutonName::TUNING);
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
  // Set up callbacks for autonom`ous and driver control periods.
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