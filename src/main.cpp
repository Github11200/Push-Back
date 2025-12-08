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
#include "../include/driver.h"

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
Chassis chassis(
    // Inertial port
    PORT7,

    // Inertial scaling
    357.5, // 357.5

    // Odometry tracker setup
    TrackerSetup::TWO_TRACKER,

    // Forward tracker port
    PORT4,

    // Sideways tracker port
    PORT8,

    // Inches to degrees ratio, this is for calculating how far the drive has moved based on the encoders FORWARD
    // (((drive_ratio) * PI * wheel_diameter) / 360)
    ((M_PI * 2.125) / 360.0),

    // SIDEWAYS
    ((M_PI * 1.980) / 360.0),

    // Forward tracker distance
    0,

    // Sideways tracker distance
    5.85725,

    // Front distance sensor distance
    (8.3175 - 5.4),

    // Left distance sensor distance
    (6.8845 - 0.3), // 0.4 from side

    // Right distance sensor distance
    (6.8845 - 0.2),

    // Back distance sensor distance
    (8.3175 - 3.4),

    // Enable logs (false by default)
    true);

Autons autons(std::make_unique<Chassis>(chassis));

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
  // chassis.odometry->startPositionTrackThread(false);
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
  autons.runAuton(AutonName::HIGH);
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

  // wait(4, sec);
  // chassis.odometry->startPositionTrackThread(true);
  // chassis.driveToPoint(Pose<double>(0, 45, 0), {.driveTimeout = 1000000}, {}, {});
  // wait(5, sec);
  // chassis.turnTo(Pose<double>(5, 5, -360), {}, {});
  // autons.runAuton(AutonName::SKILLS);

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

  // autons.~Autons();
  chassis.~Chassis();
  // willyNilly.~Pneumatic();
  // finger.~Pneumatic();
  // sloper.~Pneumatic();
  // blocker.~Pneumatic();
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
