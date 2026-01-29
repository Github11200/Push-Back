#ifndef PARAMS_H
#define PARAMS_H

#include "utils/bezier.h"

struct Settings
{
  int updateTime = 10;
  bool forwards = true;
  bool sendPositionData = false;

  Settings() = default;
};

struct TurnParams
{
  double turnMinVoltage = 0;
  double turnMaxVoltage = 12;
  double turnSettleError = 1;
  double turnSettleTime = 500;
  double turnTimeout = 2000;
  double turnKp = 1;
  double turnKi = 0;
  double turnKd = 0;
  double turnStartIntegratingLimit = 0;
  double turnSlew = 12;

  TurnParams() = default;
};

struct DriveParams
{
  double driveMinVoltage = 0;
  double driveMaxVoltage = 12;
  double driveSettleError = 0.5;
  double driveSettleTime = 500;
  double driveTimeout = 4000;
  double driveKp = 1;
  double driveKi = 0;
  double driveKd = 0;
  double driveStartIntegratingLimit = 2;
  double driveSlew = 0.3;

  DriveParams() = default;
};

struct SwingParams
{
  double swingMaxVoltage = 1;
  double swingSettleError = 1;
  double swingSettleTime = 1;
  double swingTimeout = 1;
  double swingKp = 1;
  double swingKi = 1;
  double swingKd = 1;
  double swingStartI = 1;

  SwingParams() = default;
};

struct PursuitParams
{
  bool forward;
  double lookAheadDistance = 1;
  double slewGain = 1;
  double timeout = 1;
  double kP = 1;
  double kV = 1;
};

struct MotionProfile
{
  double maximumVelocity = 10;
  double finalVelocity = 0;
  double maximumAcceleration = 5;
  double kA = 0.1;
};

struct CurvedMotionProfile : MotionProfile
{
  CubicBezier curve;
  double dt;
};

DriveParams driveParams5_in();
DriveParams driveParams10_in();
DriveParams driveParams20_in();
DriveParams driveParams30_in();
DriveParams driveParams50_in();
DriveParams driveParams100_in();

TurnParams turnParams10_deg();
TurnParams turnParams30_deg();
TurnParams turnParams45_deg();
TurnParams turnParams60_deg();
TurnParams turnParams90_deg();
TurnParams turnParams135_deg();
TurnParams turnParams180_deg();

#endif