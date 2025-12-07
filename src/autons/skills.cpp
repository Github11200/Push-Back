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
  // chassisReference->turnTo(Pose<double>(-46.5, -47, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-46.5, -45, 0), {.driveTimeout = 1200}, {}, {});

  // 1st dispenser
  chassisReference->turnTo(Pose<double>(-70, -46, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-70, -46, 0), {.driveTimeout = 3000, .driveMaxVoltage = 5}, {}, {}); // Drive into the dispenser for 3 seconds

  // Drive back
  chassisReference->turnTo(Pose<double>(-39, -46, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-39, -46, 0), {.driveTimeout = 1500}, {}, {.forwards = false});

  // Drive across field to 2nd goal first
  chassisReference->turnTo(Pose<double>(-39, 52.15, 0), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-39, 51, 0), {.driveTimeout = 1600, .driveMaxVoltage = 10, .driveSettleError = 5}, {}, {});
  chassisReference->driveToPoint(Pose<double>(-39, 52.15, 0), {.driveSettleError = 0.1, .driveSettleTime = 900, .driveTimeout = 3000, .driveMaxVoltage = 6.4}, {}, {});
  cout << "X: " << chassisReference->odometry->getPose().position.x << endl;
  cout << "Y: " << chassisReference->odometry->getPose().position.y << endl;

  // 2nd long goal
  chassisReference->turnTo(Pose<double>(-20, 52.15, -360), {}, {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(-20, 52.15, 0), {.driveTimeout = 1500, .driveMaxVoltage = 5}, {}, {.forwards = false});

  // Score
  sloper.on();
  wait(1500, msec);
  chassisReference->odometry->setPosition(-28.5, 47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // Drive into the dispenser
  chassisReference->turnTo(Pose<double>(-70, 45, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-70, 45, 0), {.driveTimeout = 3000, .driveMaxVoltage = 5}, {.turnMaxVoltage = 0}, {});

  // Score on the 2nd long goal again
  chassisReference->turnTo(Pose<double>(-20, 46, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-20, 46, 0), {.driveTimeout = 1500, .driveMaxVoltage = 5}, {}, {.forwards = false});

  // Score
  sloper.on();
  wait(1500, msec);
  chassisReference->odometry->setPosition(-28.5, 47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // Back away from 2nd long goal
  willyNilly.off();
  chassisReference->turnTo(Pose<double>(-39, 47, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-39, 47, 0), {.driveTimeout = 1000}, {}, {});

  // Position to the alleyway
  chassisReference->turnTo(Pose<double>(-39, 59, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-39, 59, 0), {.driveTimeout = 1000}, {}, {});

  // Drive to 3rd dispenser
  chassisReference->turnTo(Pose<double>(42, 56, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(42, 56, 0), {.driveTimeout = 2000}, {}, {});

  // Align to 3rd dispenser
  chassisReference->turnTo(Pose<double>(42, 37.5, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(42, 37.5, 0), {.driveTimeout = 1000}, {}, {});

  // 3rd dispenser
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(70, 37.5, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPoint(Pose<double>(70, 37.2, 0), {.driveTimeout = 3000, .driveMaxVoltage = 5}, {}, {});

  // Drive back from it
  chassisReference->turnTo(Pose<double>(42, 37.5, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 37.5, 0), {.driveTimeout = 1200}, {}, {.forwards = false});

  // Go to the other side of the field
  chassisReference->turnTo(Pose<double>(42, -60, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(42, -61.1, 0), {.driveTimeout = 1600, .driveMaxVoltage = 10}, {}, {});
  chassisReference->driveToPoint(Pose<double>(42, -60, 0), {.driveSettleError = 0.1, .driveSettleTime = 500, .driveTimeout = 3000, .driveMaxVoltage = 7}, {}, {});
  cout << "X: " << chassisReference->odometry->getPose().position.x << endl;
  cout << "Y: " << chassisReference->odometry->getPose().position.y << endl;

  // Score on the long goal
  chassisReference->turnTo(Pose<double>(15, -60, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(15, -60, 0), {.driveMaxVoltage = 6, .driveTimeout = 1500}, {}, {.forwards = false});

  // Score
  sloper.on();
  wait(1500, msec);
  chassisReference->odometry->setPosition(28.5, -47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // 4th dispenser
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->turnTo(Pose<double>(70, -49, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(70, -49, 0), {.driveTimeout = 3300, .driveMaxVoltage = 4.5}, {}, {});

  // Score the blocks from the dispenser again in the 2nd dispenser
  willyNilly.off();
  chassisReference->turnTo(Pose<double>(20, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(20, -47, 0), {.driveMaxVoltage = 5}, {}, {.forwards = false});

  // Score
  sloper.on();
  wait(1500, msec);
  sloper.off();

  // drive calmly :)
  chassisReference->turnTo(Pose<double>(50, -26, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(50, -26, 0), {.driveTimeout = 1000}, {}, {});

  // drive calmly x2 :)
  chassisReference->turnTo(Pose<double>(-65, -25, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-65, -25, 0), {}, {}, {});

  // Ram full speed into the parking zone
  chassisReference->turnTo(Pose<double>(0, 0, -5), {}, {});
  // willyNilly.on();
  sloper.on();
  Left.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  Right.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(1.5, sec);
  Left.stop(coast);
  Right.stop(coast);
  // chassisReference->turnTo(Pose<double>(64, 60, 0), {}, {});
  // chassisReference->driveToPoint(Pose<double>(64, 10, 0), {.driveMaxVoltage = 8}, {}, {});

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