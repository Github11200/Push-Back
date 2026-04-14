#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::midGoals()
{
  chassisReference->odometry->setPosition(-46.5, -14, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  IntakeRear.stop();
  IntakeMiddle.stop();
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  sloper.on();

  // Drive to the middle blocks
  finger.on();
  willyNilly.delayToggle(800);
  chassisReference->driveToPoint(Pose<double>(-19, -22, 0), {}, turnParams10_deg(), {});
  finger.off();
  wait(200, msec);

  // Drive towards and score in low goal
  willyNilly.off();
  cout << "current x: " << chassisReference->odometry->getPose().position.x << endl;
  cout << "current y: " << chassisReference->odometry->getPose().position.y << endl;
  cout << "current theta: " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->turnTo(Pose<double>(-2, -2, -360), {}, {});
  return;
  chassisReference->driveToPoint(Pose<double>(-2, -2, 0), {}, turnParams10_deg(), {});
  razer.on();
  intake.spinFullIntake(vex::directionType::rev, 12);
  IntakeFront.spin(vex::directionType::rev, 7, volt);
  wait(650, msec);
  razer.off();
  intake.spinFullIntake(vex::directionType::fwd, 12);

  // Drive back from the low goal
  chassisReference->driveToPoint(Pose<double>(-19, -22, 0), {.driveTimeout = 1100}, turnParams10_deg(), {.forwards = false});

  // Drive to the other three stack
  chassisReference->turnTo(Pose<double>(-22, 22, -360), {.turnTimeout = 650}, {});
  chassisReference->driveToPoint(Pose<double>(-22, 22, 0), {.driveTimeout = 1500}, turnParams10_deg(), {});

  // Drive into the mid goal
  chassisReference->turnTo(Pose<double>(-11, 11, -360), {.turnTimeout = 650}, {.forwards = false});
  sloper.off();
  chassisReference->driveToPoint(Pose<double>(-11, 11, 0), {.driveTimeout = 1500}, turnParams10_deg(), {});

  // Score in the mid goal
  blocker.on();
  IntakeRear.spin(vex::directionType::fwd, 6, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);

  wait(10, sec);
}