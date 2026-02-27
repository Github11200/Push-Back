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

  willyNilly.delayToggle(1350);

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
  chassisReference->turnTo(Pose<double>(-13.5, 13.25, -360), {.turnTimeout = 1000}, {.forwards = false});
  intake.stopFullIntake();
  chassisReference->driveToPoint(Pose<double>(-13.5, 13.25, 0), {}, {}, {.forwards = false});

  // Score middle goal
  sloper.off();
  IntakeRear.spin(vex::directionType::fwd, 7, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(400, msec);
  sloper.on();
  intake.stopFullIntake();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 47, 0), {.driveTimeout = 2000}, turnParams10_deg(), {});

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, 47, -360), {.turnTimeout = 700}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 200, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 500, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-27, 47, -360), {.turnTimeout = 200}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, 47, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  blocker.on();
  wait(900, msec);
  blocker.off();
  intake.stopFullIntake();

  // // Back away from goal
  // chassisReference->driveToPoint(Pose<double>(-37, 47, 0), {.driveTimeout = 600}, turnParams10_deg(), {});

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(-40, 35.2, -360), {.turnTimeout = 500}, {});
  chassisReference->driveToPoint(Pose<double>(-40, 35.2, 0), {.driveTimeout = 900}, turnParams10_deg(), {});

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-15, 37, -360), {.turnTimeout = 550}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-15, 37, 0), {.driveMaxVoltage = 8, .driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);

  wait(2000, msec);
}