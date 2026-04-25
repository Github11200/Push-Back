#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::rush_low()
{
  chassisReference->odometry->setPosition(-46.5, -15, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd, 12);
  sloper.on();

  // Drive to the middle blocks
  finger.on();
  // chassisReference->turnTo(Pose<double>(-24, -22, -360), {.turnTimeout = 50}, {});
  willyNilly.delayToggle(750);
  chassisReference->driveToPoint(Pose<double>(-20, -22, 0), {.driveTimeout = 900, .driveSettleError = 5, .driveSettleTime = 0, .driveMinVoltage = 3}, turnParams10_deg(), {});
  finger.off();
  wait(200, msec);

  // Drive in front of the loader
  chassisReference->turnTo(Pose<double>(-47, -43, -360), {.turnSettleTime = 0, .turnSettleError = 10}, {});
  willyNilly.on();
  chassisReference->driveToPoint(Pose<double>(-47, -43, 0), {.driveSettleTime = 0, .driveSettleError = 6, .driveMinVoltage = 3}, {.turnSettleTime = 0}, {});
  sloper.on();
  blocker.off();

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, -47, -360), {.turnTimeout = 300}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 150, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 610, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  // chassisReference->turnTo(Pose<double>(-24, -47.5, -360), {.turnTimeout = 1100}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, -48, 0), {.driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  // Score and NOT CHILL >:(
  blocker.on();
  wait(1000, msec);
  blocker.off();

  // chassisReference->driveDistance(5, chassisReference->getAbsoluteHeading().angle, {.driveTimeout = 800}, {}, {});
  // blocker.off();
  // chassisReference->driveWithVoltage(-10, 900, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Left.stop(brakeType::hold);
  // Right.stop(brakeType::hold);

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(-37, -60.25, -360), {.turnTimeout = 300}, {});
  chassisReference->driveToPoint(Pose<double>(-37, -60.25, 0), {.driveTimeout = 600}, turnParams10_deg(), {});
  blocker.off();

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-6, -59, -360), {.turnTimeout = 300}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-6, -59, 0), {.driveTimeout = 1300, .driveMaxVoltage = 8}, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);
}