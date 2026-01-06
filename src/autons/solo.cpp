#include "autons.h"
#include "vex.h"

void Autons::solo()
{
  DriveParams driveParams;
  TurnParams turnParams;

  // Set starting coordinates
  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd);

  willyNilly.delayToggle(650);

  // Drive to the middle blocks
  driveParams = driveParams50_in();
  driveParams.driveMaxVoltage = 12;
  chassisReference->driveToPose(Pose<double>(-19, 31, 45), driveParams, turnParams30_deg(), {}, 0.3);

  // Not getting the blocks under long goal because, quoting jinay, "our little will... it's too thick"
  // willyNilly.off();
  // willyNilly.delayToggle(1000);

  // // Intake the blocks under the long goal
  // driveParams = driveParams20_in();
  // turnParams = turnParams10_deg();
  // chassisReference->driveToPoint(Pose<double>(-8.5, 41, 0), driveParams, turnParams10_deg(), {});

  // Curve back to in front of loader
  driveParams = driveParams50_in();
  driveParams.driveSettleError = 5;
  turnParams = turnParams90_deg();

  chassisReference->driveToPose(Pose<double>(-45, 50, 90), driveParams, turnParams, {.forwards = false}, 0.4);
  intake.stopFullIntake();

  // Ram into 1st loader
  turnParams = turnParams135_deg();
  turnParams.turnTimeout = 800;
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 1200;
  chassisReference->turnTo(Pose<double>(-68, 49, -360), turnParams, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-68, 49, 0), driveParams, turnParams10_deg(), {});
  // wait(1000, msec);

  // Score in 1st long goal
  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 9;
  driveParams.driveTimeout = 1000;
  chassisReference->driveToPoint(Pose<double>(-27, 49, 0), driveParams, turnParams10_deg(), {.forwards = false});
  // intake.scoreLongGoal(); Not using this since we only need to score 2 blocks
  // intake.spinFullIntake(vex::directionType::fwd);
  // sloper.on();
  // blocker.on();
  // wait(1500, msec);
  // sloper.off();
  // blocker.off();

  // Back away from long goal
  driveParams = driveParams20_in();
  driveParams.driveTimeout = 600;
  chassisReference->driveToPoint(Pose<double>(-47, 49, 0), driveParams, turnParams10_deg(), {});

  // Drive to middle goal
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 1800;
  turnParams = turnParams45_deg();
  turnParams.turnTimeout = 700;
  chassisReference->turnTo(Pose<double>(-15, 15, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-15, 15, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score in middle goal
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(200, msec);
  blocker.off();
  willyNilly.off();
  driveParams = driveParams5_in();
  driveParams.driveTimeout = 150;
  driveParams.driveMinVoltage = 7;
  chassisReference->driveDistance(5, chassisReference->getAbsoluteHeading().angle, driveParams, turnParams10_deg(), {});

  // Curve to other group of middle blocks
  driveParams = driveParams50_in();
  driveParams.driveMaxVoltage = 12;
  // driveParams.driveTimeout = 1300;
  driveParams.driveMinVoltage = 5;
  driveParams.driveSettleError = 5;

  turnParams = turnParams90_deg();
  // turnParams.turnTimeout = 1300;

  willyNilly.delayToggle(1300);
  chassisReference->driveToPoint(Pose<double>(-23.5, -20, 0), driveParams, turnParams, {});
  willyNilly.off();

  // Curve to in front of loader
  driveParams = driveParams30_in();
  driveParams.driveMinVoltage = 3;
  driveParams.driveSettleError = 5;
  // driveParams.driveTimeout = 1300;

  turnParams = turnParams90_deg();
  chassisReference->driveToPoint(Pose<double>(-47, -42, 270), driveParams, turnParams, {});

  // Ram into 2nd loader
  turnParams = turnParams10_deg();
  turnParams.turnTimeout = 300;
  driveParams = driveParams20_in();
  driveParams.driveTimeout = 1200;
  chassisReference->turnTo(Pose<double>(-68, -42, -360), turnParams, {});
  willyNilly.on();
  chassisReference->driveToPoint(Pose<double>(-68, -42, 0), driveParams, turnParams10_deg(), {});

  // Score in 2nd long goal
  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 12;

  chassisReference->driveToPoint(Pose<double>(-27, -45, 0), driveParams, turnParams10_deg(), {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  blocker.on();
  wait(5000, msec);
}