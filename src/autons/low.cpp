#include "autons.h"
#include "vex.h"

void Autons::low()
{
    // Convert pseudocode into chassis motions. Hardware-specific actions are omitted.
    chassisReference->odometry->setPosition(-14.26, -46.871, 340);

    DriveParams dparams = fastDriveParams();
    TurnParams tparams = fastTurnParams();
    Settings settings;

    // Eat the blocks in the middle
    chassisReference->driveToPose(Pose<double>(-22.111, -22.111, 340), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // Turn toward center goal
    chassisReference->turnTo(Pose<double>(Vector2D<double>(-14, -14), -360), tparams, settings);

    // Drive to center goal
    chassisReference->driveToPose(Pose<double>(-14, -14, 45), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // (score_low_center_goal omitted)
    wait(400, msec);

    // Drive in front of loader
    chassisReference->driveToPose(Pose<double>(-46.67, -46.67, 45), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // Turn toward loader
    chassisReference->turnTo(Pose<double>(Vector2D<double>(-46.67, -58.748), -360), tparams, settings);

    // (scraper_down omitted)

    // Ram into loader
    chassisReference->driveToPose(Pose<double>(-46.67, -58.748, 180), dparams, tparams, settings, 1.0, 0.0, 0.0);
    wait(1000, msec);

    // (scraper_up omitted)

    // Line up to long goal
    chassisReference->driveToPose(Pose<double>(-46.67, -30.566, 180), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // (score_long_goal omitted)
}