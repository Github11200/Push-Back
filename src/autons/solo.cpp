#include "autons.h"
#include "vex.h"

//  -986.31

void Autons::solo()
{
  DriveParams driveParams;
  TurnParams turnParams;

  // Set starting coordinates
  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd);

  willyNilly.delayToggle(400);

  // Drive to the middle blocks
  driveParams = driveParams50_in();
  driveParams.driveSettleError = 3;
  chassisReference->driveToPose(Pose<double>(-19, 31, 45), driveParams, turnParams30_deg(), {}, 0.4);

  // Not getting the blocks under long goal because, quoting jinay, "our little will... it's too thick"
  // willyNilly.off();
  // willyNilly.delayToggle(1000);

  // // Intake the blocks under the long goal
  // driveParams = driveParams20_in();
  // turnParams = turnParams10_deg();
  // chassisReference->driveToPoint(Pose<double>(-8.5, 41, 0), driveParams, turnParams10_deg(), {});

  // Curve back to in front of loader
  driveParams = driveParams50_in();
  // driveParams.driveSettleError = 3;
  // driveParams.driveMinVoltage = 1;
  turnParams = turnParams90_deg();

  chassisReference->driveToPoint(Pose<double>(-40, 42, 0), driveParams, turnParams, {.forwards = false});

  return;

  // Ram into 1st loader
  turnParams = turnParams135_deg();
  turnParams.turnTimeout = 500;
  driveParams = driveParams20_in();
  driveParams.driveTimeout = 1300;
  chassisReference->turnTo(Pose<double>(-75, 43, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-75, 43, 0), driveParams, turnParams10_deg(), {});
  // wait(1000, msec);

  // Score in 1st long goal
  driveParams = driveParams30_in();
  driveParams.driveTimeout = 1000;
  chassisReference->driveToPoint(Pose<double>(-27, 43, 0), driveParams, turnParams10_deg(), {.forwards = false});
  // intake.scoreLongGoal(); Not using this since we only need to score 2 blocks
  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  blocker.on();
  wait(500, msec);
  sloper.off();
  blocker.off();

  return;

  // Back away from long goal
  driveParams = driveParams20_in();
  driveParams.driveTimeout = 700;
  chassisReference->driveToPoint(Pose<double>(-47, 43, 0), driveParams, turnParams10_deg(), {});

  // Drive to middle goal
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 1800;
  turnParams = turnParams45_deg();
  turnParams.turnTimeout = 700;
  chassisReference->turnTo(Pose<double>(-14, 13, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-14, 13, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score in middle goal
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(400, msec);
  blocker.off();
  willyNilly.off();
  driveParams = driveParams10_in();
  driveParams.driveTimeout = 200;
  driveParams.driveMinVoltage = 12;
  chassisReference->driveDistance(15, chassisReference->getAbsoluteHeading().angle, driveParams, turnParams10_deg(), {});

  // Curve to other group of middle blocks
  driveParams = driveParams50_in();
  driveParams.driveMaxVoltage = 12;
  driveParams.driveMinVoltage = 12;
  driveParams.driveSettleError = 2;

  turnParams = turnParams90_deg();

  willyNilly.delayToggle(1300);
  chassisReference->driveToPoint(Pose<double>(-16.647, -20.733, 0), driveParams, turnParams, {});
  willyNilly.off();

  // Curve to in front of loader
  driveParams = driveParams30_in();
  driveParams.driveMinVoltage = 3;
  driveParams.driveSettleError = 5;
  driveParams.driveSlew = 12;
  // driveParams.driveTimeout = 1300;

  turnParams = turnParams90_deg();
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), driveParams, turnParams, {});

  // Ram into 2nd loader
  turnParams = turnParams10_deg();
  turnParams.turnTimeout = 300;
  driveParams = driveParams20_in();
  driveParams.driveTimeout = 1200;
  chassisReference->turnTo(Pose<double>(-68, -47, -360), turnParams, {});
  willyNilly.on();
  chassisReference->driveToPoint(Pose<double>(-68, -47, 0), driveParams, turnParams10_deg(), {});

  // Score in 2nd long goal
  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 12;

  chassisReference->driveToPoint(Pose<double>(-27, -47.5, 0), driveParams, turnParams10_deg(), {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  blocker.on();
  wait(5000, msec);
}