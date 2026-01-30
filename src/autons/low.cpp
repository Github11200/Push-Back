#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::low()
{
  DriveParams driveParams;
  TurnParams turnParams;

  chassisReference->odometry->setPosition(-46.5, -16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  IntakeRear.stop();
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  sloper.on();

  willyNilly.delayToggle(1100);

  // Drive to the middle blocks
  turnParams = turnParams30_deg();
  driveParams = driveParams30_in();
  chassisReference->turnTo(Pose<double>(-23, -23, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-23, -23, 0), driveParams, turnParams10_deg(), {});

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

  // Drive towards and score in low goal
  turnParams = turnParams45_deg();
  driveParams = driveParams10_in();
  chassisReference->turnTo(Pose<double>(-13, -13, -360), turnParams, {});
  willyNilly.off();
  intake.spinFullIntake(vex::directionType::rev, 6);
  chassisReference->driveToPoint(Pose<double>(-13, -13, 0), driveParams, turnParams10_deg(), {});
  wait(300, msec);

  // Drive (in reverse) in front of the loader
  driveParams = driveParams30_in();
  driveParams.driveTimeout = 2000;
  willyNilly.on();
  chassisReference->driveToPoint(Pose<double>(-47, -47.5, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Ram into 1st loader
  turnParams = turnParams135_deg();
  turnParams.turnTimeout = 700;
  driveParams = driveParams20_in();
  chassisReference->turnTo(Pose<double>(-68, -47.5, -360), turnParams, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 200, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 700, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams30_in();
  driveParams.driveTimeout = 1000;
  turnParams.turnTimeout = 200;
  chassisReference->turnTo(Pose<double>(-27, -48, -360), turnParams, {.forwards = false});
  driveParams.driveTimeout = 1050;
  chassisReference->driveToPoint(Pose<double>(-27, -48, 0), driveParams, turnParams10_deg(), {.forwards = false});

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
  chassisReference->driveToPoint(Pose<double>(-37, -48, 0), driveParams, turnParams10_deg(), {});

  // Reposition to align wing
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  driveParams = driveParams10_in();
  driveParams.driveTimeout = 900;
  chassisReference->turnTo(Pose<double>(-37, -59.5, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-37, -59.5, 0), driveParams, turnParams10_deg(), {});

  // Push blocks in goal
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 550;
  driveParams = driveParams10_in();
  driveParams.driveMaxVoltage = 8;
  chassisReference->turnTo(Pose<double>(-15, -58.5, -360), turnParams, {.forwards = false});
  driveParams.driveTimeout = 10000;
  chassisReference->driveToPoint(Pose<double>(-15, -58.5, 0), driveParams, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);

  wait(2000, msec);
}