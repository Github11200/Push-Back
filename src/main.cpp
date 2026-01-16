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

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
Chassis chassis(
    // Inertial scaling
    356.324,

    // Odometry tracker setup
    TrackerSetup::TWO_TRACKER,

    // Inches to degrees ratio, this is for calculating how far the drive has moved based on the encoders
    // (((drive_ratio) * PI * wheel_diameter) / 360)

    // FORWARDS
    ((M_PI * 2.72292) / 360.0),

    // SIDEWAYS
    ((M_PI * 1.98839) / 360.0),

    // Forward tracker distance
    0.06621476,

    // Sideways tracker distance
    5.28142,

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
  // autons.prepareAuton();
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
  autons.runAuton(AutonName::SOLO);
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

  // Driver driver;
  // driver.startJoysticksThread();

  // chassis.trapezoidalMotionProfile(10, {}, driveParams10_in(), turnParams10_deg(), {});
  // chassis.driveToPose(Pose<double>(20, 20, 0), {.driveMaxVoltage = 5}, {}, {}, 0.5, 0, 0);
  // cout << chassis.odometry->getPose().position.y << endl;
  // wait(1, sec);
  // chassis.odometry->setPosition(5, 5, 90);

  // driver.startPistonsThread();

  // wait(4, sec);
  // autons.runAuton(AutonName::TUNING);
  // chassis.odometry->setPosition(0, 0, 0);
  // chassis.odometry->startPositionTrackThread(false);

  autons.prepareAuton();
  autons.runAuton(AutonName::TUNING);

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
    // driver.buttonsLoopCallback();
    // cout << chassis.odometry->getPose().position.x << ", " << chassis.odometry->getPose().position.y << endl;

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

// Forward: 0.0634636
// Sideways: 4.97877

// Forward: 0.00324508
// Sideways: 4.95606

// Forward: -0.00615135
// Sideways: 4.9561