#include "autons.h"
#include "vex.h"
#include "types/params.h"

void Autons::solo()
{
  chassisReference->odometry->setPosition(-45, 0, 180);
  chassisReference->odometry->startPositionTrackThread(true);

  cout << DriveParams().driveSettleTime << endl;
  cout << Config::kSidewaysTrackerDistance << endl;

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();

  // Push our alliance
  chassisReference->driveToPoint(Pose<double>(-45, -5, 0), {.driveTimeout = 700}, turnParams10_deg(), {});

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 47, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});

  // Ram into 1st loader
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(-68, 47, -360), {.turnTimeout = 700}, {});
  chassisReference->driveWithVoltage(12, 200, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 650, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Go up to long goal
  chassisReference->turnTo(Pose<double>(-26, 47, -360), {.turnTimeout = 200}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-26, 47, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score
  blocker.on();
  wait(800, msec);

  cout << "X: " << chassisReference->odometry->getPose().position.x << endl;
  cout << "Y: " << chassisReference->odometry->getPose().position.y << endl;
  cout << "Angle: " << chassisReference->odometry->getPose().orientation.angle << endl;

  // Turn by clipping onto the goal
  chassisReference->turnTo(Pose<double>(-23, 23, -360), {.turnTimeout = 1000}, {});

  // Eat middle blocks
  willyNilly.delayToggle(800);
  chassisReference->driveToPoint(Pose<double>(-23, -23, 0), {.driveSettleError = 1, .driveSettleTime = 100, .driveTimeout = 1100}, {}, {});

  // Drive across the field
  chassisReference->turnTo(Pose<double>(-47, -47, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), {.driveSettleError = 1, .driveSettleTime = 100, .driveTimeout = 2000}, {}, {});

  // Ram into 2nd loader
  chassisReference->turnTo(Pose<double>(-68, -47, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, 48, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 300, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 650, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-24, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, -47, 0), {.driveTimeout = 1200}, {}, {.forwards = false});
  willyNilly.off();

  // Score and NOT chill >:(
  blocker.on();
  wait(1000, msec);

  // Turn by clipping onto the goal
  chassisReference->turnTo(Pose<double>(-23, -23, -360), {.turnTimeout = 1000}, {});

  // Eat middle blocks
  willyNilly.delayToggle(800);
  chassisReference->driveToPoint(Pose<double>(-23, -23, 0), {.driveSettleError = 1, .driveSettleTime = 100, .driveTimeout = 1100}, {}, {});

  // Go up to low goal
  willyNilly.delayToggle(100);
  chassisReference->turnTo(Pose<double>(-11, -11, -360), {}, {});
  intake.stopFullIntake();
  IntakeFront.spin(vex::directionType::fwd, 12, volt);
  chassisReference->driveToPoint(Pose<double>(-11, -11, 0), {.driveTimeout = 1000}, {}, {});
  razer.on();
  willyNilly.off();

  // Score in low goal
  intake.spinFullIntake(vex::directionType::rev, 12);
  wait(200, msec);
  IntakeFront.spin(vex::directionType::rev, 7, volt);

  wait(10000, msec);
}