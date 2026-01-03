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

  // Drive to the middle blocks
  driveParams = driveParams30_in();
  chassisReference->driveToPose(Pose<double>(-10.5, 31, 45), driveParams, turnParams45_deg(), {});

  // Intake the blocks under the long goal
  driveParams = driveParams10_in();
  turnParams = turnParams10_deg();
  chassisReference->turnTo(Pose<double>(-7.7, 39, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-7.7, 39, 0), driveParams, turnParams10_deg(), {});
  willyNilly.on();

  // Curve back to in front of loader
  driveParams = driveParams50_in();
  chassisReference->driveToPose(Pose<double>(-47, 47, 315), driveParams, turnParams135_deg(), {.forwards = false});
  intake.stopFullIntake();

  // Ram into 1st loader
  turnParams = turnParams135_deg();
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  chassisReference->turnTo(Pose<double>(-68, 47, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-68, 47, 0), driveParams, turnParams10_deg(), {});
  wait(1500, msec);

  // Score in 1st long goal
  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 12;
  chassisReference->driveToPoint(Pose<double>(-27, 47, 0), driveParams, turnParams10_deg(), {.forwards = false});
  // intake.scoreLongGoal(); Not using this since we only need to score 2 blocks
  spinFullIntake(vex::directionType::fwd);
  sloper.on();
  blocker.on();
  wait(1500, msec);
  sloper.off();
  blocker.off();

  // Back away from long goal
  driveParams = driveParams20_in();
  chassisReference->driveToPoint(Pose<double>(-47, 47, 0), driveParams, turnParams10_deg(), {});

  // Drive to middle goal
  driveParams = driveParams30_in();
  turnParams = turnParams45_deg();
  chassisReference->turnTo(Pose<double>(-13, 13, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-13, 13, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Score in middle goal
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(1000, msec);
  blocker.off();
  willyNilly.off();

  // Curve to other group of middle blocks
  driveParams = driveParams50_in();
  chassisReference->driveToPose(Pose<double>(-23.5, -20, 155), driveParams, turnParams180_deg(), {});
  willyNilly.on();

  // Curve to in front of loader
  driveParams = driveParams30_in();
  chassisReference->driveToPose(Pose<double>(-47, -47, 270), driveParams, turnParams90_deg(), {});

  // Ram into 2nd loader
  turnParams = turnParams10_deg();
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  chassisReference->turnTo(Pose<double>(-68, -47, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-68, -47, 0), driveParams, turnParams10_deg(), {});

  // Score in 2nd long goal
  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 12;
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), driveParams, turnParams10_deg(), {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  blocker.on();
  wait(5000, msec);
}