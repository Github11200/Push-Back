#include "../../include/odometry/odometry.h"
#include "../../include/chassis.h"

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
  this->distanceSensorDistances.push_back(backDistanceSensorDistance);
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
  case DistanceSensor::STERN:
    return backDistance;
  default:
    break;
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
    return TrackerPositions(-chassis->getForwardTrackerPosition(), chassis->getSidewaysTrackerPosition());
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
                                        wait(10, msec);
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

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(0, 0);
  Brain.Screen.newLine();
  Brain.Screen.print("X: %.3f", currentPose.position.x);
  Brain.Screen.newLine();
  Brain.Screen.print("Y: %.3f", currentPose.position.y);
  Brain.Screen.newLine();
  Brain.Screen.print("Theta: %.3f", currentPose.orientation.angle);

  if (i == 50)
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
  chassis->Inertial.setRotation(theta, deg);
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

void Odometry::getWheelDistances()
{
  chassis->resetEncoders();
  Logger::sendMessage("Starting wheel distances test...");
  Logger::sendMessage("Turn the robot around 10 times.");

  while (!Controller.ButtonA.pressing())
    wait(20, msec);

  double forwardTrackerDelta = getTrackersPositions().forward;
  double sidewaysTrackerDelta = getTrackersPositions().sideways;

  double forwardTrackerDistanceFromCenter = -(forwardTrackerDelta / 1800);
  double sidewaysTrackerDistanceFromCenter = -(sidewaysTrackerDelta / 1800);

  cout << "Forward tracker delta: " << forwardTrackerDelta << "\n"
       << "Sideways tracker delt: " << sidewaysTrackerDelta << "\n"
       << "Forward tracker distance from center: " << forwardTrackerDistanceFromCenter << "\n"
       << "Sideways tracker distance from center: " << sidewaysTrackerDistanceFromCenter << endl;
}