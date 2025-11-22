#include "autons.h"
#include "vex.h"

void Autons::low()
{
  // Set starting coordinates
  chassisReference->odometry->setPosition(-46, -15, 90);
  // chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
  // chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);

  intake.spinFullIntake(vex::directionType::fwd);

  // Drive to the middle blocks (absolute field coordinate)
  chassisReference->turnTo(Pose<double>(-20.111, -22.111, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-20.111, -22.111, 0), {.driveMaxVoltage = 8}, {}, {});

  // Turn to face the center goal location (turn to point (14, -14))
  chassisReference->turnTo(Pose<double>(0, 0, -135), {}, {});
  intake.stopFullIntake();

  chassisReference->driveToPoint(Pose<double>(-12, -12, 0), {.driveTimeout = 550}, {}, {.forwards = false});

  intake.spinFullIntake(vex::directionType::rev);
  wait(1000, msec);
  intake.stopFullIntake();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-46.67, -46.67, 0), {.driveTimeout = 1300}, {}, {});

  // Turn toward loader entrance point
  chassisReference->turnTo(Pose<double>(0, 0, -90), {}, {});

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-70, -46.67, 180), {.driveMaxVoltage = 7, .driveTimeout = 1100}, {}, {});
  wait(1100, msec); // Eat it all up

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(0, 0, -90), {}, {});
  chassisReference->driveToPoint(Pose<double>(-25, -46.67, 0), {.driveTimeout = 1200}, {}, {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and chill :)
  sloper.on();
  wait(10000, msec);
}