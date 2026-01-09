#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::high()
{
  DriveParams driveParams;
  TurnParams turnParams;

  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd);

  willyNilly.delayToggle(500);

  // Drive to the middle blocks
  driveParams = driveParams50_in();
  driveParams.driveSettleError = 3;
  driveParams.driveTimeout = 1000;
  chassisReference->driveToPose(Pose<double>(-19, 31, 45), driveParams, turnParams30_deg(), {}, 0.4);
  chassisReference->driveDistance(1, chassisReference->getAbsoluteHeading().angle, driveParams5_in(), turnParams10_deg(), {.forwards = false});

  // Intake the blocks under the long goal
  // willyNilly.off();
  // willyNilly.delayToggle(1000);
  // driveParams = driveParams20_in();
  // turnParams = turnParams10_deg();
  // chassisReference->turnTo(Pose<double>(-8.5, 41, -360), turnParams, {});
  // chassisReference->driveToPoint(Pose<double>(-8.5, 41, 0), driveParams, turnParams10_deg(), {});

  // Drive back
  // turnParams = turnParams10_deg();
  // driveParams = driveParams20_in();
  // chassisReference->turnTo(Pose<double>(-23, 23, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-23, 23, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Turn to face the center goal location (turn to point (14, -14))
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  chassisReference->turnTo(Pose<double>(-14, 14, -360), turnParams, {.forwards = false});
  driveParams = driveParams10_in();
  driveParams.driveTimeout = 1000;
  chassisReference->driveToPoint(Pose<double>(-14, 14, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // turnParams = turnParams10_deg();
  // turnParams.turnTimeout = 200;
  // chassisReference->turnTo(Pose<double>(-46.67, 48, -360), turnParams, {});

  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd, 8);
  wait(700, msec);
  blocker.off();

  // Drive in front of the loader
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 1500;
  chassisReference->driveToPoint(Pose<double>(-46.67, 51, 0), driveParams, turnParams10_deg(), {});

  // Turn toward loader entrance point
  turnParams = turnParams45_deg();
  turnParams.turnTimeout = 800;
  chassisReference->turnTo(Pose<double>(-70, 51, -360), turnParams, {});

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 900;
  driveParams.driveMaxVoltage = 5;
  chassisReference->driveToPoint(Pose<double>(-70, 51, 0), driveParams, turnParams10_deg(), {});

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 1000;
  chassisReference->turnTo(Pose<double>(-25, 51, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-25, 51, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  sloper.on();
  blocker.on();
  wait(800, msec);
  sloper.off();

  // Back away from goal
  driveParams = driveParams5_in();
  driveParams.driveTimeout = 300;
  chassisReference->driveDistance(5, chassisReference->getAbsoluteHeading().angle, driveParams, turnParams10_deg(), {});
  // chassisReference->driveToPoint(Pose<double>(-37, 47, 0), driveParams, turnParams10_deg(), {});

  // Reposition to align wing
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  driveParams = driveParams5_in();
  driveParams.driveTimeout = 900;
  chassisReference->turnTo(Pose<double>(0, 0, 0), turnParams, {});
  chassisReference->driveDistance(8, chassisReference->getAbsoluteHeading().angle, driveParams, turnParams10_deg(), {});
  // chassisReference->driveToPoint(Pose<double>(-37, 37.5, 0), driveParams, turnParams10_deg(), {});

  // Push blocks in goal
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 550;
  driveParams = driveParams30_in();
  chassisReference->turnTo(Pose<double>(0, 0, 90), turnParams, {});
  chassisReference->driveDistance(35, chassisReference->getAbsoluteHeading().angle, driveParams30_in(), turnParams, {});
  // chassisReference->driveToPoint(Pose<double>(-10, 38.3, 0), driveParams, turnParams10_deg(), {});

  wait(2000, msec);
}