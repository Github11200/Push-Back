#include "../../include/odometry/odometry.h"
#include "../../include/chassis.h"

using namespace vex;
using namespace std;

Odometry::Odometry(Chassis *chassis, double forwardTrackerCenterDistance, double sidewaysTrackerDistance)
{
  this->chassis = chassis;
  this->trackerSetup = TWO_TRACKER;
  this->forwardTrackerCenterDistance = forwardTrackerCenterDistance;
  this->sidewaysTrackerCenterDistance = sidewaysTrackerDistance;

  this->distanceSensors.push_back(frontDistance);
  this->distanceSensors.push_back(rightDistance);
  this->distanceSensors.push_back(leftDistance);
}

Odometry::~Odometry()
{
  delete chassis;
}

TrackerPositions Odometry::getTrackersPositions()
{
  switch (this->trackerSetup)
  {
  case ZERO_TRACKER:
    return TrackerPositions(chassis->getMotorsPosition().right, 0);
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
  previousHeading = Angle<double>(0);
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

  if (deltaTheta.angle == 0)
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

  // Polar coorinates
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
  currentPose.orientation.angle = theta;
}

Wall Odometry::getWallFacing()
{
  double angle = getPose().orientation.angle;
  if (angle >= 350 && angle <= 10)
    return Wall::FRONT;
  else if (angle >= 80 && angle <= 100)
    return Wall::RIGHT;
  else if (angle >= 170 && angle <= 190)
    return Wall::REAR;
  else if (angle >= 260 && angle <= 280)
    return Wall::LEFT;
}

void Odometry::wallReset(DistanceSensor distanceSensor, Wall wall)
{
  double angle = getPose().orientation.angle;
  vex::distance sensor = distanceSensors[distanceSensor];

  if (!sensor.isObjectDetected())
  {
    Logger::sendMessage("Could not detect wall. Not resetting.");
    return;
  }

  double distanceSensorReading = sensor.objectDistance(vex::distanceUnits::in);
  double angle = this->currentPose.orientation.constrainNegative90To90().toRad().angle;
  int sign = (wall == Wall::FRONT || wall == Wall::RIGHT) ? 1 : -1;
  double distance = (72 - (cos(angle) * distanceSensorReading)) * sign;

  if (wall == Wall::FRONT || Wall::REAR)
    this->currentPose.position.y = distance;
  else if (wall == Wall::RIGHT || wall == Wall::LEFT)
    this->currentPose.position.x = distance;
}