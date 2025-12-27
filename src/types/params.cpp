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
  driveParams.driveKd = 32.5;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  driveParams.driveSlew = 1;
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
  turnParams.turnKp = 0.36;
  turnParams.turnKd = 0.55;
  turnParams.turnKi = 0.0005;
  turnParams.turnStartIntegratingLimit = 1;
  return turnParams;
}
TurnParams turnParams30_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.35;
  turnParams.turnKd = 20;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams45_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.34;
  turnParams.turnKd = 21.5;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams60_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.34;
  turnParams.turnKd = 23;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams90_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.34;
  turnParams.turnKd = 25.5;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams135_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.34;
  turnParams.turnKd = 28;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams180_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.34;
  turnParams.turnKd = 32;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}