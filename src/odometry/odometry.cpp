#include "vex.h"
#include "../../include/odometry/odometry.h"

using namespace vex;
using namespace std;

bool trackingOn = false;
double x = 0.0;
double y = 0.0;
double theta = 0.0;

void Odometry::startPositionTrackThread()
{
  trackingOn = true;
}

void Odometry::stopPositionTrackThread()
{
  trackingOn = false;
}

double Odometry::getCurrentXPosition()
{
  return x;
}

double Odometry::getCurrentYPosition()
{
  return y;
}

double Odometry::getAbsoluteHeading()
{
  return theta;
}

void Odometry::updatePosition()
{
}

void Odometry::resetPosition(double xPosition, double yPosition, double theta)
{
}
