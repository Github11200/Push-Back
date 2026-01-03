#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::skills()
{
  DriveParams driveParams;
  TurnParams turnParams;

  // Set starting coordinates
  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  // Intake the middle 4 blocks
  intake.spinFullIntake(vex::directionType::fwd);
  blocker.off();

  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 6;
  driveParams.driveSettleError = 1;

  willyNilly.delayToggle(650);
  chassisReference->driveToPose(Pose<double>(-15, 31, 45), driveParams, turnParams30_deg(), {}, 0.6);

  // Go back to align to middle goal
  driveParams = driveParams5_in();
  driveParams.driveTimeout = 500;

  chassisReference->driveToPoint(Pose<double>(-20.293, 24.674, 0), driveParams, turnParams10_deg(), {.forwards = false});
  intake.stopFullIntake();

  // Go up to middle goal
  driveParams = driveParams10_in();
  driveParams.driveMaxVoltage = 3;
  driveParams.driveTimeout = 1000;

  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 1000;
  chassisReference->turnTo(Pose<double>(-13.3, 15.287, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-13.3, 15.287, -360), driveParams, turnParams10_deg(), {.forwards = false});

  // Drive to 1st dispenser
  turnParams = turnParams10_deg();
  turnParams.turnTimeout = 300;

  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 7;

  chassisReference->turnTo(Pose<double>(-47, 49, -360), turnParams, {});

  // Score in middle goal
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(1000, msec);
  blocker.off();
  intake.stopFullIntake();

  chassisReference->driveToPoint(Pose<double>(-47, 49, 0), driveParams, turnParams10_deg(), {});

  // Ram into 1st dispenser
  turnParams = turnParams30_deg();
  turnParams.turnTimeout = 800;

  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->turnTo(Pose<double>(-68, 49, -360), turnParams, {});

  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 2500;
  chassisReference->driveToPoint(Pose<double>(-68, 49, 0), driveParams, turnParams10_deg(), {});
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

  chassisReference->turnTo(Pose<double>(42, 49, -360), turnParams90_deg(), {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 49, 0), driveParams10_in(), turnParams10_deg(), {.forwards = false});

  // Align to long goal
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 4;
  driveParams.driveTimeout = 1500;

  chassisReference->turnTo(Pose<double>(25, 49, -360), turnParams90_deg(), {.forwards = false});
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
  chassisReference->turnTo(Pose<double>(25, 49, -360), turnParams30_deg(), {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(25, 49, 0), driveParams, turnParams10_deg(), {.forwards = false});
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
  chassisReference->turnTo(Pose<double>(39, -42, -360), turnParams90_deg(), {});
  chassisReference->driveToPoint(Pose<double>(39, -42, 0), driveParams, turnParams10_deg(), {});

  // Ram into 3rd dispenser
  chassisReference->turnTo(Pose<double>(68, -42, -360), turnParams90_deg(), {});
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 2500;
  chassisReference->driveToPoint(Pose<double>(68, -42, 0), driveParams, turnParams10_deg(), {});

  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 8;

  turnParams = turnParams30_deg();
  turnParams.turnSettleError = 1.5;

  // Curve through alleyway
  chassisReference->driveToPose(Pose<double>(23, -57, 240), driveParams, turnParams, {.forwards = false});
  willyNilly.off();
  chassisReference->driveToPoint(Pose<double>(-42, -57, 0), driveParams, turnParams10_deg(), {.forwards = false});

  chassisReference->turnTo(Pose<double>(-42, -42, -360), turnParams90_deg(), {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -42, 0), driveParams20_in(), turnParams10_deg(), {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -42, -360), turnParams90_deg(), {.forwards = false});

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

  // Curve to red parking zone
  chassisReference->turnTo(Pose<double>(-63, -17, -360), turnParams45_deg(), {});
  chassisReference->driveToPoint(Pose<double>(-63, -17, 0), driveParams30_in(), turnParams10_deg(), {});

  // Clear parking zone and park
  chassisReference->driveToPoint(Pose<double>(-63, 1, 0), {}, {}, {});
}