#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::high()
{
  DriveParams driveParams;
  TurnParams turnParams;

  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();

  willyNilly.delayToggle(500);

  // Drive to the middle blocks
  turnParams = turnParams10_deg();
  driveParams = driveParams30_in();
  chassisReference->turnTo(Pose<double>(-23, 23, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-23, 23, 0), driveParams, turnParams10_deg(), {});

  // // Intake the blocks under the long goal
  // willyNilly.off();
  // willyNilly.delayToggle(1000);
  // driveParams = driveParams20_in();
  // turnParams = turnParams10_deg();
  // chassisReference->turnTo(Pose<double>(-8.5, 41, 0), turnParams, {});
  // chassisReference->driveToPoint(Pose<double>(-8.5, 41, 0), driveParams, turnParams10_deg(), {});

  // // Drive back
  // turnParams = turnParams10_deg();
  // driveParams = driveParams20_in();
  // chassisReference->turnTo(Pose<double>(-23, 23, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-23, 23, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Turn to face the center goal location (turn to point (14, -14))
  turnParams = turnParams135_deg();
  driveParams = driveParams10_in();
  driveParams.driveTimeout = 1000;
  chassisReference->turnTo(Pose<double>(-14, 14, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-14, 14, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // turnParams = turnParams10_deg();
  // turnParams.turnTimeout = 400;
  // chassisReference->turnTo(Pose<double>(-46.67, 47, -360), turnParams, {});

  // Score middle goal
  sloper.off();
  intake.spinFullIntake(vex::directionType::fwd, 8);
  wait(700, msec);
  sloper.on();
  intake.stopFullIntake();

  // Drive in front of the loader
  driveParams = driveParams30_in();
  driveParams.driveTimeout = 2000;
  chassisReference->driveToPoint(Pose<double>(-47, 47, 0), driveParams, turnParams10_deg(), {});

  // Ram into 1st loader
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 700;
  driveParams = driveParams20_in();
  chassisReference->turnTo(Pose<double>(-68, 47, -360), turnParams, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 500, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 300, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams30_in();
  driveParams.driveTimeout = 1000;
  turnParams.turnTimeout = 200;
  chassisReference->turnTo(Pose<double>(-27, 47, -360), turnParams, {.forwards = false});
  driveParams.driveTimeout = 1050;
  chassisReference->driveToPoint(Pose<double>(-27, 47, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  blocker.on();
  wait(900, msec);
  blocker.off();
  intake.stopFullIntake();

  // Back away from goal
  driveParams = driveParams10_in();
  driveParams.driveTimeout = 600;
  chassisReference->driveDistance(10, 90, driveParams, turnParams10_deg(), {});
  // chassisReference->driveToPoint(Pose<double>(-37, 47, 0), driveParams, turnParams10_deg(), {});

  // Reposition to align wing
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  driveParams = driveParams10_in();
  driveParams.driveTimeout = 900;
  chassisReference->turnTo(Pose<double>(0, 0, 0), turnParams, {});
  chassisReference->driveDistance(10, 0, driveParams, turnParams10_deg(), {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-37, 37.5, 0), driveParams, turnParams10_deg(), {});

  // Push blocks in goal
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 550;
  driveParams = driveParams10_in();
  chassisReference->turnTo(Pose<double>(0, 0, 90), turnParams, {});
  driveParams.driveTimeout = 10000;
  chassisReference->driveDistance(40, 90, driveParams, turnParams10_deg(), {.forwards = true});
  // chassisReference->driveToPoint(Pose<double>(-10, 38.3, 0), driveParams, turnParams10_deg(), {});

  wait(2000, msec);
}