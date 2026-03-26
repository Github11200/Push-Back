#include "chassis.h"

using namespace vex;
using namespace std;

void Chassis::driveWithTwoDistanceSensors(double targetYDistance, double targetXDistance, DriveParams driveParams, TurnParams turnParams, Settings settings, bool leftOrRightSensor)
{
  static Chassis *chassisPointer = this;
  static bool staticLeftOrRight = leftOrRightSensor;
  static DriveParams staticDriveParams = driveParams;
  static double staticTargetY = targetYDistance;
  static double staticTargetX = targetXDistance;

  // Make sure the drive to point is able to run;
  driveToPointRunning = true;
  thread([]()
         {
          double forwardError = 0, horizontalError = 0;
          double elapsedTime = 0;

          // While the robot is more than 1 inch away keep going
          while (forwardError > staticDriveParams.driveSettleError && elapsedTime < staticDriveParams.driveTimeout) {
            double forwardDistance = frontDistance.objectDistance(vex::distanceUnits::in) + Config::kFrontDistanceSensorDistance;
            double horizontalDistance = 0;

            // Use either the left or right distance sensors for the horizontal error compensation
            if (staticLeftOrRight)
              horizontalDistance = rightDistance.objectDistance(vex::distanceUnits::in) + Config::kRightDistanceSensorDistance;
            else
              horizontalDistance = leftDistance.objectDistance(vex::distanceUnits::in) + Config::kLeftDistanceSensorDistance;
            
            // Errors
            forwardError = forwardDistance - staticTargetY;
            horizontalError = horizontalDistance - staticTargetX;

            // Update the point that the robot is "chasing"
            Pose<double> newPose = chassisPointer->odometry->getPose();
            double newY = newPose.position.y + forwardError;
            double newX = newPose.position.x + horizontalError;
            
            chassisPointer->target = newPose;
            
            wait(10, msec);
            elapsedTime += 10;
          }
          chassisPointer->cancelDriveToPoint = true;
          wait(50, msec);
          chassisPointer->cancelDriveToPoint = false; });

  driveToPoint(Pose<double>(0, 0, 0), driveParams, turnParams, settings, true);
}