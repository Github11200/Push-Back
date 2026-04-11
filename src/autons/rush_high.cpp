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

  // Drive to the middle blocks
  finger.on();
  chassisReference->turnTo(Pose<double>(-19, 22, -360), {.turnTimeout = 50}, {});
  willyNilly.delayToggle(780);
  chassisReference->driveToPoint(Pose<double>(-19, 22, 0), {.driveMaxVoltage = 6, .driveTimeout = 950}, turnParams10_deg(), {});
  finger.off();
  wait(200, msec);

  // Drive (in reverse) in front of the loader
  chassisReference->turnTo(Pose<double>(-47, 47, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-47, 47, 0), {}, turnParams10_deg(), {});
  willyNilly.on();

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, 47, -360), {.turnTimeout = 700}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 100, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 520, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-24, 47, -360), {.turnTimeout = 1100}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, 47, 0), {.driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  blocker.on();
  wait(920, msec);

  chassisReference->turnTo(Pose<double>(-34, 47, -360), {.turnTimeout = 500}, {});
  chassisReference->driveToPoint(Pose<double>(-34, 47, 0), {.driveTimeout = 300}, turnParams10_deg(), {});
  blocker.off();
  // chassisReference->turnTo(Pose<double>(0, 48.5, -360), {.turnTimeout = 500}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(0, 47, 0), {.driveTimeout = 600}, turnParams10_deg(), {.forwards = false});
  sloper.on();
  chassisReference->driveToPoint(Pose<double>(0, 47, 0), {.driveTimeout = 100000}, turnParams10_deg(), {.forwards = false});
}