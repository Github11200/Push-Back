#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

void Autons::tuning()
{
  // Prepare chassis
  chassisReference->calibrateInertial();
  chassisReference->resetEncoders();
  Logger::sendMessage("Starting tuning auton. All motions are commented out by default.");

  // Get current pose to build relative targets
  Pose<double> currentPose = chassisReference->odometry->getPose();

  // Settings (use defaults; change if you want different update time or forward/backwards)
  Settings settings;

  // -----------------------------
  // Drive distance tuning (small -> large)
  // Uncomment one line at a time to test each distance with the corresponding DriveParams
  // -----------------------------

  // Drive 5 inches forward
  // chassisReference->driveToPoint(Pose<double>(0, 5, 0), driveParams5_in(), turnParams10_deg(), settings);

  // Drive 10 inches forward
  // chassisReference->driveToPoint(Pose<double>(0, 10, 0), driveParams10_in(), turnParams10_deg(), settings);

  // Drive 20 inches forward
  // chassisReference->driveToPoint(Pose<double>(0, 20, 0), driveParams20_in(), turnParams30_deg(), settings);

  // Drive 30 inches forward
  // chassisReference->driveToPoint(Pose<double>(0, 30, 0), driveParams30_in(), turnParams30_deg(), settings);

  // Drive 50 inches forward
  // chassisReference->driveToPoint(Pose<double>(0, 50, 0), driveParams50_in(), turnParams45_deg(), settings);

  // -----------------------------
  // Turn tuning (small -> large)
  // Uncomment one line at a time to test each turn with the corresponding TurnParams
  // Note: target.pose orientation uses absolute angles (degrees)
  // -----------------------------

  // Turn 10 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 10), turnParams10_deg(), settings);

  // Turn 30 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 30), turnParams30_deg(), settings);

  // Turn 45 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 45), turnParams45_deg(), settings);

  // Turn 60 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 60), turnParams60_deg(), settings);

  // Turn 90 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 90), turnParams90_deg(), settings);

  // Turn 180 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 180), turnParams180_deg(), settings);

  Logger::sendMessage("Tuning auton finished (motions were commented out). Uncomment desired lines to run tests.");
}
