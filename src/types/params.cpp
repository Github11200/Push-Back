#include "types/params.h"

/*==================================
            Drive Params
==================================*/

DriveParams driveParams5_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.9;
  driveParams.driveKd = 5.9;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams10_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.77;
  driveParams.driveKd = 5.3;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams20_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.77;
  driveParams.driveKd = 5.9;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams30_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.51;
  driveParams.driveKd = 4;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams50_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.47;
  driveParams.driveKd = 4;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams100_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.4;
  driveParams.driveKd = 3;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}

/*==================================
            Turn Params
==================================*/

TurnParams turnParams10_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.5098;
  turnParams.turnKd = 2.2;
  turnParams.turnKi = 0.01;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams30_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.35;
  turnParams.turnKd = 2.075;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams45_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.35;
  turnParams.turnKd = 2.3;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams60_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.28;
  turnParams.turnKd = 2;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams90_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.25;
  turnParams.turnKd = 1.9;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams135_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.2;
  turnParams.turnKd = 1.45;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams180_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.175;
  turnParams.turnKd = 1.36;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}

/*

10 inches slowly: 68.64 degrees
10 inches fast: 60.29 degrees

20 inches slowly: 121.72 degrees
20 inches fast: 117.24 degrees

*/