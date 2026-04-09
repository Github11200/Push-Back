#include "autons.h"
#include "vex.h"
#include "types/params.h"

void Autons::solo()
{
  chassisReference->odometry->setPosition(-45, 0, 180);
  chassisReference->odometry->startPositionTrackThread(false);

  cout << DriveParams().driveSettleTime << endl;
  cout << Config::kSidewaysTrackerDistance << endl;

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();

  // Push our alliance
  chassisReference->driveWithVoltage(12, 300, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  // chassisReference->driveToPoint(Pose<double>(-45, -3, 0), {.driveTimeout = 700}, turnParams10_deg(), {});

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 42, 0), {.driveTimeout = 1200, .driveSettleTime = 0}, turnParams10_deg(), {.forwards = false, .doNotEditTurnConstants = true});

  // Ram into 1st loader
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(-68, 47.5, -360), {.turnTimeout = 700}, {});
  chassisReference->driveWithVoltage(12, 200, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 400, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Go up to long goal
  chassisReference->turnTo(Pose<double>(-24, 47.5, -360), {.turnTimeout = 200}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, 47.5, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false, .doNotEditTurnConstants = true});
  willyNilly.off();

  // Score
  blocker.on();
  wait(700, msec);
  blocker.off();

  cout << "X: " << chassisReference->odometry->getPose().position.x << endl;
  cout << "Y: " << chassisReference->odometry->getPose().position.y << endl;
  cout << "Angle: " << chassisReference->odometry->getPose().orientation.angle << endl;

  // Turn by clipping onto the goal
  chassisReference->turnTo(Pose<double>(-22, 23, -360), {.turnTimeout = 850}, {});

  // Eat middle blocks and drive across the field
  willyNilly.delayToggle(1300);
  chassisReference->driveToPoint(Pose<double>(-20, -23, 0), {.driveTimeout = 1500, .driveSettleTime = 0, .driveSettleError = 4, .driveMaxVoltage = 10}, {}, {});

  // Drive in front of the 2nd loader
  // chassisReference->turnTo(Pose<double>(-47, -47, -360), {.turnSettleError = 5, .turnSettleTime = 0}, {});
  chassisReference->driveToPoint(Pose<double>(-47, -46, 0), {.driveTimeout = 1300, .driveSettleTime = 0}, {}, {});
  // willyNilly.on();
  // willyNilly.on();
  // willyNilly.on();

  // Ram into 2nd loader
  chassisReference->turnTo(Pose<double>(-68, -46, -360), {.turnSettleTime = 0}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, 48, 0), driveParams, turnParams10_deg(), {});
  // chassisReference->driveWithVoltage(12, 100, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 650, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-24, -47.5, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, -47.5, 0), {.driveTimeout = 1200}, {}, {.forwards = false});
  willyNilly.off();

  // Score and NOT chill >:(
  blocker.on();
  wait(650, msec);
  IntakeRear.spin(vex::directionType::rev, 12, volt);
  IntakeMiddle.spin(vex::directionType::rev, 12, volt);

  // Turn by clipping onto the goal
  chassisReference->turnTo(Pose<double>(-22, -23, -360), {.turnTimeout = 1000}, {});

  // Eat middle blocks
  chassisReference->driveToPoint(Pose<double>(-23, -23, 0), {.driveTimeout = 1100, .driveSettleTime = 0}, {}, {});

  // Go up to low goal
  chassisReference->turnTo(Pose<double>(-9, -9, -360), {.turnSettleTime = 0, .turnSettleError = 3}, {});
  Brain.Timer.event([](void *)
                    { IntakeFront.spin(vex::directionType::rev, 6, volt); }, 200);
  chassisReference->driveToPoint(Pose<double>(-9, -9, 0), {.driveTimeout = 1000}, {}, {});
  razer.on();
  willyNilly.off();

  // Score in low goal
  intake.spinFullIntake(vex::directionType::rev, 12);
  wait(200, msec);
  IntakeFront.spin(vex::directionType::rev, 6.5, volt);

  wait(10000, sec);
}