struct TurnParams
{
  double turnMinVoltage = 0;
  double turnMaxVoltage = 12;
  double turnSettleError = 0.01;
  double turnSettleTime = 1000;
  double turnTimeout = 10000;
  double turnKp = 1;
  double turnKi = 0;
  double turnKd = 0;
  double turnStopIntegratingLimit = 0;
  double turnSlew = 12;

  TurnParams() = default;
};

struct DriveParams
{
  double driveMinVoltage = 0;
  double driveMaxVoltage = 12;
  double driveSettleError = 0.01;
  double driveSettleTime = 1000;
  double driveTimeout = 10000;
  double driveKp = 1;
  double driveKi = 0;
  double driveKd = 0;
  double driveStopIntegratingLimit = 2;
  double driveSlew = 12;

  DriveParams() = default;
};