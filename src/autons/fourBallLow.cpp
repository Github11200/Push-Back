#include "autons.h"
#include "vex.h"
#include "types/params.h"

void Autons::fourBallLow()
{
  chassisReference->odometry->setPosition(-46.5, -14, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();

  // Drive to the middle blocks
  finger.on();
  willyNilly.delayToggle(700);
  chassisReference->driveToPoint(Pose<double>(-19, -22, 100), {.driveTimeout = 800}, turnParams10_deg(), {});
  finger.off();
  wait(200, msec);

  // Turn towards the long goal
  chassisReference->turnTo(Pose<double>(-26, -37, -360), {.turnTimeout = 800, .turnSettleError = 15, .turnSettleTime = 0}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-26, -37, 0), {.driveSettleTime = 0, .driveSettleError = 5, .driveMinVoltage = 8}, turnParams10_deg(), {.forwards = false});

  // Turn to perfectly align with it
  chassisReference->turnTo(Pose<double>(0, 0, 270), {.turnTimeout = 1500, .turnMinVoltage = 12, .turnSettleError = 5, .turnSettleTime = 0}, {}, SwingDirection::SWING_RIGHT);

  blocker.on();
  wait(800, msec);
  intake.stopFullIntake();

  // Reposition to align wing
  // chassisReference->turnTo(Pose<double>(-35, -58.5, -360), {.turnTimeout = 300}, {});
  chassisReference->driveToPoint(Pose<double>(-35, -58.5, 0), {.driveTimeout = 400, .driveMinVoltage = 8}, turnParams10_deg(), {});
  blocker.off();

  // Push blocks in goal
  // chassisReference->turnTo(Pose<double>(-8, -58.5, -360), {.turnTimeout = 300}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-8, -58, 0), {.driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);

  wait(2000, msec);
}