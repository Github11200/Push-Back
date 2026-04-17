#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::midGoals()
{
  chassisReference->odometry->setPosition(-45, 0, 180);
  chassisReference->odometry->startPositionTrackThread(false);

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();
  willyNilly.on();

  // Drive in front of the dispenser
  chassisReference->driveToPoint(Pose<double>(-47, -43, 0), {.driveTimeout = 1100, .driveSettleTime = 0}, turnParams10_deg(), {});

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, -47, -360), {.turnTimeout = 700}, {});
  chassisReference->driveWithVoltage(12, 200, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(6, 625, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Back up a bit
  chassisReference->driveToPoint(Pose<double>(-41, -47, 0), {.driveTimeout = 1100, .driveSettleTime = 0}, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Turn towards the low goal and score in it
  chassisReference->turnTo(Pose<double>(-11, -11, -360), {}, {});
  Brain.Timer.event([]()
                    { IntakeFront.spin(vex::directionType::rev, 6, vex::voltageUnits::volt); }, 1100);
  chassisReference->driveToPoint(Pose<double>(-11, -11, 0), {.driveTimeout = 1500}, turnParams10_deg(), {});

  // Outtake there
  intake.spinFullIntake(vex::directionType::rev);
  razer.on();
  IntakeFront.spin(vex::directionType::rev, 5, vex::voltageUnits::volt);
  wait(900, msec);
  intake.spinFullIntake(vex::directionType::fwd);
  razer.off();

  // Drive back from the low goal
  chassisReference->driveToPoint(Pose<double>(-19, -22, 0), {.driveTimeout = 1000, .driveSettleTime = 0}, turnParams10_deg(), {.forwards = false});

  // Drive to the other three stack
  chassisReference->turnTo(Pose<double>(-22, 24, -360), {.turnTimeout = 650, .turnSettleTime = 50}, {});
  chassisReference->driveToPoint(Pose<double>(-22, 24, 0), {.driveTimeout = 1500}, turnParams10_deg(), {});

  // Drive into the mid goal
  chassisReference->turnTo(Pose<double>(-8.5, 8.5, -360), {.turnTimeout = 650, .turnSettleTime = 50, .turnSettleError = 5}, {.forwards = false});
  sloper.off();
  chassisReference->driveToPoint(Pose<double>(-8.5, 8.5, 0), {.driveTimeout = 1300}, turnParams10_deg(), {.forwards = false});

  // Score in the mid goal
  blocker.on();
  IntakeRear.spin(vex::directionType::fwd, 4, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(700, msec);
  blocker.off();
  intake.stopFullIntake();

  sloper.on();
  chassisReference->driveDistance(5, chassisReference->getAbsoluteHeading().angle, {.driveTimeout = 800}, turnParams10_deg(), {});

  double currentTime = 0;
  while (currentTime < 14)
  {
    currentTime = Brain.Timer.time(seconds);
    wait(100, msec);
  }

  cout << "killed the mid goal" << endl;
  chassisReference->driveWithVoltage(-4, 2000, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {.forwards = false});

  wait(10, sec);
}