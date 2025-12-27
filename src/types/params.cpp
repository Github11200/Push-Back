#include "types/params.h"

/*==================================
            Drive Params
==================================*/

DriveParams driveParams5_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.8;
  driveParams.driveKd = 45;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams10_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.6;
  driveParams.driveKd = 0;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  driveParams.driveSlew = 0.05;
  return driveParams;
}
DriveParams driveParams20_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.7;
  driveParams.driveKd = 0;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams30_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 1;
  driveParams.driveKd = 0;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams50_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 1;
  driveParams.driveKd = 0;
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
  turnParams.turnKp = 0.5;
  turnParams.turnKd = 2.5;
  turnParams.turnKi = 0;
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
  turnParams.turnKd = 2.28;
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
  turnParams.turnKd = 1.48;
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