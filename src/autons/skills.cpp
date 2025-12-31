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

  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 8;
  driveParams.driveSettleError = 1;

  chassisReference->driveToPose(Pose<double>(-15, 31, 45), driveParams, turnParams30_deg(), {}, 0.6);

  // Go back to align to middle goal
  chassisReference->driveToPoint(Pose<double>(-20.293, 24.674, 0), driveParams10_in(), turnParams10_deg(), {.forwards = false});
  intake.stopFullIntake();

  // Go up to middle goal
  driveParams = driveParams10_in();
  driveParams.driveMaxVoltage = 3;

  turnParams = turnParams90_deg();
  turnParams.turnTimeout = 800;
  chassisReference->turnTo(Pose<double>(-13.7, 15.287, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-13.7, 15.287, -360), driveParams, turnParams10_deg(), {.forwards = false});

  // Score in middle goal
  // Could try to color sort the blue blocks out
  // blocker.on();
  // wait(1500, msec);
  // blocker.off();

  // Drive to 1st dispenser
  // willyNilly.on();

  turnParams = turnParams10_deg();
  turnParams.turnTimeout = 500;

  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 6;

  chassisReference->turnTo(Pose<double>(-47, 49.5, -360), turnParams, {});
  chassisReference->driveToPoint(Pose<double>(-47, 49.5, 0), driveParams30_in(), turnParams10_deg(), {});

  // Ram into 1st dispenser
  turnParams = turnParams30_deg();
  turnParams.turnTimeout = 800;

  chassisReference->turnTo(Pose<double>(-68, 49.5, -360), turnParams, {});

  driveParams = DriveParams();
  driveParams.driveMaxVoltage = 4;
  driveParams.driveTimeout = 2500;
  chassisReference->driveToPoint(Pose<double>(-68, 49.5, 0), driveParams, turnParams10_deg(), {});

  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 10;

  turnParams = turnParams30_deg();
  turnParams.turnSettleError = 2;

  // Curve through alleyway
  chassisReference->driveToPose(Pose<double>(-23, 61.5, 60), driveParams, turnParams, {.forwards = false}, 0.5);
  willyNilly.off();

  turnParams = turnParams10_deg();
  turnParams.turnTimeout = 500;

  driveParams = driveParams50_in();
  driveParams.driveMaxVoltage = 9;
  driveParams.driveSlew = 0.4;

  chassisReference->turnTo(Pose<double>(42, 61.5, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 61.5, 0), driveParams, turnParams10_deg(), {.forwards = false});

  driveParams = driveParams30_in();
  driveParams.driveMaxVoltage = 6;

  chassisReference->driveToPoint(Pose<double>(42, 47, 90), driveParams, turnParams30_deg(), {.forwards = false}, 0.5);

  // Align to long goal
  driveParams = driveParams30_in();
  driveParams.driveTimeout = 1500;
  driveParams.driveMaxVoltage = 12;

  turnParams = turnParams180_deg();
  turnParams.turnSettleTime = 500;
  turnParams.turnMaxVoltage = 8;

  chassisReference->turnTo(Pose<double>(27, 47, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(33, 47, 0), driveParams, turnParams10_deg(), {.forwards = false});
  driveParams.driveMaxVoltage = 4;
  chassisReference->driveToPoint(Pose<double>(27, 47, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.on();

  // 1st Score
  // sloper.on();
  // wait(1500, msec);
  // chassisReference->odometry->setPosition(28.5, 47, chassisReference->getAbsoluteHeading().angle);
  // sloper.off();

  // Ram into 2nd dispenser
  driveParams = driveParams20_in();
  driveParams.driveMaxVoltage = 5;
  driveParams.driveTimeout = 2500;

  chassisReference->driveToPoint(Pose<double>(68, 47, 0), driveParams, turnParams10_deg(), {});

  // Align to long goal
  driveParams.driveTimeout = 2000;
  chassisReference->driveToPoint(Pose<double>(27, 50, 0), driveParams, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // 2nd Score
  // sloper.on();
  // wait(1500, msec);
  // chassisReference->odometry->setPosition(28.5, 47, chassisReference->getAbsoluteHeading().angle);
  // sloper.off();

  // Curve to blue parking zone
  chassisReference->driveToPose(Pose<double>(58, 35, 135), driveParams20_in(), turnParams30_deg(), {}, 0.2);
  chassisReference->driveToPose(Pose<double>(63, 17, 180), driveParams20_in(), turnParams30_deg(), {}, 0.1);

  return;

  // Drive through blue parking zone, going further to make sure to intake all blocks
  chassisReference->driveToPoint(Pose<double>(63, -30, 0), {}, {}, {});

  // Back up against blue parking zone - maybe position reset against barrier?
  chassisReference->driveToPoint(Pose<double>(63, -17, 0), {}, {}, {.forwards = false});

  // Curve to eat the center blocks
  chassisReference->driveToPoint(Pose<double>(23, -23, 0), {}, {}, {});

  // Line up to middle goal
  chassisReference->turnTo(Pose<double>(13, -13, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(13, -13, 0), {}, {}, {.forwards = false});

  // Score in middle goal
  blocker.on();
  wait(1500, msec);
  blocker.off();

  // Go towards 3rd dispenser
  willyNilly.on();
  chassisReference->driveToPoint(Pose<double>(47, -47, 0), {}, {}, {});

  // Ram into 3rd dispenser
  chassisReference->turnTo(Pose<double>(68, 47, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(68, 47, 0), {.driveMaxVoltage = 5, .driveTimeout = 2500}, {}, {});

  // Curve through alleyway
  chassisReference->driveToPose(Pose<double>(23, -61, 240), {}, {}, {.forwards = false});
  willyNilly.off();
  chassisReference->driveToPoint(Pose<double>(-42, -61, 0), {}, {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -47, 0), {}, {}, {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-33, -47, 0), {.driveTimeout = 1500}, {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {.driveTimeout = 300, .driveMaxVoltage = 5}, {}, {.forwards = false});
  willyNilly.on();

  // 3rd Score
  sloper.on();
  wait(1500, msec);
  chassisReference->odometry->setPosition(-28.5, -47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // Ram into 4th dispenser
  chassisReference->driveToPoint(Pose<double>(-68, -47, 0), {.driveMaxVoltage = 5, .driveTimeout = 2500}, {}, {});

  // Align to long goal
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {.driveTimeout = 2000}, {}, {.forwards = false});
  willyNilly.off();

  // 4th Score
  sloper.on();
  wait(1500, msec);
  chassisReference->odometry->setPosition(-28.5, -47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // Curve to red parking zone
  chassisReference->driveToPose(Pose<double>(-58, -35, 315), {}, {}, {});
  chassisReference->driveToPose(Pose<double>(-63, -17, 0), {}, {}, {});

  // Clear parking zone and park
  chassisReference->driveToPoint(Pose<double>(-63, 1, 0), {}, {}, {});
}