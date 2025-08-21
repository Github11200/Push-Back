// #include "../../include/pursuit.h"
// #include "../../include/utils.h"
// #include <fstream>
// #include <iostream>
// #include <climits>

// using namespace vex;
// using namespace std;

// Pursuit::Pursuit(PursuitParams params) : params(params)
// {
// }

// /// @brief Reads a text file with the path
// /// @param fileName The name of the file
// /// @return An array of points with each point having x and y coordinates and a speed
// Path Pursuit::loadPathFromFile(string fileName)
// {
//   ifstream pathFile(fileName);
//   Path path;

//   string line;
//   Pose<double> pose;

//   // Loop through the entire file and get each coordinate and add it to the path
//   while (getline(pathFile, line))
//   {
//     if (line == "endData")
//       break;

//     string stringNumber = "";
//     int resultIndex = 0;
//     double pointResult[3];

//     for (int i = 0; i < line.size(); ++i)
//     {
//       // If it's a comma add the number and then increase the resultIndex
//       if (line[i] == ',')
//       {
//         pointResult[resultIndex] = atof(stringNumber.c_str());
//         ++resultIndex;
//         stringNumber = "";
//         continue;
//       }
//       else if (line[i] == ' ') // Don't do anything for a space
//         continue;
//       else
//         stringNumber += line[i]; // Keep adding characters to get the whole number
//     }
//     pointResult[2] = atof(stringNumber.c_str());

//     // Update the properties of the Pose object
//     pose = Pose<double>(pointResult[0], pointResult[1]);
//     // Note: We'll store speed in the orientation angle for now as a workaround
//     // This is not ideal but maintains compatibility with the existing structure
//     pose.orientation = Angle<double>(pointResult[2]);

//     // Add it to the path
//     path.push_back(pose);
//   }

//   pathFile.close();

//   return path;
// }

// int Pursuit::findClosestPoint()
// {
//   double minDistanceIndex = 0;
//   double minDistance = INT_MAX;
//   double distance = 0;
//   Pose<double> robotPose = odometry->getPose();

//   for (int i = 0; i < currentPath.size(); ++i)
//   {
//     distance = robotPose.position.distanceTo(currentPath[i].position);
//     if (distance < minDistance)
//     {
//       minDistanceIndex = i;
//       minDistance = distance;
//     }
//   }

//   return minDistanceIndex;
// }

// double Pursuit::circleIntersect(Vector2D<double> point1, Vector2D<double> point2)
// {
//   Pose<double> robotPose = odometry->getPose();
//   Vector2D<double> d = point2 - point1;
//   Vector2D<double> f = point1 - robotPose.position;

//   double a = d.dot(d);
//   double b = 2 * f.dot(d);
//   double c = f.dot(f) - params.lookAheadDistance * params.lookAheadDistance;
//   double discriminant = b * b - 4 * a * c;

//   // possible solution
//   if (discriminant >= 0)
//   {
//     discriminant = sqrt(discriminant);

//     double t1 = (-b - discriminant) / (2 * a);
//     double t2 = (-b + discriminant) / (2 * a);

//     if (t2 >= 0 && t2 <= 1)
//       return t2;
//     if (t1 >= 0 && t1 <= 1)
//       return t1;
//   }

//   return -1;
// }

// Pose<double> Pursuit::findLookAheadPoint(Vector2D<double> lastLookAhead, int lastLookAheadIndex, int closestPointIndex)
// {
//   // Start as far down the path as possible
//   int startIndex = max(closestPointIndex, lastLookAheadIndex);

//   for (int i = startIndex; i < currentPath.size() - 1; ++i)
//   {
//     Vector2D<double> lastPoint = currentPath[i].position;
//     Vector2D<double> currentPoint = currentPath[i + 1].position;

//     double t = this->circleIntersect(lastPoint, currentPoint);

//     if (t != -1)
//     {
//       Vector2D<double> lookAheadPoint = lerp<double>(lastPoint, currentPoint, t);
//       return Pose<double>(lookAheadPoint);
//     }
//   }

//   // No point found return last look ahead
//   return Pose<double>(lastLookAhead);
// }

// double Pursuit::getCurvature(Vector2D<double> lookaheadPoint)
// {
//   Pose<double> robotPose = odometry->getPose();

//   // what side of the path the robot is on
//   Vector2D<double> normalVector = Vector2D<double>(cos(robotPose.orientation.toRad().angle), sin(robotPose.orientation.toRad().angle));
//   Vector2D<double> delta = lookaheadPoint - robotPose.position;
//   double side = sgn<double>(delta.crossProduct(normalVector));

//   double a = -tan(robotPose.orientation.toRad().angle);
//   double c = tan(robotPose.orientation.toRad().angle) * robotPose.position.x - robotPose.position.y;

//   // horizontal distance to the look ahead point
//   double x = fabs(a * lookaheadPoint.x + lookaheadPoint.y + c) / sqrt((a * a) + 1);
//   double d = robotPose.position.distanceTo(lookaheadPoint);

//   return side * ((2 * x) / (d * d));
// }

// // TODO: Make the full state feedback function go slower if the robot is off the path
// double Pursuit::fullStateFeedback(Vector2D<double> target, double targetVelocity, double currentVelocity)
// {
//   Pose<double> robotPose = odometry->getPose();
//   double positionError = robotPose.position.distanceTo(target);
//   double velocityError = targetVelocity - currentVelocity;

//   return (params.kP * positionError) + (params.kV * velocityError);
// }

// void Pursuit::followPath(Path path)
// {
//   currentPath = path;
//   Pose<double> lastPointOnPath = currentPath[currentPath.size() - 1];
//   Pose<double> closestPoint;
//   Pose<double> lookAheadPoint;
//   Vector2D<double> lastLookAheadPoint = currentPath[0].position;
//   int lastLookAheadPointIndex = 0;

//   double curvature;
//   double targetVelocity;
//   double previousTargetVelocity = 0;
//   double leftTargetVelocity;
//   double rightTargetVelocity;

//   // Used in the wait() function at the end of each loop iteration
//   double waitTime = 20;

//   timer pursuitTimer;
//   pursuitTimer.clear();

//   for (int i = 0; true; ++i)
//   {
//     // Check timeout
//     if (pursuitTimer.time(timeUnits::msec) > params.timeout)
//     {
//       cout << "Pure Pursuit timed out" << endl;
//       break;
//     }

//     // Get the closest point on the path
//     int closestPointIndex = this->findClosestPoint();
//     closestPoint = currentPath[closestPointIndex];

//     // Check if we've reached a stop point (using orientation angle as speed storage)
//     if (closestPoint.orientation.angle == 0)
//     {
//       cout << "Exiting Pure Pursuit curve" << endl;
//       break;
//     }

//     // Get the point where the circle intersects
//     lookAheadPoint = this->findLookAheadPoint(lastLookAheadPoint, lastLookAheadPointIndex, closestPointIndex);

//     if (lookAheadPoint.position == lastLookAheadPoint)
//     {
//       wait(waitTime, vex::timeUnits::msec);
//       continue;
//     }

//     // Get the curvature of the path
//     curvature = this->getCurvature(lookAheadPoint.position);

//     // Calculate the velocities
//     targetVelocity = closestPoint.orientation.angle; // Speed stored in orientation angle
//     targetVelocity = this->fullStateFeedback(lookAheadPoint.position, closestPoint.orientation.angle, previousTargetVelocity);

//     // Apply slew rate limiting
//     targetVelocity = slew<double>(targetVelocity, previousTargetVelocity, params.slewGain);

//     // Calculate the target speeds for the motors (assuming trackWidth is available)
//     double trackWidth = 12.0; // Default value, should be configured properly
//     leftTargetVelocity = targetVelocity * (2 + curvature * trackWidth) / 2;
//     rightTargetVelocity = targetVelocity * (2 - curvature * trackWidth) / 2;

//     previousTargetVelocity = targetVelocity;

//     // Normalize velocities if they exceed maximum
//     double maxVel = max(fabs(leftTargetVelocity), fabs(rightTargetVelocity));
//     if (maxVel > 100)
//     {
//       leftTargetVelocity = (leftTargetVelocity / maxVel) * 100;
//       rightTargetVelocity = (rightTargetVelocity / maxVel) * 100;
//     }

//     // Apply motor velocities using the chassis motor velocities method
//     Pair motorVoltages = getMotorVelocities(targetVelocity, curvature * targetVelocity);

//     // TODO: We need to implement proper motor control here
//     // This is a placeholder as the motor control interface needs to be defined

//     lastLookAheadPoint = lookAheadPoint.position;
//     lastLookAheadPointIndex = closestPointIndex;

//     wait(waitTime, vex::timeUnits::msec);
//   }

//   cout << "Exited Pure Pursuit Curve. Final Position:" << endl;
//   Pose<double> finalPose = odometry->getPose();
//   cout << finalPose.position.x << ", " << finalPose.position.y << endl;
// }