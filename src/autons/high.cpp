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
  driveParams.driveMaxVoltage = 12;
  chassisReference->driveToPose(Pose<double>(-19, 31, 45), driveParams, turnParams30_deg(), {}, 0.3);

  // Intake the blocks under the long goal
  willyNilly.off();
  willyNilly.delayToggle(1000);
  driveParams = driveParams20_in();
  turnParams = turnParams10_deg();
  chassisReference->turnTo(Pose<double>(-8.5, 41, 0), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-8.5, 41, 0), driveParams, turnParams10_deg(), {});

  // Drive back
  turnParams = turnParams10_deg();
  driveParams = driveParams20_in();
  chassisReference->turnTo(Pose<double>(-23, 23, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-23, 23, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Turn to face the center goal location (turn to point (14, -14))
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  chassisReference->turnTo(Pose<double>(-14, 14, -360), turnParams, {.forwards = false});
  driveParams = driveParams10_in();
  driveParams.driveTimeout = 1000;
  chassisReference->driveToPoint(Pose<double>(-14, 14, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // turnParams = turnParams10_deg();
  // turnParams.turnTimeout = 400;
  // chassisReference->turnTo(Pose<double>(-46.67, 47, -360), turnParams, {});

  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd, 8);
  wait(700, msec);

  // Drive in front of the loader
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 2000;
  driveParams.driveSettleError = 12;
  driveParams.driveMinVoltage = 2;
  chassisReference->driveToPoint(Pose<double>(-46.67, 45.75, 0), driveParams, turnParams10_deg(), {});

  // Turn toward loader entrance point
  turnParams = turnParams45_deg();
  turnParams.turnTimeout = 800;
  chassisReference->turnTo(Pose<double>(-70, 45.75, -360), turnParams, {});
  blocker.off();

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 600;
  driveParams.driveMaxVoltage = 6;
  chassisReference->driveToPoint(Pose<double>(-90, 45.75, 0), driveParams, turnParams10_deg(), {});
  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(500, msec);
  Left.stop(vex::brakeType::coast);
  Right.stop(vex::brakeType::coast);

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 1000;
  chassisReference->turnTo(Pose<double>(-25, 46.25, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-25, 46.25, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  sloper.on();
  blocker.on();
  wait(1000, msec);
  sloper.off();

  // Back away from goal
  driveParams = driveParams5_in();
  driveParams.driveTimeout = 300;
  chassisReference->driveDistance(5, chassisReference->getAbsoluteHeading().angle, driveParams, turnParams10_deg(), {});
  // chassisReference->driveToPoint(Pose<double>(-37, 47, 0), driveParams, turnParams10_deg(), {});

  // Reposition to align wing
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  driveParams = driveParams10_in();
  driveParams.driveTimeout = 900;
  chassisReference->turnTo(Pose<double>(0, 0, 0), turnParams, {});
  chassisReference->driveDistance(10, chassisReference->getAbsoluteHeading().angle, driveParams, turnParams10_deg(), {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-37, 37.5, 0), driveParams, turnParams10_deg(), {});

  // Push blocks in goal
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 550;
  chassisReference->turnTo(Pose<double>(0, 0, 270), turnParams, {});
  chassisReference->driveDistance(10, chassisReference->getAbsoluteHeading().angle, driveParams10_in(), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-10, 38.3, 0), driveParams, turnParams10_deg(), {});

  wait(2000, msec);
}