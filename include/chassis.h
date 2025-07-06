#ifndef CHASSIS_H
#define CHASSIS_H

#include "vex.h"

using namespace vex;
using namespace std;

class chassis
{
private:
  /* data */
public:
  chassis(/* args */);

  void driveDistance();
  void driveToPoint();
  void driveToPose();

  void turnToAngle();
  void turnToPoint();

  ~chassis();
};

#endif