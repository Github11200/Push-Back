#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::low()
{
  chassisReference->odometry->setPosition(-46.5, -14, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  IntakeRear.stop();
  IntakeMiddle.stop();
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  sloper.on();

  // Drive to the middle blocks
  finger.on();
  chassisReference->turnTo(Pose<double>(-24, -22, -360), {.turnTimeout = 50}, {});
  willyNilly.delayToggle(600);
  chassisReference->driveToPoint(Pose<double>(-24, -22, 0), {.driveTimeout = 950}, turnParams10_deg(), {});
  finger.off();
  wait(200, msec);

  // Drive towards and score in low goal
  willyNilly.off();
  chassisReference->turnTo(Pose<double>(-9, -9, -360), {.turnTimeout = 650, .turnSettleTime = 100, .turnSettleError = 3}, {});
  chassisReference->driveToPoint(Pose<double>(-9, -9, 0), {.driveTimeout = 900, .driveSettleTime = 0, .driveSettleError = 3}, turnParams10_deg(), {});
  razer.on();
  intake.spinFullIntake(vex::directionType::rev, 12);
  IntakeFront.spin(vex::directionType::rev, 4, volt);
  wait(850, msec);
  razer.off();
  intake.spinFullIntake(vex::directionType::fwd, 12);

  // Drive (in reverse) in front of the loader
  chassisReference->turnTo(Pose<double>(-47, -45, -360), {.turnSettleTime = 0, .turnSettleError = 5}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-47, -45, 0), {.driveSettleTime = 0, .driveSettleError = 6}, {.turnSettleTime = 0}, {.forwards = false});
  willyNilly.on();

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, -46.5, -360), {.turnTimeout = 700}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 100, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 610, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  // chassisReference->turnTo(Pose<double>(-24, -47.5, -360), {.turnTimeout = 1100}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, -47, 0), {.driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  // Score and NOT CHILL >:(
  blocker.on();
  wait(800, msec);
  intake.stopFullIntake();

  // // Back away from goal
  // chassisReference->driveToPoint(Pose<double>(-37, -47, 0), {.driveTimeout = 600}, turnParams10_deg(), {});

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(-35, -58, -360), {.turnTimeout = 300}, {});
  chassisReference->driveToPoint(Pose<double>(-35, -58, 0), {.driveTimeout = 500}, turnParams10_deg(), {});
  blocker.off();

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-8, -58, -360), {.turnTimeout = 300}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-8, -58, 0), {.driveTimeout = 1300, .driveMaxVoltage = 6}, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);

  wait(2000, msec);
}