#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::skills()
{
    // Set starting coordinates
    chassisReference->odometry->setPosition(-17.5, 46.5, 90);
    chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
    chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);

    chassisReference->driveToPoint(Pose<double>(-47, 46.5, 0), {}, {}, {});

    // 1st dispenser
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, 180), {}, {});
    willyNilly.on();
    intake.spinFullIntake(vex::directionType::fwd);
    chassisReference->odometry->resumePositionTrackThread();
    chassisReference->driveToPoint(Pose<double>(-47, 70, 0), {.driveTimeout = 3000}, {}, {}); // Drive into the dispenser for 3 seconds

    // 1st long goal
    chassisReference->driveToPoint(Pose<double>(-47, 31, 0), {}, {}, {.forwards = false});

    // Score
    sloper.on();
    wait(3000, msec);
    intake.stopFullIntake();
    sloper.off();
    wait(300, msec);

    // Back away from 1st long goal
    chassisReference->driveToPoint(Pose<double>(-47, 39, 0), {}, {}, {});

    // Drive across field to 2nd dispenser
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, -90), {}, {});
    chassisReference->odometry->resumePositionTrackThread();
    chassisReference->driveToPoint(Pose<double>(47, 39, 0), {}, {}, {});

    // 2nd dispenser
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, 180), {}, {});
    willyNilly.on();
    intake.spinFullIntake(vex::directionType::fwd);
    chassisReference->odometry->resumePositionTrackThread();
    chassisReference->driveToPoint(Pose<double>(47, 70, 0), {.driveTimeout = 3000}, {}, {});

    // 2nd long goal
    chassisReference->driveToPoint(Pose<double>(47, 31, 0), {}, {}, {.forwards = false});

    // Score
    sloper.on();
    wait(3000, msec);
    intake.stopFullIntake();
    sloper.off();
    wait(300, msec);

    // Back away from 2nd long goal
    chassisReference->driveToPoint(Pose<double>(47, 39, 0), {}, {}, {});

    // Position to the alleyway
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, -90), {}, {});
    chassisReference->odometry->resumePositionTrackThread();
    chassisReference->driveToPoint(Pose<double>(60, 39, 0), {}, {}, {});

    // Drive to 3rd dispenser
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, 0), {}, {});
    chassisReference->odometry->resumePositionTrackThread();
    chassisReference->driveToPoint(Pose<double>(60, -38, 0), {}, {}, {});

    // Align to 3rd dispenser
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, 45), {}, {});
    chassisReference->odometry->resumePositionTrackThread();
    chassisReference->driveToPoint(Pose<double>(47, -51, 0), {}, {}, {});

    // 3rd dispenser
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, 0), {}, {});
    willyNilly.on();
    intake.spinFullIntake(vex::directionType::fwd);
    chassisReference->odometry->resumePositionTrackThread();
    chassisReference->driveToPoint(Pose<double>(47, -70, 0), {.driveTimeout = 3000}, {}, {});

    // 2nd long goal other half
    chassisReference->driveToPoint(Pose<double>(47, -31, 0), {}, {}, {.forwards = false});

    // Score
    sloper.on();
    wait(3000, msec);
    intake.stopFullIntake();
    sloper.off();
    wait(300, msec);

    // Back away from 2nd long goal other half
    chassisReference->driveToPoint(Pose<double>(47, -39, 0), {}, {}, {});

    // Drive across field to 4th dispenser
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, 90), {}, {});
    chassisReference->odometry->resumePositionTrackThread();
    chassisReference->driveToPoint(Pose<double>(-47, -39, 0), {}, {}, {.forwards = false});

    // 4th dispenser
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, 0), {}, {});
    willyNilly.on();
    intake.spinFullIntake(vex::directionType::fwd);
    chassisReference->odometry->resumePositionTrackThread();
    chassisReference->driveToPoint(Pose<double>(-47, -70, 0), {.driveTimeout = 3000}, {}, {});

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

    // Align to middle goal
    chassisReference->odometry->pausePositionTrackThread();
    chassisReference->turnTo(Pose<double>(0, 0, -135), {}, {});
    chassisReference->odometry->resumePositionTrackThread();
    intake.stopFullIntake();
    chassisReference->driveToPoint(Pose<double>(14, 14, 0), {}, {}, {.forwards = false});

    // Score
    sloper.on();
    wait(600, msec);
    intake.spinFullIntake(vex::directionType::fwd);
    wait(3000, msec);
    intake.stopFullIntake();
    sloper.off();

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
}