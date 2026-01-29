#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::skills()
{
  DriveParams driveParams;
  TurnParams turnParams;

  // Set starting coordinates
  chassisReference->odometry->setPosition(-63, -16, 0);
  chassisReference->odometry->startPositionTrackThread(false);

  // Start up the intake
  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();

  // Drive through park zone
  chassisReference->driveWithVoltage(12, 2000, 0, turnParams10_deg(), {});

  // Drive back against park zone and distance reset y-position
  chassisReference->driveWithVoltage(-5, 1000, 0, turnParams10_deg(), {});
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, 16, chassisReference->odometry->getPose().orientation.angle);

  // Go forwards a bit
  driveParams = driveParams5_in();
  chassisReference->driveToPoint(Pose<double>(-63, 23, 0), driveParams, turnParams10_deg(), {});

  // Distance reset x-position against the wall
  turnParams = turnParams90_deg();
  chassisReference->turnTo(Pose<double>(-23, 23, -360), turnParams, {});
  chassisReference->driveWithVoltage(-5, 700, 0, turnParams10_deg(), {});
  chassisReference->odometry->setPosition(-62, chassisReference->odometry->getPose().position.y, chassisReference->odometry->getPose().orientation.angle);

  // Eat center blocks
  turnParams = turnParams10_deg();
  driveParams = driveParams30_in();
  chassisReference->turnTo(Pose<double>(-23, 23, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-23, 23, 0), driveParams, turnParams10_deg(), {});

  // Align to middle goal
  turnParams = turnParams135_deg();
  driveParams = driveParams10_in();
  chassisReference->turnTo(Pose<double>(-13, 13, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-13, 13, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Score in middle goal
  sloper.off();
  intake.spinFullIntake(vex::directionType::fwd, 5);
  wait(1500, msec);
  sloper.on();

  return;

  // Drive to 1st dispenser
  turnParams = turnParams10_deg();
  turnParams.turnTimeout = 300;

  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 7;

  chassisReference->turnTo(Pose<double>(-47, 49, -360), turnParams, {});

  // Score in middle goal
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd, 8);
  wait(1000, msec);

  chassisReference->driveToPoint(Pose<double>(-47, 49, 0), driveParams, turnParams10_deg(), {});

  // Ram into 1st loader
  turnParams = turnParams30_deg();
  turnParams.turnTimeout = 800;

  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->turnTo(Pose<double>(-68, 51, -360), turnParams, {});
  willyNilly.on();
  blocker.off();

  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 2500;
  chassisReference->driveToPoint(Pose<double>(-68, 50, 0), driveParams, turnParams10_deg(), {});
  wait(1500, msec);

  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 8;

  turnParams = turnParams30_deg();
  turnParams.turnSettleError = 1.5;

  // Curve through alleyway
  chassisReference->driveToPose(Pose<double>(-23, 63, 60), driveParams, turnParams, {.forwards = false}, 0.1);
  willyNilly.off();
  intake.stopFullIntake();

  turnParams = turnParams10_deg();
  turnParams.turnTimeout = 1000;

  driveParams = driveParams50_in();
  driveParams.driveMaxVoltage = 6;
  driveParams.driveSlew = 0.2;

  chassisReference->turnTo(Pose<double>(42, 63, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 63, 0), driveParams, turnParams10_deg(), {.forwards = false});
  wait(200, msec);

  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 600;
  chassisReference->turnTo(Pose<double>(42, 49, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 49, 0), driveParams10_in(), turnParams10_deg(), {.forwards = false});

  // Align to long goal
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 4;
  driveParams.driveTimeout = 1500;

  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  chassisReference->turnTo(Pose<double>(25, 49, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(25, 49, 0), driveParams, turnParams30_deg(), {.forwards = false});

  // 1st Score
  intake.scoreLongGoal();

  // Ram into 2nd dispenser
  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 2500;

  willyNilly.on();
  chassisReference->turnTo(Pose<double>(58, 48, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(58, 48, 0), driveParams, turnParams10_deg(), {});

  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 5;

  // Align to long goal
  chassisReference->turnTo(Pose<double>(25, 48, -360), turnParams30_deg(), {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(25, 48, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // 2nd Score
  intake.scoreLongGoal();

  // Back away from 1st goal
  driveParams = driveParams10_in();
  chassisReference->driveToPoint(Pose<double>(39, 49, 0), driveParams, turnParams10_deg(), {});

  // Drive across the field towards 3rd dispenser
  willyNilly.on();
  driveParams = driveParams50_in();
  driveParams.driveMaxVoltage = 8;
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  chassisReference->turnTo(Pose<double>(39, -43, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(39, -43, 0), driveParams, turnParams10_deg(), {});

  // Ram into 3rd dispenser
  chassisReference->turnTo(Pose<double>(68, -43, -360), turnParams90_deg(), {});
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 2500;
  chassisReference->driveToPoint(Pose<double>(68, -43, 0), driveParams, turnParams10_deg(), {});

  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 8;

  turnParams = turnParams30_deg();
  turnParams.turnSettleError = 1.5;

  // Curve through alleyway
  chassisReference->driveToPose(Pose<double>(23, -57, 240), driveParams, turnParams, {.forwards = false});
  willyNilly.off();
  chassisReference->driveToPoint(Pose<double>(-42, -57, 0), driveParams, turnParams10_deg(), {.forwards = false});

  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  chassisReference->turnTo(Pose<double>(-42, -42, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -42, 0), driveParams20_in(), turnParams10_deg(), {.forwards = false});

  // Align to long goal
  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 500;
  chassisReference->turnTo(Pose<double>(-27, -42, -360), turnParams, {.forwards = false});

  driveParams = driveParams20_in();
  driveParams.driveTimeout = 1500;
  driveParams.driveMaxVoltage = 5;
  chassisReference->driveToPoint(Pose<double>(-27, -42, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.on();

  // 3rd Score
  // sloper.on();
  // wait(1500, msec);
  // chassisReference->odometry->setPosition(-28.5, -47, chassisReference->getAbsoluteHeading().angle);
  // sloper.off();

  // Ram into 4th dispenser
  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 2500;
  chassisReference->driveToPoint(Pose<double>(-68, -41, 0), driveParams, turnParams10_deg(), {});

  // Align to long goal
  driveParams = driveParams30_in();
  driveParams.driveTimeout = 2000;
  driveParams.driveMaxVoltage = 5;
  chassisReference->driveToPoint(Pose<double>(-27, -42, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // 4th Score
  // sloper.on();
  // wait(1500, msec);
  // chassisReference->odometry->setPosition(-28.5, -44, chassisReference->getAbsoluteHeading().angle);
  // sloper.off();

  driveParams = driveParams10_in();
  driveParams.driveTimeout = 700;
  chassisReference->driveDistance(10, chassisReference->getAbsoluteHeading().angle, driveParams, turnParams10_deg(), {});

  // Curve to red parking zone
  turnParams = turnParams45_deg();
  turnParams.turnTimeout = 600;
  driveParams = driveParams30_in();
  driveParams.driveTimeout = 1000;
  driveParams.driveMinVoltage = 1;
  driveParams.driveSettleError = 3;
  chassisReference->turnTo(Pose<double>(-63, -17, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-63, -17, 0), driveParams, turnParams10_deg(), {});

  // Clear parking zone and park
  turnParams = turnParams45_deg();
  turnParams.turnTimeout = 800;
  chassisReference->turnTo(Pose<double>(-63, 1, -360), turnParams, {});

  finger.on();
  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(1, sec);
  Left.stop(coast);
  Right.stop(coast);
}