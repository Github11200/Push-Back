#include "autons.h"
#include "vex.h"

void Autons::high()
{
    // Convert pseudocode into chassis motions. Hardware-specific actions (scoring, scraper) are intentionally omitted.
    // Set starting coordinates
    chassisReference->odometry->setPosition(-17.742, -47.297, 350);
    chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
    chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);
    while (true) {
        cout << "X: " << chassisReference->odometry->getPose().position.x << "Y: " << chassisReference->odometry->getPose().position.y << "R: " << chassisReference->odometry->getPose().orientation.angle << endl;
        chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
        chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);
        wait(500, msec);
    }
    return;
    chassisReference->odometry->setPosition(-17.742, -47.297, 350);

    // Use fast drive/turn params and default settings for autonomous motions 
    DriveParams dparams = fastDriveParams();
    TurnParams tparams = fastTurnParams();
    Settings settings;

    // Drive to the middle blocks (absolute field coordinate)
    chassisReference->driveToPose(Pose<double>(-22.111, -22.111, 350), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // Turn to face the center goal location (turn to point (14, -14))
    chassisReference->turnTo(Pose<double>(Vector2D<double>(-14, -14), -360), tparams, settings);

    // Drive to center goal
    chassisReference->driveToPose(Pose<double>(-14, -14, 225), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // (score_high_center_goal omitted)
    wait(400, msec);

    // Drive in front of the loader
    chassisReference->driveToPose(Pose<double>(-46.67, -46.67, 225), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // Turn toward loader entrance point
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