#include "chassis.h"
#include "types/motionProfilePose.h"

using namespace std;
using namespace vex;

struct TrajectoryParams
{
  CurvedMotionProfile profile;
  double trackWidth;
};

double limitSpeedDueToCurvature(double maxSpeed, double curvature,
                                double trackWidth)
{
  double radius = 1 / curvature;
  return (2 * maxSpeed) / (2 + trackWidth * curvature);
}

vector<double> pass(const vector<double> &distances, vector<double> &velocities,
                    const vector<double> &accelerations)
{
  vector<double> constrainedVelocities;
  constrainedVelocities.push_back(velocities[0]);

  int length = distances.size();
  for (int i = 1; i < length; ++i)
  {
    double deltaD = abs(distances[i] - distances[i - 1]);

    double maxAttainableVelocity =
        sqrt(pow(velocities[i - 1], 2) + 2 * accelerations[i] * deltaD);

    velocities[i] = min(velocities[i], maxAttainableVelocity);
  }

  return constrainedVelocities;
}

vector<MotionProfilePose<double>> generateTrajectory(TrajectoryParams params)
{
  CubicBezier curve = params.profile.curve;

  vector<Vector2D<double>> positions({curve.getPosition(0)});
  vector<double> curvatures({curve.getCurvature(0)});
  vector<double> distances({0});
  vector<double> velocities({params.profile.initialVelocity});
  vector<double> accelerations({curve.getSecondDerivative(0).magnitude()});
  vector<double> angles({atan2(curve.getFirstDerivative(0).y, curve.getFirstDerivative(0).x)});

  // First constrain based on only the curvature
  int numberOfSegments =
      curve.getArcLength(1) / params.profile.distanceBetweenPoints;
  for (int i = 1; i < numberOfSegments; ++i)
  {
    double t = static_cast<double>(i) / static_cast<double>(numberOfSegments);

    double currentDistance = curve.getArcLength(t);

    double speed = curve.getFirstDerivative(t).magnitude();
    double curvature = curve.getCurvature(t);

    double constrainedSpeed = limitSpeedDueToCurvature(
        params.profile.maximumVelocity, abs(curvature), params.trackWidth);
    double acceleration = curve.getSecondDerivative(t).magnitude();
    acceleration = min(acceleration, params.profile.maximumAcceleration);

    positions.push_back(curve.getPosition(t));
    curvatures.push_back(curvature);
    distances.push_back(currentDistance);
    velocities.push_back(min(constrainedSpeed, speed));
    accelerations.push_back(acceleration);
    angles.push_back(atan2(curve.getFirstDerivative(t).y, curve.getFirstDerivative(t).x));
  }

  positions.push_back(curve.getPosition(1));
  curvatures.push_back(curve.getCurvature(1));
  distances.push_back(curve.getArcLength(1));
  velocities.push_back(params.profile.finalVelocity);
  accelerations.push_back(min(curve.getSecondDerivative(1).magnitude(),
                              params.profile.maximumAcceleration));
  angles.push_back(atan2(curve.getFirstDerivative(1).y, curve.getFirstDerivative(1).x));

  // Left -> Right pass
  pass(distances, velocities, accelerations);

  std::reverse(distances.begin(), distances.end());
  std::reverse(velocities.begin(), velocities.end());
  std::reverse(accelerations.begin(), accelerations.end());

  // Right --> Left pass
  pass(distances, velocities, accelerations);

  std::reverse(distances.begin(), distances.end());
  std::reverse(velocities.begin(), velocities.end());
  std::reverse(accelerations.begin(), accelerations.end());

  vector<double> times({0.0});

  // Distances --> Times
  double time = 0;
  for (int i = 1; i < velocities.size(); ++i)
  {
    double deltaD = distances[i] - distances[i - 1];
    double acceleration =
        (pow(velocities[i], 2) - pow(velocities[i - 1], 2)) / (2 * deltaD);

    acceleration = min(acceleration, params.profile.maximumAcceleration);

    if (acceleration == 0.0)
      time += deltaD / velocities[i];
    else
      time += (velocities[i] - velocities[i - 1]) / acceleration;

    times.push_back(time);
  }

  vector<MotionProfilePose<double>> trajectory;
  for (int i = 0; i < times.size(); ++i)
  {
    trajectory.push_back(MotionProfilePose<double>(
        times[i],
        Pose<double>(positions[i], Angle<double>((M_PI / 2) - angles[i]).toDeg().angle),
        velocities[i], curvatures[i] * velocities[i], accelerations[i]));
  }

  return trajectory;
}

void Chassis::curvedMotionProfile(CurvedMotionProfile profile, RamseteParams ramseteParams)
{
  vector<MotionProfilePose<double>> trajectory = generateTrajectory({.profile = profile, .trackWidth = trackWidth});

  cout << trajectory[0].pose.orientation.angle << endl;

  // .first = linear, .second = angular
  pair<double, double> previousVelocities(0, 0);
  for (int i = 1; i < trajectory.size(); ++i)
  {
    double desiredVelocity = trajectory[i].velocity;
    double desiredAngularVelocity = trajectory[i].angularVelocity;

    Pose<double> desiredPose = trajectory[i].pose;
    Pose<double> currentPose = odometry->getPose();
    Angle<double> currentAngle = getAbsoluteHeading().constrainNegative180To180();

    double xError = desiredPose.position.x - currentPose.position.x;
    double yError = desiredPose.position.y - currentPose.position.y;
    double angleError = (desiredPose.orientation - currentPose.orientation).constrainNegative180To180().angle;

    double currentAngleRad = -currentAngle.toRad().angle;
    double transformationMatrix[2][2] = {
        {cos(currentAngleRad), sin(currentAngleRad)},
        {-sin(currentAngleRad), cos(currentAngleRad)}};

    double localXError = xError * transformationMatrix[0][0] + yError * transformationMatrix[0][1];
    double localYError = xError * transformationMatrix[1][0] + yError * transformationMatrix[1][1];
    double localAngleError = Angle<double>(angleError).toRad().angle;

    double gainValue =
        2 * ramseteParams.zeta * sqrt(pow(desiredAngularVelocity, 2) + ramseteParams.beta * pow(desiredVelocity, 2));

    double linearVelocity =
        desiredVelocity * cos(localAngleError) +
        (gainValue * localYError);

    double angularVelocity =
        desiredAngularVelocity +
        gainValue * localAngleError +
        ramseteParams.beta * desiredVelocity * sinc(localAngleError) * localXError;

    linearVelocity = linearVelocity * profile.kV + trajectory[i].acceleration * profile.kA;
    angularVelocity = angularVelocity * profile.kV + trajectory[i].acceleration * profile.kA;

    double leftPower = (linearVelocity + angularVelocity);
    double rightPower = (linearVelocity - angularVelocity);

    Left.spin(vex::directionType::fwd, leftPower, vex::voltageUnits::volt);
    Right.spin(vex::directionType::fwd, rightPower, vex::voltageUnits::volt);

    if (i != trajectory.size() - 1)
      vex::wait(trajectory[i + 1].time - trajectory[i].time, vex::timeUnits::sec);
  }

  Left.stop(coast);
  Right.stop(coast);
}