#ifndef PARAMS_H
#define PARAMS_H

struct Settings
{
  // TODO: Make sure this update time is good
  int updateTime = 10;
  bool forwards = true;

  Settings() = default;
};

struct TurnParams
{
  double turnMinVoltage = 0;
  double turnMaxVoltage = 12;
  double turnSettleError = 1;
  double turnSettleTime = 200;
  double turnTimeout = 100000;
  double turnKp = 0.3;
  double turnKi = 0;
  double turnKd = 0.5;
  double turnStopIntegratingLimit = 1;
  double turnSlew = 12; // by default the turn slew will be disabled

  TurnParams() = default;
};

struct DriveParams
{
  double driveMinVoltage = 0.5;
  double driveMaxVoltage = 12;
  double driveSettleError = 1;
  double driveSettleTime = 200;
  double driveTimeout = 100000;
  double driveKp = 0.3;
  double driveKi = 0;
  double driveKd = 0.5;
  double driveStopIntegratingLimit = 1;
  double driveSlew = 12; // by default the drive slew will be disabled

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
  double maximumVelocity = 5;
  double finalVelocity = 0;
  double maximumAcceleration = 0;
  double kA = 0.1;
};

#endif