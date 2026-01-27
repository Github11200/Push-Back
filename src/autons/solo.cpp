#include "autons.h"
#include "vex.h"

void Autons::solo()
{
  DriveParams driveParams;
  TurnParams turnParams;

  chassisReference->odometry->setPosition(-46.5, -16.5, 180);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  willyNilly.on();

  // Drive in front of the loader
  driveParams = driveParams30_in();
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), driveParams, turnParams10_deg(), {});

  // Ram into 1st loader
  turnParams = turnParams90_deg();
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 1200;
  chassisReference->turnTo(Pose<double>(-68, -47, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-68, -47, 0), driveParams, turnParams10_deg(), {});
  wait(1000, msec);

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams30_in();
  chassisReference->turnTo(Pose<double>(-27, -47, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score and chill
  blocker.on();
  wait(250, msec);
  blocker.off();

  // Back away from 1st long goal
  driveParams = driveParams20_in();
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), driveParams, turnParams10_deg(), {});
  finger.on();

  // Eat group of blocks in middle
  turnParams = turnParams45_deg();
  driveParams = driveParams50_in();
  chassisReference->turnTo(Pose<double>(-16, -16, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-16, -16, 0), driveParams, turnParams10_deg(), {});

  // Score in low goal
  turnParams = turnParams10_deg();
  chassisReference->turnTo(Pose<double>(-13, -13, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-13, -13, 0), driveParams, turnParams10_deg(), {});
  intake.spinFullIntake(vex::directionType::rev, 7);
  wait(800, msec);

  // Eat other middle blocks with a curve
  driveParams = driveParams30_in();
  turnParams = turnParams180_deg();
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveToPose(Pose<double>(-23.5, 20, 25), driveParams, turnParams, {}, 0.2);

  // Turn toward loader entrance point with a curve
  driveParams = driveParams30_in();
  turnParams = turnParams45_deg();
  willyNilly.on()
      chassisReference->driveToPose(Pose<double>(-47, 47, 270), driveParams, turnParams, {}, 0.2);

  // Ram into 2nd loader
  turnParams = turnParams10_deg();
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 1200;
  chassisReference->turnTo(Pose<double>(-68, 47, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-68, 47, 0), driveParams, turnParams10_deg(), {});
  wait(1000, msec);

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams30_in();
  chassisReference->turnTo(Pose<double>(-27, 47, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, 47, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score and chill
  blocker.on();
  wait(10000, msec);
}