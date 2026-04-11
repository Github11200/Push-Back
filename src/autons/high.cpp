#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::high()
{
  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();

  willyNilly.delayToggle(1050);

  // Drive to the middle blocks
  chassisReference->turnTo(Pose<double>(-22, 23, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-22, 23, 0), {.driveMaxVoltage = 8}, {}, {});

  // // Intake the blocks under the long goal
  // willyNilly.off();
  // willyNilly.delayToggle(1000);
  // chassisReference->turnTo(Pose<double>(-8.5, 41, 0), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-8.5, 41, 0), {}, turnParams10_deg(), {});

  // // Drive back
  // chassisReference->turnTo(Pose<double>(-23, 23, -360), {}, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-23, 23, 0), {}, turnParams10_deg(), {.forwards = false});

  // Turn to face the center goal location (turn to point (14, -14))
  chassisReference->turnTo(Pose<double>(-10, 11.25, -360), {.turnTimeout = 1000}, {.forwards = false});
  sloper.off();
  intake.stopFullIntake();
  chassisReference->driveToPoint(Pose<double>(-10, 11.25, 0), {}, {}, {.forwards = false});

  // Score middle goal
  blocker.on();
  IntakeRear.spin(vex::directionType::fwd, 6, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(250, msec);
  intake.stopFullIntake();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 48, 0), {.driveTimeout = 2000}, turnParams10_deg(), {});
  sloper.on();
  blocker.off();

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, 48, -360), {.turnTimeout = 700}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  IntakeRear.stop(vex::brakeType::coast);
  // chassisReference->driveToPoint(Pose<double>(-80, -48, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 200, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 500, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-20, 48.5, -360), {.turnTimeout = 200}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-20, 48.5, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(900, msec);
  intake.stopFullIntake();

  // // Back away from goal
  // chassisReference->driveToPoint(Pose<double>(-37, 47, 0), {.driveTimeout = 600}, turnParams10_deg(), {});

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(-35, 38.25, -360), {.turnTimeout = 300}, {});
  chassisReference->driveToPoint(Pose<double>(-35, 38.25, 0), {.driveTimeout = 500}, turnParams10_deg(), {});
  blocker.off();

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-8, 38.25, -360), {.turnTimeout = 300}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-8, 38.25, 0), {.driveTimeout = 1300}, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);

  wait(2000, msec);
}