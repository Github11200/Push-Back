#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::high()
{
  // Set starting coordinates
  chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
  chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);

  intake.spinFullIntake(vex::directionType::fwd);

  // Drive to the middle blocks (absolute field coordinate)
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(-22.111, -22.111, -360), {.turnKp = 0.36}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(-22.111, -22.111, 0), {}, {}, {});

  // Turn to face the center goal location (turn to point (14, -14))
  // Vector2D<double> previousPosition = chassisReference->odometry->getPose();
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, -135), {}, {});
  chassisReference->odometry->resumePositionTrackThread();

  chassisReference->driveToPoint(Pose<double>(-14, -14, 0), {}, {}, {.forwards = false});

  blocker.off();
  wait(400, msec);
  blocker.on();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-46.67, -46.67, 0), {}, {}, {});

  // Turn toward loader entrance point
  chassisReference->turnTo(Pose<double>(0, 0, 180), {}, {});

  // Slap down the willy nilly
  willyNilly.on();

  return;

  // Ram into loader
  chassisReference->driveToPoint(Pose<double>(-46.67, -58.748, 180), {}, {}, {});
  wait(1000, msec); // Eat it all up

  // Pull this thingy up
  willyNilly.off();

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-46.67, -30.566, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-46.67, -30.566, 0), {}, {}, {.forwards = false});

  // (score_long_goal omitted)
  sloper.on();
  wait(100, msec);
  blocker.off();
}