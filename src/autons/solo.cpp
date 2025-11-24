#include "autons.h"
#include "vex.h"

void Autons::solo()
{
  // Set starting coordinates
  chassisReference->odometry->setPosition(-46, 15, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  // chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
  // chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);

  intake.spinFullIntake(vex::directionType::fwd);

  // Drive to the middle blocks (absolute field coordinate)
  chassisReference->turnTo(Pose<double>(-20.111, 23, -360), {.turnTimeout = 200}, {});
  chassisReference->driveToPoint(Pose<double>(-20.111, 23, 0), {.driveMaxVoltage = 10, .driveTimeout = 1300}, {}, {});

  // Turn to face the center goal location (turn to point (14, -14))
  chassisReference->turnTo(Pose<double>(0, 0, -33), {.turnTimeout = 400}, {});
  intake.stopFullIntake();

  chassisReference->driveToPoint(Pose<double>(-11.9, 12, 0), {.driveTimeout = 800}, {}, {.forwards = false});

  sloper.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(200, msec);
  intake.stopFullIntake();
  wait(400, msec);
  sloper.off();
  wait(300, msec);

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-46.67, 45.5, 0), {.driveTimeout = 1400}, {}, {});

  // Turn toward loader entrance point
  chassisReference->turnTo(Pose<double>(0, 0, -90), {.turnTimeout = 200}, {});

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-80, 45.5, 180), {.driveMaxVoltage = 6, .driveTimeout = 1100}, {}, {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(0, 0, -90), {}, {});
  chassisReference->driveToPoint(Pose<double>(-25, 45.5, 0), {.driveTimeout = 700}, {}, {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and chill :)
  sloper.on();
  wait(2000, msec);

  // Back away from 1st long goal
  chassisReference->driveToPoint(Pose<double>(-37, 46.67, 0), {.driveTimeout = 500, .driveSlew = 12, .driveSettleError = 6}, {}, {});
  sloper.off();
  finger.on();

  // Turn to group of blocks in middle
  chassisReference->turnTo(Pose<double>(0, 0, 167), {.turnTimeout = 300}, {});
  chassisReference->driveToPoint(Pose<double>(-21, -27.2, 0), {.driveTimeout = 2500, .driveSettleError = 18, .driveSlew = 12}, {}, {});

  chassisReference->turnTo(Pose<double>(0, 0, 233), {.turnTimeout = 100}, {});

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-46.67, -50.67, 0), {.driveTimeout = 1400, .driveSettleError = 4, .driveSlew = 12}, {}, {});

  // Turn toward loader entrance point
  chassisReference->turnTo(Pose<double>(0, 0, -90), {.turnTimeout = 150}, {});

  // Slap down the willy nilly
  willyNilly.on();

  // Ram into loader
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-80, -50.67, 0), {.driveMaxVoltage = 6, .driveTimeout = 1100, .driveSlew = 12}, {}, {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(0, 0, -90), {.turnTimeout = 100}, {});
  chassisReference->driveToPoint(Pose<double>(-25, -50.67, 0), {.driveTimeout = 1000, .driveSlew = 12}, {}, {.forwards = false});

  // Pull this thingy up
  willyNilly.off();

  // Score and chill :)
  sloper.on();
  wait(10000, msec);
}