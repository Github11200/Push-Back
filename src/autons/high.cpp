#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::high()
{
  chassisReference->forwardTrackerInchesToDegreesRatio = ((M_PI * 2.03) / 360.0);

  // Set starting coordinates
  chassisReference->odometry->setPosition(-46, 15, 90);
  Inertial.setRotation(90, deg);
  chassisReference->odometry->startPositionTrackThread(false);

  // chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
  // chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);

  intake.spinFullIntake(vex::directionType::fwd);

  // Drive to the middle blocks (absolute field coordinate)
  chassisReference->turnTo(Pose<double>(-20.111, 23, -360), {.turnTimeout = 100}, {});
  chassisReference->driveToPoint(Pose<double>(-20.111, 23, 0), {.driveMaxVoltage = 4.5, .driveTimeout = 1300}, {.turnMaxVoltage = 1}, {});
  willyNilly.on();
  wait(100, msec);

  // Turn to face the center goal location (turn to point (14, -14))
  chassisReference->turnTo(Pose<double>(-12.2, 12, -360), {.turnTimeout = 900, .turnSettleError = 1}, {.forwards = false});
  intake.stopFullIntake();

  chassisReference->driveToPoint(Pose<double>(-12.2, 12, 0), {.driveTimeout = 800}, {.turnMaxVoltage = 0.5}, {.forwards = false});

  sloper.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(300, msec);
  intake.stopFullIntake();
  wait(400, msec);
  sloper.off();
  wait(300, msec);

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-46.67, 46.9, 0), {.driveTimeout = 1300}, {}, {});

  // Turn toward loader entrance point
  chassisReference->turnTo(Pose<double>(-70, 46.9, -360), {}, {});

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-70, 46.9, 180), {.driveMaxVoltage = 6, .driveTimeout = 1500}, {}, {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-25, 49.3, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-25, 49.3, 0), {.driveTimeout = 1100}, {}, {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and NOT CHILL >:(
  sloper.on();
  wait(1200, msec);
  // chassisReference->odometry->setPosition(-28.5, 47, chassisReference->getAbsoluteHeading().angle);
  // chassisReference->Inertial.setRotation(chassisReference->getAbsoluteHeading().angle, deg);
  sloper.off();

  // Back away from goal
  chassisReference->driveToPoint(Pose<double>(-37, 47, 0), {.driveTimeout = 1000}, {}, {});

  // Reposition to align wing
  chassisReference->turnTo(Pose<double>(-37, 36.9, -360), {.turnTimeout = 900}, {});
  // chassisReference->driveDistance(11, 180, {}, {}, {});
  chassisReference->driveToPoint(Pose<double>(-37, 36.9, 0), {.driveTimeout = 1000}, {.turnKp = 0, .turnKd = 0, .turnKi = 0}, {});

  // Push blocks in goal
  chassisReference->turnTo(Pose<double>(-10, 38.3, -360), {}, {});
  // chassisReference->driveDistance(30, 90, {}, {}, {});
  chassisReference->driveToPoint(Pose<double>(-10, 38.3, 0), {.driveTimeout = 4000}, {.turnKp = 0, .turnKd = 0, .turnKi = 0}, {});

  wait(2000, msec);
}