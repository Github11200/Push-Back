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

  willyNilly.delayToggle(700);

  // Drive to the middle blocks
  driveParams = driveParams50_in();
  driveParams.driveSettleError = 3;
  driveParams.driveMaxVoltage = 12;
  chassisReference->driveToPose(Pose<double>(-8.5, 31, 45), driveParams, turnParams30_deg(), {}, 0.6);
  willyNilly.off();
  willyNilly.delayToggle(1000);

  // Intake the blocks under the long goal
  driveParams = driveParams20_in();
  turnParams = turnParams10_deg();
  chassisReference->driveToPoint(Pose<double>(-8.5, 41, 0), driveParams, turnParams10_deg(), {});

  // Curve back to in front of loader
  driveParams = driveParams50_in();
  chassisReference->driveToPose(Pose<double>(-47, 50, 315), driveParams, turnParams135_deg(), {.forwards = false}, 0.6);
  intake.stopFullIntake();

  // Ram into 1st loader
  turnParams = turnParams135_deg();
  turnParams.turnTimeout = 700;
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 1500;
  chassisReference->turnTo(Pose<double>(-68, 49, -360), turnParams, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-68, 49, 0), driveParams, turnParams10_deg(), {});
  // wait(1000, msec);

  // Score in 1st long goal
  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 2000;
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
  turnParams = turnParams45_deg();
  turnParams.turnTimeout = 700;
  chassisReference->turnTo(Pose<double>(-15, 15, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-15, 15, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Score in middle goal
  // blocker.on();
  // intake.spinFullIntake(vex::directionType::fwd);
  wait(200, msec);
  // blocker.off();
  // willyNilly.off();

  // Curve to other group of middle blocks
  driveParams = driveParams50_in();
  chassisReference->driveToPose(Pose<double>(-23.5, -20, 155), driveParams, turnParams180_deg(), {}, 0.9);
  willyNilly.on();

  // Curve to in front of loader
  driveParams = driveParams30_in();
  chassisReference->driveToPose(Pose<double>(-47, -47, 270), driveParams, turnParams90_deg(), {}, 0.6);

  // Ram into 2nd loader
  turnParams = turnParams10_deg();
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  chassisReference->turnTo(Pose<double>(-68, -49, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-68, -49, 0), driveParams, turnParams10_deg(), {});

  // Score in 2nd long goal
  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 12;
  chassisReference->driveToPoint(Pose<double>(-27, -49, 0), driveParams, turnParams10_deg(), {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  blocker.on();
  wait(5000, msec);
}