#include "autons.h"
#include "vex.h"

void Autons::solo()
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
  driveParams.driveTimeout = 900;
  chassisReference->driveToPose(Pose<double>(-19, 31, 45), driveParams, turnParams30_deg(), {}, 0.4);

  // Turn to face the center goal location (turn to point (14, -14))
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 400;
  chassisReference->turnTo(Pose<double>(-14, 14, -360), turnParams, {.forwards = false});
  driveParams = driveParams10_in();
  driveParams.driveTimeout = 1000;
  chassisReference->driveToPoint(Pose<double>(-14, 14, 0), driveParams, turnParams10_deg(), {.forwards = false});

  turnParams = turnParams10_deg();
  turnParams.turnTimeout = 200;
  chassisReference->turnTo(Pose<double>(-46.67, 47, -360), turnParams, {});

  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd, 8);
  wait(600, msec);

  // Drive in front of the loader
  driveParams = driveParams50_in();
  driveParams.driveSettleError = 5;
  driveParams.driveMaxVoltage = 12;
  driveParams.driveTimeout = 1100;
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 1100;

  chassisReference->driveToPose(Pose<double>(-45, 50, 90), driveParams, turnParams, {.forwards = false}, 0.2);
  intake.stopFullIntake();

  // Ram into 1st loader
  turnParams = turnParams180_deg();
  turnParams.turnTimeout = 1000;
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 1200;
  chassisReference->turnTo(Pose<double>(-68, 49, -360), turnParams, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-68, 49, 0), driveParams, turnParams10_deg(), {});
  // wait(1000, msec);

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 600;
  driveParams.driveMaxVoltage = 6;
  chassisReference->driveToPoint(Pose<double>(-90, 45, 0), driveParams, turnParams10_deg(), {});
  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(400, msec);
  Left.stop(vex::brakeType::coast);
  Right.stop(vex::brakeType::coast);

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 1600;
  turnParams = turnParams45_deg();
  turnParams.turnTimeout = 700;
  chassisReference->turnTo(Pose<double>(-15, 15, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-15, 15, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score and chill
  sloper.on();
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd, 8);
  wait(250, msec);
  blocker.off();

  // Back away from 1st long goal
  driveParams = driveParams5_in();
  driveParams.driveTimeout = 200;
  driveParams.driveSlew = 12;
  driveParams.driveMinVoltage = 3;
  // chassisReference->driveToPoint(Pose<double>(-37, 49, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveDistance(8, chassisReference->getAbsoluteHeading().angle, driveParams, turnParams10_deg(), {});
  sloper.off();
  finger.on();

  // Turn to group of blocks in middle
  turnParams = turnParams30_deg();
  turnParams.turnTimeout = 600;
  chassisReference->turnTo(Pose<double>(0, 0, 167), turnParams, {});

  // driveParams = driveParams50_in();
  // driveParams.driveTimeout = 2500;
  // driveParams.driveMinVoltage = 2;
  // driveParams.driveSettleError = 20;
  // driveParams.driveSlew = 12;
  // chassisReference->driveToPoint(Pose<double>(-21, -27.2, 0), driveParams, turnParams10_deg(), {});

  willyNilly.delayToggle(300);

  // turnParams = turnParams30_deg();
  // turnParams.turnTimeout = 400;
  // chassisReference->turnTo(Pose<double>(-46.67, -53, -360), turnParams, {});

  // Drive in front of the loader
  driveParams = driveParams50_in();
  driveParams.driveTimeout = 2000;
  driveParams.driveSettleError = 10;
  driveParams.driveMinVoltage = 3;
  driveParams.driveSlew = 2;
  chassisReference->driveToPoint(Pose<double>(-47.5, -54, 0), driveParams, turnParams45_deg(), {});

  // Turn toward loader entrance point
  turnParams = turnParams45_deg();
  turnParams.turnTimeout = 150;
  chassisReference->turnTo(Pose<double>(-80, -54, -360), turnParams, {});

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  driveParams = driveParams30_in();
  driveParams.driveSettleError = 7;
  driveParams.driveTimeout = 1300;

  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 1100;
  chassisReference->driveToPose(Pose<double>(-47, -40, 270), driveParams, turnParams, {}, 0.2);

  // Line up to long goal
  turnParams = turnParams10_deg();
  turnParams.turnTimeout = 300;
  driveParams = driveParams20_in();
  driveParams.driveTimeout = 1200;
  chassisReference->turnTo(Pose<double>(-68, -40, -360), turnParams, {});
  willyNilly.on();
  chassisReference->driveToPoint(Pose<double>(-68, -40, 0), driveParams, turnParams10_deg(), {});

  driveParams = driveParams30_in();
  driveParams.driveTimeout = 1000;
  driveParams.driveSlew = 12;
  chassisReference->driveToPoint(Pose<double>(-25, -56, 0), driveParams, turnParams10_deg(), {.forwards = false});

  chassisReference->driveToPoint(Pose<double>(-27, -42, 0), driveParams, turnParams10_deg(), {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  blocker.on();
  wait(10000, msec);
}