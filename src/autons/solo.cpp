#include "autons.h"
#include "vex.h"
#include "types/params.h"

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
  driveParams.driveSettleError = 1;
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), driveParams, turnParams10_deg(), {});

  // Ram into 1st loader
  turnParams = turnParams90_deg();
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 780;
  chassisReference->turnTo(Pose<double>(-68, -47, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams30_in();
  chassisReference->turnTo(Pose<double>(-27, -47, -360), turnParams, {.forwards = false});
  driveParams.driveTimeout = 1100;
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score
  blocker.on();
  wait(700, msec);
  blocker.off();

  // Back away from 1st long goal
  driveParams = driveParams20_in();
  driveParams.driveTimeout = 800;
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), driveParams, turnParams10_deg(), {});
  finger.on();

  // Eat group of blocks in middle
  turnParams = turnParams45_deg();
  driveParams = driveParams50_in();
  driveParams.driveMaxVoltage = 8;
  chassisReference->turnTo(Pose<double>(-13, -13, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-13, -13, 0), driveParams, turnParams10_deg(), {});
  wait(200, msec);

  // Score in low goal
  turnParams = turnParams10_deg();
  driveParams = driveParams5_in();
  chassisReference->turnTo(Pose<double>(-10.8, -10.8, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-10.8, -10.8, 0), driveParams, turnParams10_deg(), {});
  intake.spinFullIntake(vex::directionType::rev, 7);
  wait(800, msec);

  // Back up from low goal
  driveParams = driveParams10_in();
  turnParams = turnParams180_deg();
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->turnTo(Pose<double>(-23, -23, -360), turnParams, {.forwards = false});
  chassisReference->driveToPose(Pose<double>(-23, -23, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Eat other middle blocks
  turnParams = turnParams45_deg();
  driveParams = driveParams50_in();
  chassisReference->turnTo(Pose<double>(-22, 30, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-22, 30, 0), driveParams, turnParams10_deg(), {});

  // Go towards loader entrance point
  turnParams = turnParams45_deg();
  driveParams = driveParams30_in();
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(-47, 48, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-47, 48, 0), driveParams, turnParams10_deg(), {});

  // Ram into 2nd loader
  turnParams = turnParams10_deg();
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 780;
  chassisReference->turnTo(Pose<double>(-68, 48, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-80, 48, 0), driveParams, turnParams10_deg(), {});

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams30_in();
  chassisReference->turnTo(Pose<double>(-27, 48, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, 48, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score and chill
  blocker.on();
  wait(10000, msec);
}