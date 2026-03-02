#include "autons.h"
#include "vex.h"
#include "types/params.h"

void Autons::solo()
{
  chassisReference->odometry->setPosition(-46.5, -16.5, 180);
  chassisReference->odometry->startPositionTrackThread(false);

  cout << DriveParams().driveSettleTime << endl;

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  willyNilly.on();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, -44, 0), {.driveTimeout = 700}, turnParams10_deg(), {});

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, -45.5, -360), {.turnTimeout = 700}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 300, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 650, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-27, -47, -360), {.turnTimeout = 200}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score
  blocker.on();
  wait(800, msec);

  // Back away from 1st long goal
  // chassisReference->driveToPoint(Pose<double>(-37, -47, 0), {.driveSettleError = 3, .driveSettleTime = 0}, {}, {});

  // chassisReference->turnTo(Pose<double>(-10, -10, -360), {.turnSettleError = 5, .turnSettleTime = 0}, {});
  // chassisReference->driveToPoint(Pose<double>(-18.5, -18.5, 0), {}, {}, {});

  // chassisReference->driveToPose(Pose<double>(-18, -18, 45), {.driveSettleError = 0.1}, {.turnSettleError = 0.1}, {}, 0.4, 0, 0);

  willyNilly.delayToggle(800);
  chassisReference->driveToPoint(Pose<double>(-25, -21.5, 0), {.driveSettleError = 1, .driveSettleTime = 100}, {}, {});

  blocker.off();

  // Go up to low goal
  willyNilly.delayToggle(100);
  chassisReference->turnTo(Pose<double>(-11, -10, -360), {}, {});
  intake.stopFullIntake();
  IntakeFront.spin(vex::directionType::fwd, 12, volt);
  chassisReference->driveToPoint(Pose<double>(-11, -10, 0), {.driveTimeout = 1000}, {}, {});
  razer.on();

  // // This fixes the angle before outtaking
  // chassisReference->turnTo(Pose<double>(-23, -23, -360), {.turnTimeout = 100}, {.forwards = false});

  // Score in low goal
  intake.spinFullIntake(vex::directionType::rev, 12);
  wait(200, msec);
  IntakeFront.spin(vex::directionType::rev, 7, volt);
  wait(1000, msec);
  razer.off();

  finger.on();

  // Back up from low goal
  chassisReference->driveToPoint(Pose<double>(-23, -23, 0), {.driveTimeout = 400}, {}, {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd, 12);

  // Eat other middle blocks
  chassisReference->turnTo(Pose<double>(-21, 18, -360), {.turnTimeout = 300}, {});
  willyNilly.delayToggle(900);
  // finger.on();
  chassisReference->driveToPoint(Pose<double>(-21, 18, 0), {.driveMinVoltage = 12, .driveSettleError = 10, .driveSettleTime = 0}, {}, {});

  // Go towards loader entrance point
  // willyNilly.on();
  // chassisReference->turnTo(Pose<double>(-47, 47, -360), {.turnTimeout = 600}, {});
  // chassisReference->driveToPoint(Pose<double>(-47, 47, 0), {.driveTimeout = 800, .driveSlew = 12}, {}, {});

  chassisReference->driveToPose(Pose<double>(-47, 45.5, 270), {.driveSettleError = 0.1, .driveTimeout = 1400}, {.turnSettleError = 0.1, .turnTimeout = 1300}, {}, 0.28); //.turnSettleError = 0.3, {}, 0.8, 0, 2.4

  // Ram into 2nd loader
  chassisReference->turnTo(Pose<double>(-68, 46.5, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, 48, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 350, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 500, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-24, 46.5, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, 46.5, 0), {.driveTimeout = 1200}, {}, {.forwards = false});
  willyNilly.off();

  // Score and NOT chill >:(
  blocker.on();
  wait(1000, msec);

  finger.off();
  chassisReference->driveToPoint(Pose<double>(-38, 37, 0), {.driveSettleError = 3, .driveSettleTime = 0}, {}, {});
  blocker.off();
  chassisReference->turnTo(Pose<double>(-15, 36, -360), {.turnSettleError = 5, .turnSettleTime = 0}, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-15, 36.5, 0), {}, {}, {.forwards = false});
  // chassisReference->driveDistance(30, 270, driveParams30_in(), turnParams10_deg(), {.forwards = false});

  // Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  // Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);
}