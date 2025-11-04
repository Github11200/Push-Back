#include "autons.h"
#include "subsystems/intake.h"
#include "vex.h"

void Autons::high()
{
    Intake intake;

    // Convert pseudocode into chassis motions. Hardware-specific actions (scoring, scraper) are intentionally omitted.
    // Set starting coordinates
    chassisReference->odometry->setPosition(0, 0, 0);
    chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR); 
    chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);
    // while (true) {
    //     cout << "X: " << chassisReference->odometry->getPose().position.x << "Y: " << chassisReference->odometry->getPose().position.y << "R: " << chassisReference->odometry->getPose().orientation.angle << endl;
    //     chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR);
    //     chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);
    //     wait(500, msec);
    // }
    // return;

    intake.spinFullIntake(vex::directionType::fwd);

    // Drive to the middle blocks (absolute field coordinate) 
    chassisReference->turnTo(Pose<double>(-22.111, -22.111, -360), {.turnKp = 0.3}, {});  
    chassisReference->driveToPoint(Pose<double>(-22.111, -22.111, 0), {}, {}, {});
    chassisReference->odometry->wallReset(DistanceSensor::STERN, Wall::REAR); 
    chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);
 
    // Turn to face the center goal location (turn to point (14, -14)) 
    chassisReference->turnTo(Pose<double>(-14, -14, -360), {}, { .forwards = false });

    // Drive to center goal
    cout << "X: " << chassisReference->odometry->getPose().position.x << endl;  
    cout << "Y: " << chassisReference->odometry->getPose().position.y << endl;
    // chassisReference->driveToPoint(Pose<double>(-14, -14, 0), {}, {}, { .forwards = false });
    // chassisReference->odometry->wallReset(DistanceSensor::STARBOARD, Wall::LEFT);  
    // chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::REAR);  

    cout << "HAHAHAHAHHAHAHAHAHAH" << endl;

    // // (score_high_center_goal omitted)
    // wait(400, msec);

    // // Drive in front of the loader
    // chassisReference->driveToPose(Pose<double>(-46.67, -46.67, 225), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // // Turn toward loader entrance point
    // chassisReference->turnTo(Pose<double>(Vector2D<double>(-46.67, -58.748), -360), tparams, settings);

    // // Slap down the willy nilly
    // willyNilly.on();

    // // Ram into loader
    // chassisReference->driveToPose(Pose<double>(-46.67, -58.748, 180), dparams, tparams, settings, 1.0, 0.0, 0.0);
    // wait(1000, msec);

    // // Pull this thingy up
    // willyNilly.off();

    // // Line up to long goal
    // chassisReference->driveToPose(Pose<double>(-46.67, -30.566, 180), dparams, tparams, settings, 1.0, 0.0, 0.0);

    // (score_long_goal omitted)
}