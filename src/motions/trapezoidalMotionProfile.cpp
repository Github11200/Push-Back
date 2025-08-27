#include "../../include/chassis.h"

using namespace std;
using namespace vex;

void Chassis::trapezoidalMotionProfile(double distance, MotionProfile motionProfileSettings, DriveParams driveParams, TurnParams turnParams, Settings settings)
{
  // vf^2 = vi^2 + 2ad
  double maximumReachableVelocity = min(sqrt(2 * motionProfileSettings.maximumAcceleration * (distance / 2)), motionProfileSettings.maximumVelocity);

  double kV = 1 / maximumReachableVelocity;

  // vf = vi + at
  double accelerationTime = (maximumReachableVelocity / motionProfileSettings.maximumAcceleration);
  // TODO: Remove deceleration time
  double decelerationTime = (maximumReachableVelocity) / motionProfileSettings.maximumAcceleration;

  // d = vf^2 / 2a
  double accelerationDistance = (motionProfileSettings.maximumAcceleration * pow(accelerationTime, 2)) / 2;
  double decelerationDistance = (motionProfileSettings.maximumAcceleration * pow(decelerationTime, 2)) / 2;
  double cruiseDistance = distance - accelerationDistance - decelerationDistance;

  // If there is no time to cruise then it's just a triangular profile
  if (cruiseDistance < 0)
    cruiseDistance = 0;
  double cruiseTime = (cruiseDistance / maximumReachableVelocity);

  double totalTime = accelerationTime + decelerationTime + cruiseTime;
  double elapsedTime = 0;

  PID driveFeedbackPID(settings.updateTime, driveParams);
  PID turnFeedbackPID(settings.updateTime, turnParams);

  Pose<double> startPose = odometry->getPose();
  Pose<double> currentPose = startPose;

  double setpoint, setpointVelocity, setpointAcceleration, feedforward, driveError, turnError, driveOutput, turnOutput = 0;

  // cout << "Cruise distance: " << cruiseDistance << endl;
  cout << "max reachable velocity (not light speed): " << maximumReachableVelocity << endl;
  cout << "acceleration distance: " << accelerationDistance << endl;
  cout << "deceleration distance: " << decelerationDistance << endl;
  // cout << "max acceleration: " << motionProfileSettings.maximumAcceleration << endl;
  cout << "acceleration time: " << accelerationTime << endl;
  cout << "deceleration time: " << decelerationTime << endl;
  cout << "max velocity: " << maximumReachableVelocity << endl;
  cout << "kv: " << kV << endl;
  cout << "total time: " << totalTime << endl;

  while (elapsedTime < totalTime)
  {
    currentPose = odometry->getPose();

    if (elapsedTime < accelerationTime) // Accelerating
    {
      // d = (a * t^2) / 2
      setpoint = (motionProfileSettings.maximumAcceleration * pow(elapsedTime, 2)) / (double)2;

      setpointVelocity = motionProfileSettings.maximumAcceleration * elapsedTime;
      setpointAcceleration = motionProfileSettings.maximumAcceleration;
    }
    else if (elapsedTime < accelerationTime + cruiseTime) // Cruising
    {
      // How long we've been cruising for
      double elapsedCruiseTime = elapsedTime - accelerationTime;
      setpoint = (accelerationDistance + (maximumReachableVelocity * elapsedCruiseTime));

      setpointVelocity = maximumReachableVelocity;
      setpointAcceleration = 0;
    }
    else // Decelerating
    {
      double elapsedDecelerationTime = elapsedTime - accelerationTime - cruiseTime;
      // This is the same formula as d = v * t + 1/2 * a * t^2 except the acceleration is negative which is why there's a minus sign
      double travelledDecelerationDistance = maximumReachableVelocity * elapsedDecelerationTime - (motionProfileSettings.maximumAcceleration * pow(elapsedDecelerationTime, 2)) / 2;

      setpoint = accelerationDistance + cruiseDistance + travelledDecelerationDistance;

      setpointVelocity = maximumReachableVelocity - (motionProfileSettings.maximumAcceleration * elapsedDecelerationTime);
      setpointAcceleration = motionProfileSettings.maximumAcceleration;
    }

    feedforward = kV * setpointVelocity + motionProfileSettings.kA * setpointAcceleration;

    driveError = setpoint - (startPose.position.distanceTo(currentPose.position));
    turnError = currentPose.orientation.angleTo(startPose.orientation).angle;

    driveOutput = driveFeedbackPID.compute(driveError);
    turnOutput = turnFeedbackPID.compute(turnError);

    Pair motorOutputs = getMotorVelocities(driveOutput, turnOutput);
    Left.spin(fwd, feedforward + motorOutputs.left, volt);
    Right.spin(fwd, feedforward + motorOutputs.right, volt);

    elapsedTime += (settings.updateTime / (double)1000); // Convert the update time from millseconds to seconds
    wait(settings.updateTime, msec);
  }

  Left.stop(brake);
  Right.stop(brake);
}