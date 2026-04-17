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

  willyNilly.delayToggle(650);

  // Drive to the middle blocks
  // chassisReference->turnTo(Pose<double>(-23, 23, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-23, 23, 0), {.driveTimeout = 900, .driveSettleTime = 0}, {}, {});

  // Turn to face the center goal location (turn to point (14, -14))
  chassisReference->turnTo(Pose<double>(-10, 10, -360), {.turnTimeout = 650, .turnSettleTime = 100, .turnSettleError = 3}, {.forwards = false});
  sloper.off();
  intake.stopFullIntake();
  chassisReference->driveToPoint(Pose<double>(-10, 10, 0), {.driveTimeout = 900, .driveSettleTime = 0, .driveSettleError = 3}, {}, {.forwards = false});

  // Score middle goal
  blocker.on();
  IntakeRear.spin(vex::directionType::fwd, 6, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(300, msec);
  intake.stopFullIntake();

  // Drive in front of the loader
  chassisReference->turnTo(Pose<double>(-47, 44.5, -360), {.turnSettleTime = 0, .turnSettleError = 5}, {});
  chassisReference->driveToPoint(Pose<double>(-47, 44.5, 0), {.driveSettleTime = 0, .driveSettleError = 6}, {.turnSettleTime = 0}, {});
  willyNilly.on();
  sloper.on();
  blocker.off();

  // Ram into 1st loader
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->turnTo(Pose<double>(-68, 47.5, -360), {.turnTimeout = 700, .turnSettleTime = 0, .turnSettleError = 5}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 100, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 700, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  // chassisReference->turnTo(Pose<double>(-20, 50, -360), {.turnTimeout = 300}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-20, 48, 0), {.driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  // Score and NOT CHILL >:(
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(900, msec);
  intake.stopFullIntake();

  // // Back away from goal
  // chassisReference->driveToPoint(Pose<double>(-37, 47, 0), {.driveTimeout = 600}, turnParams10_deg(), {});

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(-35, 39.5, -360), {.turnTimeout = 300}, {});
  chassisReference->driveToPoint(Pose<double>(-35, 39.5, 0), {.driveTimeout = 400, .driveMinVoltage = 8}, turnParams10_deg(), {});
  blocker.off();

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-8, 39.5, -360), {.turnTimeout = 300}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-8, 39.5, 0), {.driveTimeout = 1300}, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);

  wait(2000, msec);
}