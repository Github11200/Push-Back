#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::rush_high()
{
  chassisReference->odometry->setPosition(-46.5, 15, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd, 12);
  sloper.on();

  willyNilly.delayToggle(500);

  // Drive to the middle blocks
  // chassisReference->turnTo(Pose<double>(-23, 23, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-24, 24, 0), {.driveTimeout = 900, .driveSettleTime = 0}, {}, {});

  // Drive in front of the loader
  chassisReference->turnTo(Pose<double>(-47, 43.5, -360), {.turnSettleTime = 0, .turnSettleError = 5}, {});
  willyNilly.on();
  chassisReference->driveToPoint(Pose<double>(-47, 43.5, 0), {.driveSettleTime = 0, .driveSettleError = 6}, {.turnSettleTime = 0}, {});
  sloper.on();
  blocker.off();

  // Ram into 1st loader
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->turnTo(Pose<double>(-68, 46.5, -360), {.turnTimeout = 700, .turnSettleTime = 0, .turnSettleError = 5}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 100, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5.5, 700, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  // chassisReference->turnTo(Pose<double>(-20, 50, -360), {.turnTimeout = 300}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-20, 47, 0), {.driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  // Score and NOT CHILL >:(
  blocker.on();
  wait(950, msec);

  // Pull this thingy up
  willyNilly.off();

  // chassisReference->turnTo(Pose<double>(-34, 46, -360), {.turnTimeout = 500}, {});
  // chassisReference->driveToPoint(Pose<double>(-34, 46, 0), {.driveTimeout = 300}, turnParams10_deg(), {});
  // blocker.off();
  // // chassisReference->turnTo(Pose<double>(0, -48.5, -360), {.turnTimeout = 500}, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(0, 46, 0), {.driveTimeout = 600}, turnParams10_deg(), {.forwards = false});
  // sloper.on();
  // chassisReference->driveToPoint(Pose<double>(0, 46, 0), {.driveTimeout = 100000}, turnParams10_deg(), {.forwards = false});

  chassisReference->driveDistance(5, chassisReference->getAbsoluteHeading().angle, {.driveTimeout = 800}, {}, {});
  blocker.off();
  chassisReference->driveWithVoltage(-10, 900, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  Left.stop(brakeType::hold);
  Right.stop(brakeType::hold);
}