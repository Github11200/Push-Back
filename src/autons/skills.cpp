#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::skills()
{
  // TODO: enter in stuff like lead for drive to points with Desmos
  // Set starting coordinates
  chassisReference->odometry->setPosition(-46.5, 16.5, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  // Intake the middle 4 blocks
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->driveToPose(Pose<double>(-15, 31, 45), {}, {}, {});

  // Go back to align to middle goal
  chassisReference->driveToPoint(Pose<double>(-23, 23, 0), {}, {}, {.forwards = false});

  // Go up to middle goal
  chassisReference->turnTo(Pose<double>(-13, 13, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-13, 13, 0), {}, {}, {.forwards = false});

  // Score in middle goal
  // Could try to color sort the blue blocks out
  blocker.on();
  wait(1500, msec);
  blocker.off();

  // Drive to 1st dispenser
  willyNilly.on();
  chassisReference->driveToPoint(Pose<double>(-47, 47, 0), {}, {}, {});

  // Ram into 1st dispenser
  chassisReference->turnTo(Pose<double>(-68, 47, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-68, 47, 0), {.driveMaxVoltage = 5, .driveTimeout = 2500}, {}, {});

  // Curve through alleyway
  chassisReference->driveToPose(Pose<double>(-23, 61, 90), {}, {}, {.forwards = false});
  willyNilly.off();
  chassisReference->driveToPoint(Pose<double>(23, 61, 0), {}, {}, {.forwards = false});
  chassisReference->driveToPose(Pose<double>(51, 47, 90), {}, {}, {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(27, 47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(27, 47, 0), {.driveTimeout = 1500}, {}, {.forwards = false});
  willyNilly.on();

  // 1st Score
  sloper.on();
  wait(1500, msec);
  chassisReference->odometry->setPosition(28.5, 47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // Ram into 2nd dispenser
  chassisReference->driveToPoint(Pose<double>(68, 47, 0), {.driveMaxVoltage = 5, .driveTimeout = 2500}, {}, {});

  // Align to long goal
  chassisReference->driveToPoint(Pose<double>(27, 47, 0), {.driveTimeout = 2000}, {}, {.forwards = false});
  willyNilly.off();

  // 2nd Score
  sloper.on();
  wait(1500, msec);
  chassisReference->odometry->setPosition(28.5, 47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // Curve to blue parking zone
  chassisReference->driveToPose(Pose<double>(58, 35, 135), {}, {}, {});
  chassisReference->driveToPose(Pose<double>(63, 17, 180), {}, {}, {});

  // Drive through blue parking zone, going further to make sure to intake all blocks
  chassisReference->driveToPoint(Pose<double>(63, -30, 0), {}, {}, {});

  // Back up against blue parking zone - maybe position reset against barrier?
  chassisReference->driveToPoint(Pose<double>(63, -17, 0), {}, {}, {.forwards = false});

  // Curve to eat the center blocks
  chassisReference->driveToPoint(Pose<double>(23, -23, 0), {}, {}, {});

  // Line up to middle goal
  chassisReference->turnTo(Pose<double>(13, -13, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(13, -13, 0), {}, {}, {.forwards = false});

  // Score in middle goal
  blocker.on();
  wait(1500, msec);
  blocker.off();

  // Go towards 3rd dispenser
  willyNilly.on();
  chassisReference->driveToPoint(Pose<double>(47, -47, 0), {}, {}, {});

  // Ram into 3rd dispenser
  chassisReference->turnTo(Pose<double>(68, 47, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(68, 47, 0), {.driveMaxVoltage = 5, .driveTimeout = 2500}, {}, {});

  // Curve through alleyway
  chassisReference->driveToPose(Pose<double>(23, -61, 270), {}, {}, {.forwards = false});
  willyNilly.off();
  chassisReference->driveToPoint(Pose<double>(-23, -61, 0), {}, {}, {.forwards = false});
  chassisReference->driveToPose(Pose<double>(-51, -47, 270), {}, {}, {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {.driveTimeout = 1500}, {}, {.forwards = false});
  willyNilly.on();

  // 3rd Score
  sloper.on();
  wait(1500, msec);
  chassisReference->odometry->setPosition(-28.5, -47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // Ram into 4th dispenser
  chassisReference->driveToPoint(Pose<double>(-68, -47, 0), {.driveMaxVoltage = 5, .driveTimeout = 2500}, {}, {});

  // Align to long goal
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {.driveTimeout = 2000}, {}, {.forwards = false});
  willyNilly.off();

  // 4th Score
  sloper.on();
  wait(1500, msec);
  chassisReference->odometry->setPosition(-28.5, -47, chassisReference->getAbsoluteHeading().angle);
  sloper.off();

  // Curve to red parking zone
  chassisReference->driveToPose(Pose<double>(-58, -35, 315), {}, {}, {});
  chassisReference->driveToPose(Pose<double>(-63, -17, 0), {}, {}, {});

  // Clear parking zone and park
  chassisReference->driveToPoint(Pose<double>(-63, 1, 0), {}, {}, {});
}