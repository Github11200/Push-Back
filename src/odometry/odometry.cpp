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

void Odometry::startPositionTrackThread()
{
  static Odometry *odometryPointer = this;

  isTracking = true;
  previousHeading = Angle<double>(0);
  previousTrackerPositions = TrackerPositions(0, 0);
  positionTrackThread = new thread([]()
                                   {
                                      while (odometryPointer->isTracking) {
                                        odometryPointer->updatePosition();
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

void Odometry::updatePosition()
{
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

  previousTrackerPositions = trackerPosition;
  previousHeading = absoluteHeading;
}

void Odometry::setPosition(double xPosition, double yPosition, double theta)
{
  currentPose.position.x = xPosition;
  currentPose.position.y = yPosition;
  currentPose.orientation.angle = theta;
}
