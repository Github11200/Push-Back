#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::skills()
{
  // Set starting coordinates
  chassisReference->odometry->setPosition(-46.5, -16.5, 180);
  chassisReference->odometry->startPositionTrackThread(false);

  // Drive in front of the dispenser
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(-46.5, -47, 180), {}, {});
  chassisReference->driveToPoint(Pose<double>(-46.5, -47, 0), {.driveTimeout = 1500}, {}, {});

  // 1st dispenser
  chassisReference->turnTo(Pose<double>(-70, -47, 270), {}, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-70, -47, 0), {.driveTimeout = 3000, .driveMaxVoltage = 4}, {}, {}); // Drive into the dispenser for 3 seconds

  // Drive back
  chassisReference->turnTo(Pose<double>(-39, -47, 270), {}, {});
  chassisReference->driveToPoint(Pose<double>(-39, -46.5, 0), {.driveTimeout = 1500}, {}, {.forwards = false});

  // Drive across field to 2nd goal first
  chassisReference->turnTo(Pose<double>(-39, 45, 0), {}, {});
  chassisReference->driveToPoint(Pose<double>(-39, 47, 0), {}, {}, {});

  // 2nd long goal
  chassisReference->turnTo(Pose<double>(-28.5, 4, 270), {}, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-20, 47, 0), {.driveTimeout = 1500, .driveMaxVoltage = 5}, {}, {.forwards = false});
  chassisReference->odometry->setPosition(-28.5, 47, chassisReference->getAbsoluteHeading().angle);

  // Score
  sloper.on();
  wait(1500, msec);
  sloper.off();

  // Drive into the dispenser
  chassisReference->turnTo(Pose<double>(-70, 47, 270), {}, {});
  chassisReference->driveToPoint(Pose<double>(-70, 47, 0), {.driveTimeout = 3000, .driveMaxVoltage = 4}, {}, {});

  // Score on the 2nd long goal again
  chassisReference->turnTo(Pose<double>(-20, 47, 270), {}, {});
  chassisReference->driveToPoint(Pose<double>(-20, 47, 0), {.driveTimeout = 1500, .driveMaxVoltage = 5}, {}, {.forwards = false});
  chassisReference->odometry->setPosition(-28.5, 47, chassisReference->getAbsoluteHeading().angle);

  // Score
  sloper.on();
  wait(1500, msec);
  sloper.off();

  // Back away from 2nd long goal
  willyNilly.off();
  chassisReference->turnTo(Pose<double>(-39, 47, 270), {}, {});
  chassisReference->driveToPoint(Pose<double>(-39, 47, 0), {.driveTimeout = 1000}, {}, {});

  // Position to the alleyway
  chassisReference->turnTo(Pose<double>(-39, 58, 0), {}, {});
  chassisReference->driveToPoint(Pose<double>(-39, 58, 0), {.driveTimeout = 1000}, {}, {});

  // Drive to 3rd dispenser
  chassisReference->turnTo(Pose<double>(39, 54, 90), {}, {});
  chassisReference->driveToPoint(Pose<double>(39, 54, 0), {.driveTimeout = 2000}, {}, {});

  // Align to 3rd dispenser
  chassisReference->turnTo(Pose<double>(39, 40, 180), {}, {});
  chassisReference->driveToPoint(Pose<double>(39, 40, 0), {.driveTimeout = 1000}, {}, {});

  // 3rd dispenser
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(70, 40, 90), {}, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(70, 40, 0), {.driveTimeout = 3000, .driveMaxVoltage = 4}, {}, {});

  // Drive back from it
  chassisReference->turnTo(Pose<double>(39, 40, 90), {}, {});
  chassisReference->driveToPoint(Pose<double>(39, 40, 0), {.driveTimeout = 1200}, {}, {.forwards = false});

  // Go to the other side of the field
  chassisReference->turnTo(Pose<double>(39, -54, 180), {}, {});
  chassisReference->driveToPoint(Pose<double>(39, -54, 0), {}, {}, {});

  // Score on the long goal
  chassisReference->turnTo(Pose<double>(20, -54, 90), {}, {});
  chassisReference->driveToPoint(Pose<double>(20, -54, 0), {.driveMaxVoltage = 5}, {}, {.forwards = false});
  chassisReference->odometry->setPosition(28.5, -47, chassisReference->getAbsoluteHeading().angle);

  // Score
  sloper.on();
  wait(3000, msec);
  sloper.off();
  wait(300, msec);

  // 4th dispenser
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->turnTo(Pose<double>(70, -47, 90), {}, {});
  chassisReference->driveToPoint(Pose<double>(70, -47, 0), {.driveTimeout = 3000, .driveMaxVoltage = 4}, {}, {});

  // Score the blocks from the dispenser again in the 2nd dispenser
  willyNilly.off();
  chassisReference->turnTo(Pose<double>(20, -47, 90), {}, {});
  chassisReference->driveToPoint(Pose<double>(20, -47, 0), {.driveMaxVoltage = 5}, {}, {.forwards = false});

  // Score
  sloper.on();
  wait(1500, msec);
  sloper.off();

  chassisReference->turnTo(Pose<double>(30, -47, 90), {}, {});
  chassisReference->driveToPoint(Pose<double>(30, -47, 0), {}, {}, {});

  // Curve there
  chassisReference->driveToPose(Pose<double>(62.472, -33.442, 0), {}, {}, {}, 0.4, 0, 0.5);

  // Ram full speed into the parking zone
  chassisReference->turnTo(Pose<double>(64, 60, 0), {}, {});
  chassisReference->driveToPoint(Pose<double>(64, 10, 0), {}, {}, {});

  /*
  WE'LL DO THIS SOME OTHER DAY :)
*/

  // Back away from 1st long goal other half (drive longer to line up to get center balls 45 degrees)
  // chassisReference->driveToPoint(Pose<double>(-47, -47, 0), {}, {}, {});

  // // Eat 1st ball stack
  // intake.spinFullIntake(vex::directionType::fwd);
  // chassisReference->odometry->pausePositionTrackThread();
  // chassisReference->turnTo(Pose<double>(-23, -23, -360), {}, {});
  // chassisReference->odometry->resumePositionTrackThread();
  // chassisReference->driveToPoint(Pose<double>(-23, -23, 0), {}, {}, {});

  // // Eat 2nd ball stack
  // chassisReference->odometry->pausePositionTrackThread();
  // chassisReference->turnTo(Pose<double>(23, -23, -360), {}, {});
  // chassisReference->odometry->resumePositionTrackThread();
  // chassisReference->driveToPoint(Pose<double>(23, -23, 0), {}, {}, {});

  // // Align to low goal
  // chassisReference->odometry->pausePositionTrackThread();
  // chassisReference->turnTo(Pose<double>(0, 0, 135), {}, {});
  // chassisReference->odometry->resumePositionTrackThread();
  // intake.stopFullIntake();
  // chassisReference->driveToPoint(Pose<double>(14, -14, 0), {}, {}, {});

  // // Score
  // intake.spinFullIntake(vex::directionType::rev);
  // wait(3000, msec);
  // intake.stopFullIntake();

  // // Back away from low goal
  // chassisReference->driveToPoint(Pose<double>(23, -23, 0), {}, {}, {.forwards = false});

  // // Eat 3rd ball stack
  // chassisReference->odometry->pausePositionTrackThread();
  // chassisReference->turnTo(Pose<double>(23, 23, -360), {}, {});
  // chassisReference->odometry->resumePositionTrackThread();
  // chassisReference->driveToPoint(Pose<double>(23, 23, 0), {}, {}, {});

  // // Align to middle high goal
  // chassisReference->odometry->pausePositionTrackThread();
  // chassisReference->turnTo(Pose<double>(0, 0, -135), {}, {});
  // chassisReference->odometry->resumePositionTrackThread();
  // intake.stopFullIntake();
  // chassisReference->driveToPoint(Pose<double>(14, 14, 0), {}, {}, {.forwards = false});

  // // Score
  // blocker.on();
  // intake.spinFullIntake(vex::directionType::fwd);
  // wait(3000, msec);
  // blocker.off();
  // intake.stopFullIntake();

  // // Back away from low goal
  // chassisReference->driveToPoint(Pose<double>(23, 23, 0), {}, {}, {});

  // // Drive near park zone
  // chassisReference->odometry->pausePositionTrackThread();
  // chassisReference->turnTo(Pose<double>(23, 61, -360), {}, {});
  // chassisReference->odometry->resumePositionTrackThread();
  // chassisReference->driveToPoint(Pose<double>(23, 61, 0), {}, {}, {});

  // // Go into park zone
  // intake.spinFullIntake(vex::directionType::rev);
  // chassisReference->odometry->pausePositionTrackThread();
  // chassisReference->turnTo(Pose<double>(0, 0, 90), {}, {});
  // chassisReference->odometry->resumePositionTrackThread();
  // chassisReference->driveToPoint(Pose<double>(0, 61, 0), {}, {}, {});

  // // Chill
  // wait(10000, msec);
  // intake.stopFullIntake();
}