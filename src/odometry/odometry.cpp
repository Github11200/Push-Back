#include "odometry/odometry.h"
#include "chassis.h"

using namespace vex;
using namespace std;

Odometry::Odometry(Chassis *chassis,
                   double forwardTrackerCenterDistance,
                   double sidewaysTrackerDistance,
                   double frontDistanceSensorDistance,
                   double rightDistanceSensorDistance,
                   double leftDistanceSensorDistance,
                   double backDistanceSensorDistance,
                   TrackerSetup trackerSetup)
{
  this->chassis = chassis;
  this->trackerSetup = TWO_TRACKER;
  this->forwardTrackerCenterDistance = forwardTrackerCenterDistance;
  this->sidewaysTrackerCenterDistance = sidewaysTrackerDistance;
  this->trackerSetup = trackerSetup;

  this->distanceSensorDistances.push_back(frontDistanceSensorDistance);
  this->distanceSensorDistances.push_back(rightDistanceSensorDistance);
  this->distanceSensorDistances.push_back(leftDistanceSensorDistance);
  // this->distanceSensorDistances.push_back(backDistanceSensorDistance);
}

Odometry::~Odometry()
{
  delete chassis;
}

vex::distance Odometry::getDistanceSensor(DistanceSensor distanceSensor)
{
  switch (distanceSensor)
  {
  case DistanceSensor::FORWARD:
    return frontDistance;
  case DistanceSensor::PORT:
    return leftDistance;
  case DistanceSensor::STARBOARD:
    return rightDistance;
  // case DistanceSensor::STERN:
  //   return backDistance;
  default:
    return rightDistance;
  }
}

TrackerPositions Odometry::getTrackersPositions()
{
  switch (this->trackerSetup)
  {
  case ZERO_TRACKER:
    return TrackerPositions((chassis->getMotorsPosition().right + chassis->getMotorsPosition().left) / 2, 0);
  case FORWARD_TRACKER:
    return TrackerPositions(chassis->getForwardTrackerPosition(), 0);
  case SIDEWAYS_TRACKER:
    return TrackerPositions(chassis->getMotorsPosition().right, chassis->getSidewaysTrackerPosition());
  case TWO_TRACKER:
    return TrackerPositions(chassis->getForwardTrackerPosition(), chassis->getSidewaysTrackerPosition());
  default:
    return TrackerPositions(-1, -1);
  }
}

void Odometry::startPositionTrackThread(bool sendLogs)
{
  static Odometry *odometryPointer = this;
  static bool staticSendLogs = sendLogs;

  isTracking = true;
  previousHeading = Angle<double>(chassis->getAbsoluteHeading().toRad());
  previousTrackerPositions = TrackerPositions(0, 0);
  Brain.Screen.setPenWidth(10);

  positionTrackThread = new thread([]()
                                   {
                                      while (odometryPointer->isTracking) {
                                        odometryPointer->updatePosition(staticSendLogs);
                                        wait(5, msec);
                                      } });
}

void Odometry::stopPositionTrackThread()
{
  isTracking = false;
  positionTrackThread->join();
  delete positionTrackThread;
}

void Odometry::pausePositionTrackThread() { this->pauseOdom = true; }
void Odometry::resumePositionTrackThread() { this->pauseOdom = false; }

Pose<double> Odometry::getPose() { return currentPose; }

void Odometry::updatePosition(bool sendLogs)
{
  static int i = 0;
  TrackerPositions trackerPosition = getTrackersPositions();
  Angle<double> absoluteHeading = chassis->getAbsoluteHeading().toRad();

  double forwardTrackerDelta = trackerPosition.forward - previousTrackerPositions.forward;
  double sidewaysTrackerDelta = trackerPosition.sideways - previousTrackerPositions.sideways;
  Angle<double> deltaTheta = absoluteHeading - previousHeading;

  Vector2D<double> localTranslation;
  Vector2D<double> globalTranslation;

  if (deltaTheta.angle == 0.0)
  {
    localTranslation.x = sidewaysTrackerDelta;
    localTranslation.y = forwardTrackerDelta;
  }
  else
  {
    double length = 2 * sin(deltaTheta.angle / 2);

    localTranslation.x = length * ((sidewaysTrackerDelta / deltaTheta.angle) + sidewaysTrackerCenterDistance);
    localTranslation.y = length * ((forwardTrackerDelta / deltaTheta.angle) + forwardTrackerCenterDistance);
  }

  // Polar coordinates
  double polarLength = 0;
  double polarAngle = 0;

  if (localTranslation.x == 0 && localTranslation.y == 0)
  {
    polarLength = 0;
    polarAngle = 0;
  }
  else
  {
    polarLength = hypot(localTranslation.x, localTranslation.y);
    polarAngle = atan2(localTranslation.y, localTranslation.x);
  }

  double globalPolarAngle = polarAngle - previousHeading.angle - (deltaTheta.angle / 2);

  // Global translation
  globalTranslation.x = polarLength * cos(globalPolarAngle);
  globalTranslation.y = polarLength * sin(globalPolarAngle);

  currentPose.position.x += globalTranslation.x;
  currentPose.position.y += globalTranslation.y;
  currentPose.orientation = absoluteHeading.toDeg();

  if (!sendLogs)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(0, 0);
    Brain.Screen.newLine();
    Brain.Screen.print("X: %.3f", currentPose.position.x);
    Brain.Screen.newLine();
    Brain.Screen.print("Y: %.3f", currentPose.position.y);
    Brain.Screen.newLine();
    Brain.Screen.print("Theta: %.3f", currentPose.orientation.angle);
  }

  if (sendLogs && i == 50)
  {
    i = 0;
    if (sendLogs)
      Logger::sendPositionData(currentPose);
  }
  ++i;

  previousTrackerPositions = trackerPosition;
  previousHeading = absoluteHeading;
}

void Odometry::setPosition(double xPosition, double yPosition, double theta)
{
  currentPose.position.x = xPosition;
  currentPose.position.y = yPosition;
  Inertial.setRotation(theta, deg);
  currentPose.orientation.angle = theta;
}

void Odometry::wallReset(DistanceSensor distanceSensor, Wall wall)
{
  double angle = this->currentPose.orientation.constrainNegative90To90().toRad().angle;
  vex::distance sensor = getDistanceSensor(distanceSensor);
  double distanceToTrackingCenter = distanceSensorDistances[distanceSensor];

  if (!sensor.isObjectDetected())
  {
    Logger::sendMessage("Could not detect wall. Not resetting.");
    return;
  }

  double distanceSensorReading = sensor.objectDistance(vex::distanceUnits::in) + distanceToTrackingCenter;
  cout << sensor.objectDistance(vex::distanceUnits::in) << endl;
  int sign = (wall == Wall::FRONT || wall == Wall::RIGHT) ? 1 : -1;
  double distance = (70.31 - (cos(angle) * distanceSensorReading)) * sign;

  if (wall == Wall::FRONT || wall == Wall::REAR)
    this->currentPose.position.y = distance;
  else if (wall == Wall::RIGHT || wall == Wall::LEFT)
    this->currentPose.position.x = distance;
}

void Odometry::getWheelOffsets()
{
  // int iterations = 5;
  // double forwardOffset = 0;
  // double sidewaysOffset = 0;

  // for (int i = 1; i <= iterations; ++i)
  // {
  //   chassis->resetEncoders();
  //   setPosition(0, 0, 0);
  //   Angle<double> initialTheta = chassis->getAbsoluteHeading();

  //   double target = i % 2 == 0 ? 90 : 270;
  //   chassis->turnTo(Pose<double>(0, 0, target), {.turnMaxVoltage = 6, .turnSettleError = 1}, {});
  //   wait(250, msec);

  //   Angle<double> deltaTheta = Angle<double>(fabs((chassis->getAbsoluteHeading() - initialTheta).constrainNegative180To180().angle)).toRad();
  //   // cout << deltaTheta.toDeg().angle << endl;

  //   double forwardDelta = chassis->getForwardTrackerPosition();
  //   double sidewaysDelta = chassis->getSidewaysTrackerPosition();
  //   // cout << "sidewaysDelta: " << fabs(sidewaysDelta) / deltaTheta.angle << endl;

  //   forwardOffset += fabs(forwardDelta) / deltaTheta.angle;
  //   sidewaysOffset += fabs(sidewaysDelta) / deltaTheta.angle;
  //   // cout << "Forward offset: " << (forwardOffset) << endl;
  //   cout << "total: " << (sidewaysOffset) << endl;
  //   cout << "offset: " << (sidewaysOffset / i) << endl;
  // }

  // cout << "Forward offset: " << (forwardOffset / iterations) << endl;
  // cout << "Sideways offset: " << (sidewaysOffset / iterations) << endl;

  int iterations = 5;
  double forwardTrackerOffsets = 0;
  double sidewaysTrackerOffsets = 0;

  for (int i = 0; i < iterations; ++i)
  {
    chassis->resetEncoders();
    Logger::sendMessage("Spin the robot 360 degrees slowly. Press A when you are done.");

    while (!Controller.ButtonA.pressing())
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(0, 0);
      Brain.Screen.newLine();
      Brain.Screen.print("Theta: %.3f", chassis->getAbsoluteHeading().angle);
      wait(50, msec);
    }
    wait(500, msec);

    TrackerPositions trackerPositions = getTrackersPositions();
    cout << "Forward: " << trackerPositions.forward << endl;
    cout << "Sideways: " << trackerPositions.sideways << endl;
    forwardTrackerOffsets += (trackerPositions.forward) / (2 * M_PI);
    sidewaysTrackerOffsets += (trackerPositions.sideways) / (2 * M_PI);

    if (i + 1 == iterations)
      break;

    Logger::sendMessage("Distances have been recorded, reset the bot, and press A when you are ready.");
    while (!Controller.ButtonA.pressing())
      wait(50, msec);
    wait(500, msec);
  }

  ostringstream stringStream;
  stringStream << "Forward tracker offsets: " << (forwardTrackerOffsets / iterations) << endl;
  stringStream << "Sideways tracker offsets: " << (sidewaysTrackerOffsets / iterations) << endl;
  Logger::sendMessage(stringStream.str());
}

// Forward tracker - 0, sideways - 1
void Odometry::getWheelDiameters(int forwardOrSidewaysTracker, double currentWheelDiameter)
{
  int iterations = 5;
  double totalDistanceTravelled = 0;

  for (int i = 0; i < iterations; ++i)
  {
    chassis->resetEncoders();
    Logger::sendMessage("Move the robot 20 inches.");
    while (!Controller.ButtonA.pressing())
      wait(50, msec);
    wait(500, msec);

    double trackerPosition = (forwardOrSidewaysTracker == 0 ? ForwardTracker : SidewaysTracker).position(vex::rotationUnits::deg);
    totalDistanceTravelled += ((M_PI * currentWheelDiameter) / 360) * trackerPosition;

    if (i + 1 == iterations)
      break;

    Logger::sendMessage("Distance recorded, reset the position, and press A to continue.");
    while (!Controller.ButtonA.pressing())
      wait(50, msec);
    wait(500, msec);
  }

  double averagedDistance = totalDistanceTravelled / iterations;
  double newWheelDiameter = (20 / averagedDistance) * currentWheelDiameter;

  ostringstream stringStream;
  stringStream << "New wheel diameter: " << newWheelDiameter;
  Logger::sendMessage(stringStream.str());
}

// 2.72419 - Wheel diameter with 2 iterations
// 2.71598 - Wheel diameter with 5 iterations
// 2.7175 - Wheel diameter with 5 iterations using the value from above
// 2.71146 - Wheel diameter with 5 iterations using the value from above

// 2.00273 - Wheel diameter with 5 iterations
// 2.00671 - Wheel diameter with 5 iterations

// First run - 3 iterations
// Forward offsets --> 0.195881
// Sideways offsets --> -4.91426

// Second run - 5 iterations
// Forward offsets --> 0.185003
// Sideways offsets --> -4.90956

// Third run - 5 iterations
// Forward offsets --> 0.0939232
// Sideways offsets --> -4.90447

// Fourth run - 5 iterations
// Forward offsets --> 0.0389147
// Sideways offsets --> -4.90045

// Fifth run - 5 iterations
// Forward offsets --> 0.260887
// Sideways offsets --> -4.89781