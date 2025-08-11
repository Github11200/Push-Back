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
  double turnMinVoltage = 1;
  double turnMaxVoltage = 1;
  double turnSettleError = 1;
  double turnSettleTime = 1;
  double turnTimeout = 1;
  double turnKp = 1;
  double turnKi = 1;
  double turnKd = 1;
  double turnStopIntegratingLimit = 1;
  double turnSlew = 12; // by default the turn slew will be disabled

  TurnParams() = default;
};

struct DriveParams
{
  double driveMinVoltage = 1;
  double driveMaxVoltage = 1;
  double driveSettleError = 1;
  double driveSettleTime = 1;
  double driveTimeout = 1;
  double driveKp = 1;
  double driveKi = 1;
  double driveKd = 1;
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

#endif