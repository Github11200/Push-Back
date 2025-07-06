#ifndef PARAMS_H
#define PARAMS_H

#include "vex.h"

using namespace vex;
using namespace std;

struct DriveParams
{
  double drive_min_voltage = 1;
  double drive_max_voltage = 1;
  double heading_max_voltage = 1;
  double drive_settle_error = 1;
  double drive_settle_time = 1;
  double drive_timeout = 1;
  double drive_kp = 1;
  double drive_ki = 1;
  double drive_kd = 1;
  double drive_starti = 1;
  double drive_slew = 1;
  double heading_kp = 1;
  double heading_ki = 1;
  double heading_kd = 1;
  double heading_starti = 1;

  DriveParams() = default;
};

struct TurnParams
{
  double turn_max_voltage = 1;
  double turn_settle_error = 1;
  double turn_settle_time = 1;
  double turn_timeout = 1;
  double turn_kp = 1;
  double turn_ki = 1;
  double turn_kd = 1;
  double turn_starti = 1;

  TurnParams() = default;
};

struct SwingParams
{
  double swing_max_voltage = 1;
  double swing_settle_error = 1;
  double swing_settle_time = 1;
  double swing_timeout = 1;
  double swing_kp = 1;
  double swing_ki = 1;
  double swing_kd = 1;
  double swing_starti = 1;

  SwingParams() = default;
};

#endif