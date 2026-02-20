#include "autons.h"
#include "vex.h"
#include "types/params.h"

void Autons::solo()
{
  chassisReference->odometry->setPosition(-46.5, -16.5, 180);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  willyNilly.on();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), {.driveTimeout = 700}, turnParams10_deg(), {});

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, -47, -360), {.turnTimeout = 700}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 300, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 550, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-27, -47, -360), {.turnTimeout = 200}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score
  blocker.on();
  wait(700, msec);
  blocker.off();

  // Back away from 1st long goal
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), {.driveTimeout = 1100}, {}, {});

  chassisReference->turnTo(Pose<double>(-10, -10, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-18.5, -18.5, 0), {.driveSettleError = 5, .driveMinVoltage = 3}, {}, {});
  wait(300, msec);

  // Score in low goal
  // chassisReference->turnTo(Pose<double>(-10, -10, -360), turnParams10_deg(), {});
  chassisReference->driveToPoint(Pose<double>(-10, -10, 0), {}, turnParams10_deg(), {});
  razer.on();
  intake.spinFullIntake(vex::directionType::rev, 8);
  wait(800, msec);
  razer.off();

  // Back up from low goal
  chassisReference->turnTo(Pose<double>(-23, -23, -360), {.turnTimeout = 100}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-23, -23, 0), {.driveTimeout = 400}, {}, {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd, 12);

  // Eat other middle blocks
  chassisReference->turnTo(Pose<double>(-22, 30, -360), {.turnTimeout = 300}, {});
  willyNilly.delayToggle(1300);
  finger.on();
  chassisReference->driveToPoint(Pose<double>(-22, 30, 0), {.driveMinVoltage = 5, .driveSettleError = 25}, {}, {});

  // Go towards loader entrance point
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(-47, 47, -360), {.turnTimeout = 600}, {});
  chassisReference->driveToPoint(Pose<double>(-47, 47, 0), {.driveTimeout = 800, .driveSlew = 12}, {}, {});

  // Ram into 2nd loader
  chassisReference->turnTo(Pose<double>(-68, 47, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, 48, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 300, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 550, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-27, 47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, 47, 0), {.driveTimeout = 1050}, {}, {.forwards = false});
  willyNilly.off();

  // Score and chill
  blocker.on();
  wait(10000, msec);
}