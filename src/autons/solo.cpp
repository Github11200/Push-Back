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
  // chassisReference->driveToPoint(Pose<double>(-47, -47, 0), {.driveTimeout = 800}, turnParams10_deg(), {});
  // finger.on();

  // Eat group of blocks in middle
  chassisReference->turnTo(Pose<double>(-19, -18.5, -360), {.turnTimeout = 0}, {}, SwingDirection::SWING_RIGHT);
  chassisReference->driveToPoint(Pose<double>(-19, -18.5, 0), {.driveTimeout = 900}, turnParams10_deg(), {});
  wait(200, msec);

  // Score in low goal
  chassisReference->turnTo(Pose<double>(-12, -10.5, -360), turnParams10_deg(), {});
  intake.spinFullIntake(vex::directionType::rev, 6);
  chassisReference->driveToPoint(Pose<double>(-12, -10.5, 0), {}, turnParams10_deg(), {});
  intake.spinFullIntake(vex::directionType::rev, 8);
  wait(400, msec);

  // Back up from low goal
  chassisReference->turnTo(Pose<double>(-23, -23, -360), {.turnTimeout = 100}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-23, -23, 0), {.driveTimeout = 400}, turnParams10_deg(), {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd, 12);

  // Eat other middle blocks
  chassisReference->turnTo(Pose<double>(-22, 30, -360), {.turnTimeout = 300}, {});
  willyNilly.delayToggle(1300);
  finger.on();
  chassisReference->driveToPoint(Pose<double>(-22, 30, 0), {.driveMinVoltage = 5, .driveSettleError = 25}, turnParams10_deg(), {});

  // Go towards loader entrance point
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(-47, 48, -360), {.turnTimeout = 600}, {});
  chassisReference->driveToPoint(Pose<double>(-47, 48, 0), {.driveTimeout = 800, .driveSlew = 12}, turnParams10_deg(), {});

  // Ram into 2nd loader
  chassisReference->turnTo(Pose<double>(-68, 48, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, 48, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 300, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 550, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-27, 47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, 47, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score and chill
  blocker.on();
  wait(10000, msec);
}