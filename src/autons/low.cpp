#include "autons.h"
#include "vex.h"

void Autons::low()
{
  // Set starting coordinates
  chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
  chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);

  intake.spinFullIntake(vex::directionType::fwd);

  // Drive to the middle blocks (absolute field coordinate)
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(-22.111, -21.111, -360), {.turnKp = 0.36}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(-22.111, -21.111, 0), {.driveMaxVoltage = 5}, {}, {});

  // Turn to face the center goal location (turn to point (14, -14))
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, 35), {.turnKp = 0.3}, {}); // Angle was -125 in high.cpp
  chassisReference->odometry->resumePositionTrackThread();
  intake.stopFullIntake();

  chassisReference->driveToPoint(Pose<double>(-11, -12, 0), {.driveTimeout = 1000}, {}, {});

  intake.spinFullIntake(vex::directionType::rev);
  wait(700, msec);
  intake.stopFullIntake();

  // Drive backwards in front of the loader since we're facing the middle goal rn
  chassisReference->driveToPoint(Pose<double>(-47.67, -46.67, 0), {.driveTimeout = 1800}, {}, {.forwards = false});

  // Turn toward loader entrance point
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, 180), {.turnKp = 0.32}, {});
  chassisReference->odometry->resumePositionTrackThread();

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-47.67, -62.748, 180), {.driveTimeout = 1000}, {.turnMaxVoltage = 0}, {});
  wait(2000, msec); // Eat it all up

  // Line up to long goal
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, 180), {.turnKp = 0.3}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(-45.67, -20.566, 0), {.driveTimeout = 1200}, {}, {.forwards = false});

  // Pull this thingy us
  willyNilly.off();

  // Score and chill :)
  sloper.on();
  wait(10000, msec);
}