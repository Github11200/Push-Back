#ifndef PARAMS_H
#define PARAMS_H

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
  double driveMinVoltage = 0; // turn up for motion chaining
  double driveMaxVoltage = 12; // preferably don't change, will make bot slower
  double driveSettleError = 1; // make it like 0.01 for pid tuning
  double driveSettleTime = 200;
  double driveTimeout = 100000; // insanely high value for pid tuning
  double driveKp = 500; // tune first
  double driveKi = 0; // tune third
  double driveKd = 0; // tune second
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

inline DriveParams fastDriveParams()
{
  DriveParams driveParams;
  driveParams.driveMinVoltage = 0.3;
  driveParams.driveMaxVoltage = 10;
  driveParams.driveSettleError = 0.5;
  driveParams.driveSettleTime = 150;
  driveParams.driveTimeout = 80000;
  driveParams.driveKp = 0.5;
  driveParams.driveKi = 0.1;
  driveParams.driveKd = 5;
  driveParams.driveStopIntegratingLimit = 0.8;
  driveParams.driveSlew = 15;
  return driveParams;
}

inline DriveParams slowDriveParams()
{
  DriveParams driveParams;
  driveParams.driveMinVoltage = 0.2;
  driveParams.driveMaxVoltage = 8;
  driveParams.driveSettleError = 2;
  driveParams.driveSettleTime = 300;
  driveParams.driveTimeout = 120000;
  driveParams.driveKp = 0.2;
  driveParams.driveKi = 0.05;
  driveParams.driveKd = 0.3;
  driveParams.driveStopIntegratingLimit = 1.2;
  driveParams.driveSlew = 8;
  return driveParams;
}

inline TurnParams fastTurnParams()
{
  TurnParams turnParams;
  turnParams.turnMinVoltage = 0.2;
  turnParams.turnMaxVoltage = 10;
  turnParams.turnSettleError = 0.8;
  turnParams.turnSettleTime = 180;
  turnParams.turnTimeout = 90000;
  turnParams.turnKp = 0.4;
  turnParams.turnKi = 0.02;
  turnParams.turnKd = 0.7;
  turnParams.turnStopIntegratingLimit = 0.9;
  turnParams.turnSlew = 14;
  return turnParams;
}

inline TurnParams slowTurnParams()
{
  TurnParams turnParams;
  turnParams.turnMinVoltage = 0.1;
  turnParams.turnMaxVoltage = 6;
  turnParams.turnSettleError = 1.5;
  turnParams.turnSettleTime = 250;
  turnParams.turnTimeout = 110000;
  turnParams.turnKp = 0.25;
  turnParams.turnKi = 0.01;
  turnParams.turnKd = 0.4;
  turnParams.turnStopIntegratingLimit = 1.3;
  turnParams.turnSlew = 9;
  return turnParams;
}

inline SwingParams fastSwingParams()
{
  SwingParams swingParams;
  swingParams.swingMaxVoltage = 8;
  swingParams.swingSettleError = 0.6;
  swingParams.swingSettleTime = 0.8;
  swingParams.swingTimeout = 0.7;
  swingParams.swingKp = 1.2;
  swingParams.swingKi = 1.1;
  swingParams.swingKd = 1.3;
  swingParams.swingStartI = 0.9;
  return swingParams;
}

inline SwingParams slowSwingParams()
{
  SwingParams swingParams;
  swingParams.swingMaxVoltage = 4;
  swingParams.swingSettleError = 1.2;
  swingParams.swingSettleTime = 1.5;
  swingParams.swingTimeout = 1.8;
  swingParams.swingKp = 0.8;
  swingParams.swingKi = 0.7;
  swingParams.swingKd = 0.9;
  swingParams.swingStartI = 1.2;
  return swingParams;
}

#endif