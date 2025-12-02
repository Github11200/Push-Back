#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::high()
{
  // Set starting coordinates
  chassisReference->odometry->setPosition(-46, 15, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  // chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
  // chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);

  intake.spinFullIntake(vex::directionType::fwd);

  // Drive to the middle blocks (absolute field coordinate)
  chassisReference->turnTo(Pose<double>(-20.111, 23, -360), {}, {});

  // TODO: this stops the whole program for some reason
  // // Slap down the willy nilly
  // willyNilly.delayToggle(3000);

  chassisReference->driveToPoint(Pose<double>(-20.111, 23, 0), {.driveMaxVoltage = 6}, {}, {});

  // Turn to face the center goal location (turn to point (14, -14))
  chassisReference->turnTo(Pose<double>(-11.9, 12, -360), {}, {.forwards = false});
  intake.stopFullIntake();

  chassisReference->driveToPoint(Pose<double>(-11.9, 12, 0), {.driveTimeout = 600}, {}, {.forwards = false});

  sloper.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(200, msec);
  intake.stopFullIntake();
  wait(400, msec);
  sloper.off();
  wait(300, msec);

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-46.67, 47, 0), {.driveTimeout = 1300}, {}, {});

  // Turn toward loader entrance point
  chassisReference->turnTo(Pose<double>(0, 0, -90), {}, {});

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-70, 47, 180), {.driveMaxVoltage = 5, .driveTimeout = 1500}, {}, {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(0, 0, -90), {}, {});
  chassisReference->driveToPoint(Pose<double>(-25, 47.2, 0), {.driveTimeout = 1100}, {}, {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  sloper.on();
  wait(1200, msec);
  chassisReference->odometry->setPosition(-28.5, 47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // Back away from goal
  chassisReference->driveToPoint(Pose<double>(-37, 47, 0), {.driveTimeout = 1000}, {}, {});
  chassisReference->odometry->setPosition(-37, 47, chassisReference->getAbsoluteHeading().angle);

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(0, 0, 180), {}, {});
  // chassisReference->driveDistance(11, 180, {}, {}, {});
  chassisReference->driveToPoint(Pose<double>(-37, 33.5, 0), {.driveTimeout = 1100}, {.turnKp = 0, .turnKd = 0, .turnKi = 0}, {});
  chassisReference->odometry->setPosition(-37, 33.5, chassisReference->getAbsoluteHeading().angle);

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-8, 35, -360), {}, {});
  // chassisReference->driveDistance(30, 90, {}, {}, {});
  chassisReference->driveToPoint(Pose<double>(-8, 35, 0), {.driveTimeout = 4000}, {.turnKp = 0, .turnKd = 0, .turnKi = 0}, {});

  wait(2000, msec);
}