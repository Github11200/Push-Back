#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

// TODO: Move the coordinates when it's at the third goal and scoring to be further down (increase the absolute value of y)

void Autons::skills()
{
  // Set starting coordinates
  chassisReference->odometry->setPosition(-46.5, -16.5, 180);
  chassisReference->odometry->startPositionTrackThread(true);

  // Drive in front of the dispenser
  chassisReference->driveToPoint(Pose<double>(-46.5, -46, 0), {}, {}, {});

  // 1st dispenser
  chassisReference->turnTo(Pose<double>(0, 0, 270), {}, {});
  willyNilly.on();
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-70, -47, 0), {.driveTimeout = 3000, .driveMaxVoltage = 5}, {}, {}); // Drive into the dispenser for 3 seconds

  // Drive back
  chassisReference->driveToPoint(Pose<double>(-39, -47, 0), {.driveTimeout = 1500}, {}, {.forwards = false});

  // Drive across field to 2nd goal first
  chassisReference->turnTo(Pose<double>(0, 0, 0), {}, {});
  chassisReference->driveToPoint(Pose<double>(-39, 47, 0), {}, {}, {});

  // 2nd long goal
  chassisReference->turnTo(Pose<double>(0, 0, 270), {}, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-20, 48.5, 0), {.driveTimeout = 1500}, {}, {.forwards = false});
  chassisReference->odometry->setPosition(-28.5, 47, chassisReference->getAbsoluteHeading().angle);

  // Score
  sloper.on();
  wait(3000, msec);
  sloper.off();
  wait(300, msec);

  // Drive into the dispenser
  chassisReference->driveToPoint(Pose<double>(-70, 47, 0), {.driveTimeout = 3000, .driveMaxVoltage = 5}, {}, {});

  // 2nd long goal
  chassisReference->driveToPoint(Pose<double>(-20, 47, 0), {.driveTimeout = 2000}, {}, {.forwards = false});

  // Score
  sloper.on();
  wait(3000, msec);
  intake.stopFullIntake();
  sloper.off();
  wait(300, msec);

  // Back away from 2nd long goal
  willyNilly.off();
  chassisReference->driveToPoint(Pose<double>(-39, 47, 0), {}, {}, {});

  // Position to the alleyway
  chassisReference->turnTo(Pose<double>(0, 0, 0), {}, {});
  chassisReference->driveToPoint(Pose<double>(-39, 58, 0), {}, {}, {});
  finger.on();

  // Drive to 3rd dispenser
  chassisReference->turnTo(Pose<double>(0, 0, 90), {}, {});
  chassisReference->driveToPoint(Pose<double>(39, 58, 0), {}, {}, {});

  // Align to 3rd dispenser
  chassisReference->turnTo(Pose<double>(0, 0, 180), {}, {});
  chassisReference->driveToPoint(Pose<double>(39, 43, 0), {}, {}, {});

  // 3rd dispenser
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(0, 0, 90), {}, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(70, 43, 0), {.driveTimeout = 3000, .driveMaxVoltage = 5}, {}, {});

  // Drive back from it
  chassisReference->driveToPoint(Pose<double>(39, 43, 0), {}, {}, {.forwards = false});

  // Go to the other side of the field
  chassisReference->turnTo(Pose<double>(0, 0, 180), {}, {});
  chassisReference->driveToPoint(Pose<double>(39, -47, 0), {}, {}, {});

  // Score on the long goal
  chassisReference->turnTo(Pose<double>(0, 0, 90), {}, {});
  chassisReference->driveToPoint(Pose<double>(20, -47, 0), {}, {}, {.forwards = false});
  chassisReference->odometry->setPosition(28.5, -47, chassisReference->getAbsoluteHeading().angle);

  // Score
  sloper.on();
  wait(3000, msec);
  intake.stopFullIntake();
  sloper.off();
  wait(300, msec);

  // 4th dispenser
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(70, -47, 0), {.driveTimeout = 3000}, {}, {});

  return;

  // 1st long goal other half
  chassisReference->driveToPoint(Pose<double>(-47, -31, 0), {}, {}, {.forwards = false});

  // Score
  sloper.on();
  wait(3000, msec);
  intake.stopFullIntake();
  sloper.off();
  wait(300, msec);

  // Back away from 1st long goal other half (drive longer to line up to get center balls 45 degrees)
  chassisReference->driveToPoint(Pose<double>(-47, -47, 0), {}, {}, {});

  // Eat 1st ball stack
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(-23, -23, -360), {}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(-23, -23, 0), {}, {}, {});

  // Eat 2nd ball stack
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(23, -23, -360), {}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(23, -23, 0), {}, {}, {});

  // Align to low goal
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, 135), {}, {});
  chassisReference->odometry->resumePositionTrackThread();
  intake.stopFullIntake();
  chassisReference->driveToPoint(Pose<double>(14, -14, 0), {}, {}, {});

  // Score
  intake.spinFullIntake(vex::directionType::rev);
  wait(3000, msec);
  intake.stopFullIntake();

  // Back away from low goal
  chassisReference->driveToPoint(Pose<double>(23, -23, 0), {}, {}, {.forwards = false});

  // Eat 3rd ball stack
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(23, 23, -360), {}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(23, 23, 0), {}, {}, {});

  // Align to middle high goal
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, -135), {}, {});
  chassisReference->odometry->resumePositionTrackThread();
  intake.stopFullIntake();
  chassisReference->driveToPoint(Pose<double>(14, 14, 0), {}, {}, {.forwards = false});

  // Score
  blocker.on();
  intake.spinFullIntake(vex::directionType::fwd);
  wait(3000, msec);
  blocker.off();
  intake.stopFullIntake();

  // Back away from low goal
  chassisReference->driveToPoint(Pose<double>(23, 23, 0), {}, {}, {});

  // Drive near park zone
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(23, 61, -360), {}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(23, 61, 0), {}, {}, {});

  // Go into park zone
  intake.spinFullIntake(vex::directionType::rev);
  chassisReference->odometry->pausePositionTrackThread();
  chassisReference->turnTo(Pose<double>(0, 0, 90), {}, {});
  chassisReference->odometry->resumePositionTrackThread();
  chassisReference->driveToPoint(Pose<double>(0, 61, 0), {}, {}, {});

  // Chill
  wait(10000, msec);
  intake.stopFullIntake();
}