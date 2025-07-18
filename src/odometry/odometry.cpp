#include "vex.h"
#include "../../include/odometry/odometry.h"

using namespace vex;
using namespace std;

bool trackingOn = false;
double x = 0.0;
double y = 0.0;
double theta = 0.0;

Odometry odometry;

void Odometry::startPositionTrackThread()
{
  trackingOn = true;
}

void Odometry::stopPositionTrackThread()
{
  trackingOn = false;
}

Pose<double> Odometry::getPose()
{
  return currentPose;
}

void Odometry::updatePosition()
{
}

void Odometry::resetPosition(double xPosition, double yPosition, double theta)
{
}
