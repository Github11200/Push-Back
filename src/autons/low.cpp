#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::low()
{
  chassisReference->odometry->setPosition(-46.5, -15, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  IntakeRear.stop();
  IntakeMiddle.stop();
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  sloper.on();

  // Drive to the middle blocks
  finger.on();
  chassisReference->turnTo(Pose<double>(-19, -22, -360), {.turnTimeout = 50}, {});
  willyNilly.delayToggle(900);
  chassisReference->driveToPoint(Pose<double>(-19, -22, 0), {.driveMaxVoltage = 7, .driveTimeout = 950}, turnParams10_deg(), {});
  finger.off();
  wait(200, msec);

  // Drive towards and score in low goal
  willyNilly.off();
  chassisReference->turnTo(Pose<double>(-9, -9.8, -360), {.turnTimeout = 650}, {});
  chassisReference->driveToPoint(Pose<double>(-9, -9.8, 0), {.driveTimeout = 900}, turnParams10_deg(), {});
  razer.on();
  intake.spinFullIntake(vex::directionType::rev, 12);
  IntakeFront.spin(vex::directionType::rev, 7, volt);
  wait(510, msec);
  razer.off();
  intake.spinFullIntake(vex::directionType::fwd, 12);

  // Drive (in reverse) in front of the loader
  chassisReference->turnTo(Pose<double>(-47, -48.5, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-47, -48.5, 0), {.driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});
  willyNilly.on();

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, -48.5, -360), {.turnTimeout = 700}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 100, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 510, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-24, -48.5, -360), {.turnTimeout = 1100}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, -48.5, 0), {.driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  blocker.on();
  wait(700, msec);
  intake.stopFullIntake();

  // // Back away from goal
  // chassisReference->driveToPoint(Pose<double>(-37, -47, 0), {.driveTimeout = 600}, turnParams10_deg(), {});

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(-35, -60, -360), {.turnTimeout = 300}, {});
  chassisReference->driveToPoint(Pose<double>(-35, -60, 0), {.driveTimeout = 500}, turnParams10_deg(), {});
  blocker.off();

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-8, -60, -360), {.turnTimeout = 300}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-8, -60, 0), {.driveTimeout = 1300}, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);

  wait(2000, msec);
}