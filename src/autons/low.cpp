#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::low()
{
  chassisReference->odometry->setPosition(-46.5, -16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  IntakeRear.stop();
  IntakeMiddle.spin(vex::directionType::fwd, 4, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  sloper.on();

  willyNilly.delayToggle(1050);

  // Drive to the middle blocks
  chassisReference->turnTo(Pose<double>(-22, -23, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-22, -23, 0), {.driveMaxVoltage = 8}, turnParams10_deg(), {});
  wait(1, sec);

  // // Intake the blocks under the long goal
  // willyNilly.off();
  // willyNilly.delayToggle(1000);
  // chassisReference->turnTo(Pose<double>(-8.5, 41, 0), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-8.5, 41, 0), {}, turnParams10_deg(), {});

  // // Drive back
  // chassisReference->turnTo(Pose<double>(-23, 23, -360), {}, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-23, 23, 0), {}, turnParams10_deg(), {.forwards = false});

  // Drive towards and score in low goal
  // willyNilly.off();
  // chassisReference->turnTo(Pose<double>(-9, -10.5, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-9, -10.5, 0), {.driveTimeout = 1100}, turnParams10_deg(), {});
  // razer.on();
  // intake.spinFullIntake(vex::directionType::rev, 12);
  // IntakeFront.spin(vex::directionType::rev, 7, volt);
  // wait(1300, msec);
  // razer.off();
  // intake.spinFullIntake(vex::directionType::fwd, 12);

  // Drive (in reverse) in front of the loader
  chassisReference->turnTo(Pose<double>(-47, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), {.driveTimeout = 2000}, turnParams10_deg(), {.forwards = false});
  willyNilly.on();

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, -47, -360), {.turnTimeout = 700}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, -47, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 100, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 750, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-27, -48, -360), {.turnTimeout = 200}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -48, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  blocker.on();
  wait(1300, msec);
  intake.stopFullIntake();

  // // Back away from goal
  // chassisReference->driveToPoint(Pose<double>(-37, -47, 0), {.driveTimeout = 600}, turnParams10_deg(), {});

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(-40, -61.5, -360), {.turnTimeout = 500}, {});
  chassisReference->driveToPoint(Pose<double>(-40, -61.5, 0), {.driveTimeout = 900}, turnParams10_deg(), {});
  blocker.off();

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-14.8, -60, -360), {.turnTimeout = 550}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-14.8, -60, 0), {.driveMaxVoltage = 12, .driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);

  wait(2000, msec);
}