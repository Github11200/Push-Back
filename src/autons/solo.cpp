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
  // chassisReference->driveWithVoltage(12, 300, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveDistance(5, chassisReference->getAbsoluteHeading().angle, {.driveTimeout = 500}, {}, {});

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 41, 0), {.driveTimeout = 1100, .driveSettleTime = 0}, turnParams10_deg(), {.forwards = false});

  // Ram into 1st loader
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(-68, 46, -360), {.turnTimeout = 700}, {});
  chassisReference->driveWithVoltage(12, 200, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(6, 400, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Go up to long goal
  chassisReference->turnTo(Pose<double>(-24, 47.5, -360), {.turnTimeout = 200}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, 47.5, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false, .doNotEditTurnConstants = true});
  willyNilly.off();

  // Score
  blocker.on();
  wait(750, msec);

  // Turn by clipping onto the goal
  chassisReference->turnTo(Pose<double>(-22, 23, -360), {.turnTimeout = 900}, {});
  blocker.off();

  // Eat middle blocks and drive across the field
  willyNilly.delayToggle(1050);
  chassisReference->driveToPoint(Pose<double>(-21, -23, 0), {.driveTimeout = 1500, .driveSettleTime = 0, .driveSettleError = 4, .driveMaxVoltage = 10}, {}, {});

  // Drive in front of the 2nd loader
  chassisReference->driveToPoint(Pose<double>(-49, -47, 0), {.driveTimeout = 1100, .driveSettleTime = 200}, {}, {});

  // Ram into 2nd loader
  chassisReference->turnTo(Pose<double>(-68, -47.5, -360), {.turnSettleTime = 0, .turnTimeout = 700}, {});
  chassisReference->driveWithVoltage(6.5, 500, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-24, -48, -360), {.turnTimeout = 300}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, -48, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score and NOT chill >:(
  blocker.on();
  wait(675, msec);
  IntakeRear.spin(vex::directionType::rev, 12, volt);
  IntakeMiddle.spin(vex::directionType::rev, 12, volt);

  // Turn by clipping onto the goal
  chassisReference->turnTo(Pose<double>(-22, -27, -360), {.turnTimeout = 1000}, {});

  // Eat middle blocks
  chassisReference->driveToPoint(Pose<double>(-23, -27, 0), {.driveTimeout = 1100, .driveSettleTime = 0}, turnParams10_deg(), {.doNotEditTurnConstants = true});

  // Go up to low goal
  chassisReference->turnTo(Pose<double>(-9, -9, -360), {.turnSettleTime = 0, .turnSettleError = 3}, {});
  Brain.Timer.event([](void *)
                    { IntakeFront.spin(vex::directionType::rev, 5, volt); wait(100, msec); IntakeFront.stop(vex::brakeType::coast); }, 150);
  chassisReference->driveToPoint(Pose<double>(-9, -9, 0), {.driveTimeout = 1000}, turnParams10_deg(), {.doNotEditTurnConstants = true});
  razer.on();
  willyNilly.off();

  // Score in low goal
  intake.spinFullIntake(vex::directionType::rev, 12);
  wait(200, msec);
  IntakeFront.spin(vex::directionType::rev, 4, volt);

  wait(10000, sec);
}