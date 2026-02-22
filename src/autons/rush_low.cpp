#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::rush_low()
{
  chassisReference->odometry->setPosition(-46.5, -16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd, 12);
  sloper.on();

  willyNilly.delayToggle(1250);

  // Drive to the middle blocks
  chassisReference->turnTo(Pose<double>(-22, 23, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-22, 23, 0), {}, turnParams10_deg(), {});

  // Drive in front of the loader
  chassisReference->turnTo(Pose<double>(-47, -47, -360), {.turnSettleTime = 0}, {});
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), {.driveSettleTime = 0}, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-27, -47.5, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47.5, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  blocker.on();
  wait(900, msec);
  blocker.off();
  intake.stopFullIntake();

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(-40, -61.5, -360), {.turnTimeout = 500}, {});
  chassisReference->driveToPoint(Pose<double>(-40, -61.5, 0), {.driveTimeout = 900}, turnParams10_deg(), {});

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-15, -59, -360), {.turnTimeout = 550}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-15, -59, 0), {.driveMaxVoltage = 8, .driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);

  wait(20000, msec);
}