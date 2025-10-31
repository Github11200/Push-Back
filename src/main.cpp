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
Driver driver;

Chassis chassis(
    // Inertial port
    PORT7,

    // Odometry tracker setup
    TrackerSetup::ZERO_TRACKER,

    // Forward tracker port
    PORT21,

    // Sideways tracker port
    PORT22,

    // Inches to degrees ratio, this is for calculating how far the drive has moved based on the encoders
    // (((drive_ratio) * PI * wheel_diameter) / 360)
    (((48 / 84) * M_PI * 4.125) / 360.0),

    // Forward tracker distance
    5.8,

    // Sideways tracker distance
    1.625,

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

Autons autons(&chassis);

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
  // autons.runAuton(AutonName::TESTING, vex::color::red);
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
  driver.startJoysticksThread();
  driver.startPistonsThread();

  // wait(4, sec);  
  // cout << "done waiting" << endl; 

  // chassis.odometry->wallReset(DistanceSensor::FORWARD, Wall::FRONT);
  // cout << "Front distance: " << frontDistance.objectDistance(vex::distanceUnits::in) << endl;
  // cout << "Right distance: " << rightDistance.objectDistance(inches) << endl;  
  // chassis.odometry->wallReset(DistanceSensor::FORWARD, Wall::REAR); 
  // chassis.odometry->wallReset(DistanceSensor::STARBOARD, Wall::RIGHT); 
         
  // cout << "start moving" << endl;
  // chassis.driveToPose(Pose<double>(10, 20, 90), {
  //   .driveKp = 0.2 
  // }, { 
  //   .turnKp = 0.1,
  //   .turnKi = 0
  // }, {}, 0.2, 0, 0.5);
  // chassis.turnTo(Pose<double>(0, 0, -45), {}, {}); 
  // cout << "Y: " << chassis.odometry->getPose().position.y << endl;    
  // chassis.turnTo(Pose<double>(0, 0, 84), {}, {});   // Turns to angle (doesn't matter what you put in the x and y coordinates)
  // chassis.turnTo(Pose<double>(5, 5, -360), {}, {}); // Turns to point (you need the -360 for this)

  // autons.high();
  
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
