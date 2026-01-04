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

  willyNilly.delayToggle(650);

  // Drive to the middle blocks
  driveParams = driveParams50_in();
  driveParams.driveMaxVoltage = 12;
  chassisReference->driveToPose(Pose<double>(-19, 31, 45), driveParams, turnParams30_deg(), {}, 0.3);

  // Drive back
  turnParams = turnParams10_deg();
  driveParams = driveParams20_in();
  chassisReference->turnTo(Pose<double>(-23, 23, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-23, 23, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Turn to face the center goal location (turn to point (14, -14))
  turnParams = turnParams90_deg();
  chassisReference->turnTo(Pose<double>(-12, 12, -360), turnParams, {.forwards = false});
  intake.stopFullIntake();
  driveParams = driveParams10_in();
  chassisReference->driveToPoint(Pose<double>(-12, 12, 0), driveParams, turnParams10_deg(), {.forwards = false});

  sloper.on();
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(300, msec);
  intake.stopFullIntake();
  wait(400, msec);
  sloper.off();
  blocker.off();
  wait(300, msec);

  // Drive in front of the loader
  driveParams = driveParams50_in();
  chassisReference->driveToPoint(Pose<double>(-46.67, 46.9, 0), driveParams, turnParams10_deg(), {});

  // Turn toward loader entrance point
  turnParams = turnParams45_deg();
  chassisReference->turnTo(Pose<double>(-70, 46.9, -360), turnParams, {});

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  driveParams = driveParams50_in();
  chassisReference->driveToPoint(Pose<double>(-70, 46.9, 180), driveParams, turnParams10_deg(), {});

  // Line up to long goal
  turnParams = turnParams10_deg();
  driveParams = driveParams50_in();
  chassisReference->turnTo(Pose<double>(-25, 49.3, -360), turnParams, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-25, 49.3, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  sloper.on();
  wait(1200, msec);
  // chassisReference->odometry->setPosition(-28.5, 47, chassisReference->getAbsoluteHeading().angle);
  // chassisReference->Inertial.setRotation(chassisReference->getAbsoluteHeading().angle, deg);
  sloper.off();

  // Back away from goal
  driveParams = driveParams10_in();
  chassisReference->driveToPoint(Pose<double>(-37, 47, 0), driveParams, turnParams10_deg(), {});

  // Reposition to align wing
  turnParams = turnParams90_deg();
  driveParams = driveParams10_in();
  chassisReference->turnTo(Pose<double>(-37, 36.9, -360), turnParams, {});
  // chassisReference->driveDistance(11, 180, {}, {}, {});
  chassisReference->driveToPoint(Pose<double>(-37, 36.9, 0), driveParams, turnParams10_deg(), {});

  // Push blocks in goal
  turnParams = turnParams90_deg();
  driveParams = driveParams30_in();
  chassisReference->turnTo(Pose<double>(-10, 38.3, -360), turnParams, {});
  // chassisReference->driveDistance(30, 90, {}, {}, {});
  chassisReference->driveToPoint(Pose<double>(-10, 38.3, 0), driveParams, turnParams10_deg(), {});

  wait(2000, msec);
}