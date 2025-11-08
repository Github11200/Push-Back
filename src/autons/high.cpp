#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::high()
{
  int reversed = 1;
  if (side == Side::RIGHT)
    reversed = -1;

  // Set starting coordinates
  chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
  chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);

  intake.spinFullIntake(vex::directionType::fwd);

  // Drive to the middle blocks (absolute field coordinate)
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(-22.111 * reversed, -20.111, -360), {.turnKp = 0.42}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(-22.111 * reversed, -20.111, 0), {.driveMaxVoltage = 7.5}, {}, {});

  // Turn to face the center goal location (turn to point (14, -14))
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, -125 * reversed), {.turnKp = 0.3}, {});
  chassisReference->odometry->resumePositionTrackThread();
  intake.stopFullIntake();

  chassisReference->driveToPoint(Pose<double>(-10 * reversed, -12, 0), {.driveTimeout = 550}, {}, {.forwards = false});

  sloper.on();
  wait(600, msec);
  intake.spinFullIntake(vex::directionType::fwd);
  wait(400, msec);
  intake.stopFullIntake();
  sloper.off();
  wait(300, msec);

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47.67 * reversed, -43.67, 0), {.driveTimeout = 1300}, {}, {});

  // Turn toward loader entrance point
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, 180), {.turnKp = 0.32}, {});
  chassisReference->odometry->resumePositionTrackThread();

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-47.67 * reversed, -72.748, 180), {.driveTimeout = 800}, {}, {});
  // chassisReference->driveToPoint(Pose<double>(-47.67, -72.748, 180), {.driveTimeout = 2000, .driveMaxVoltage = 3}, {}, {});
  wait(1000, msec); // Eat it all up

  // Line up to long goal
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, 180), {.turnKp = 0.3}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(-46.67 * reversed, -20.566, 0), {.driveTimeout = 1200}, {}, {.forwards = false});

  // Pull this thingy us
  willyNilly.off();

  // Score and chill :)
  sloper.on();
  wait(10000, msec);
}