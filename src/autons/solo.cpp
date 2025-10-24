#include "autons.h"
#include "vex.h"

void Autons::solo()
{
    // Solo auton is similar to high but repeats some steps. Hardware-specific actions omitted.
    chassisReference->odometry->setPosition(14.26, -46.871, 340);

    DriveParams dparams = fastDriveParams();
    TurnParams tparams = fastTurnParams();
    Settings settings;

    // First set of interactions
    chassisReference->driveToPose(Pose<double>(22.111, -22.111, 340), dparams, tparams, settings, 1.0, 0.0, 0.0);
    chassisReference->turnTo(Pose<double>(Vector2D<double>(14, -14), -360), tparams, settings);
    chassisReference->driveToPose(Pose<double>(14, -14, 225), dparams, tparams, settings, 1.0, 0.0, 0.0);
    // (score_high_center_goal omitted)
    wait(400, msec);

    chassisReference->driveToPose(Pose<double>(46.67, -46.67, 225), dparams, tparams, settings, 1.0, 0.0, 0.0);
    chassisReference->turnTo(Pose<double>(Vector2D<double>(46.67, -58.748), -360), tparams, settings);
    // (scraper_down omitted)
    chassisReference->driveToPose(Pose<double>(46.67, -58.748, 180), dparams, tparams, settings, 1.0, 0.0, 0.0);
    wait(1000, msec);
    // (scraper_up omitted)
    chassisReference->driveToPose(Pose<double>(46.67, -30.566, 180), dparams, tparams, settings, 1.0, 0.0, 0.0);
    // (score_long_goal omitted)
    wait(4000, msec);

    // Back away from long goal so the aligner doesn't get stuck
    chassisReference->driveToPose(Pose<double>(46.67, -37.813, 180), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // Turn and eat the other middle blocks
    chassisReference->turnTo(Pose<double>(Vector2D<double>(-22.111, -22.111), -360), tparams, settings);
    chassisReference->driveToPose(Pose<double>(-22.111, -22.111, 258), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // Go to opposite loader and perform the same loader interaction
    chassisReference->driveToPose(Pose<double>(-46.67, -46.67, 135), dparams, tparams, settings, 1.0, 0.0, 0.0);
    chassisReference->turnTo(Pose<double>(Vector2D<double>(-46.67, -58.748), -360), tparams, settings);
    // (scraper_down omitted)
    chassisReference->driveToPose(Pose<double>(-46.67, -58.748, 180), dparams, tparams, settings, 1.0, 0.0, 0.0);
    wait(1000, msec);
    // (scraper_up omitted)
    chassisReference->driveToPose(Pose<double>(-46.67, -30.566, 180), dparams, tparams, settings, 1.0, 0.0, 0.0);
    // (score_long_goal omitted)
}