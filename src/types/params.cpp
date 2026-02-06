#include "types/params.h"
#include "types/vector.h"
#include "utils/interpLUT.h"

/*==================================
            Drive Params
==================================*/

DriveParams driveParams5_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.928;
  driveParams.driveKd = 5.9;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams10_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.87;
  driveParams.driveKd = 4.1;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams20_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.592;
  driveParams.driveKd = 2;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams30_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.51;
  driveParams.driveKd = 2;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams50_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.456;
  driveParams.driveKd = 2;
  driveParams.driveKi = 0;
  driveParams.driveStartIntegratingLimit = 0;
  return driveParams;
}
DriveParams driveParams100_in()
{
  DriveParams driveParams;
  driveParams.driveKp = 0.4;
  driveParams.driveKd = 2;
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
  turnParams.turnKp = 0.5185;
  turnParams.turnKd = 2.2;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams30_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.33;
  turnParams.turnKd = 2.075;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams45_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.33;
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
  turnParams.turnKp = 0.27;
  turnParams.turnKd = 1.9;
  turnParams.turnKi = 0;
  turnParams.turnStartIntegratingLimit = 0;
  return turnParams;
}
TurnParams turnParams135_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.192;
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

vector<Vector2D<double>> turnParamsKp = {
    Vector2D<double>(10, turnParams10_deg().turnKp),
    Vector2D<double>(30, turnParams30_deg().turnKp),
    Vector2D<double>(45, turnParams45_deg().turnKp),
    Vector2D<double>(60, turnParams60_deg().turnKp),
    Vector2D<double>(90, turnParams90_deg().turnKp),
    Vector2D<double>(135, turnParams135_deg().turnKp),
    Vector2D<double>(180, turnParams180_deg().turnKp)};

vector<Vector2D<double>> turnParamsKi = {
    Vector2D<double>(10, turnParams10_deg().turnKi),
    Vector2D<double>(30, turnParams30_deg().turnKi),
    Vector2D<double>(45, turnParams45_deg().turnKi),
    Vector2D<double>(60, turnParams60_deg().turnKi),
    Vector2D<double>(90, turnParams90_deg().turnKi),
    Vector2D<double>(135, turnParams135_deg().turnKi),
    Vector2D<double>(180, turnParams180_deg().turnKi)};

vector<Vector2D<double>> turnParamsKd = {
    Vector2D<double>(10, turnParams10_deg().turnKd),
    Vector2D<double>(30, turnParams30_deg().turnKd),
    Vector2D<double>(45, turnParams45_deg().turnKd),
    Vector2D<double>(60, turnParams60_deg().turnKd),
    Vector2D<double>(90, turnParams90_deg().turnKd),
    Vector2D<double>(135, turnParams135_deg().turnKd),
    Vector2D<double>(180, turnParams180_deg().turnKd)};

vector<Vector2D<double>> driveParamsKp = {
    Vector2D<double>(5, driveParams5_in().driveKp),
    Vector2D<double>(10, driveParams10_in().driveKp),
    Vector2D<double>(20, driveParams20_in().driveKp),
    Vector2D<double>(30, driveParams30_in().driveKp),
    Vector2D<double>(50, driveParams50_in().driveKp),
    Vector2D<double>(100, driveParams100_in().driveKp)};

vector<Vector2D<double>> driveParamsKi = {
    Vector2D<double>(5, driveParams5_in().driveKi),
    Vector2D<double>(10, driveParams10_in().driveKi),
    Vector2D<double>(20, driveParams20_in().driveKi),
    Vector2D<double>(30, driveParams30_in().driveKi),
    Vector2D<double>(50, driveParams50_in().driveKi),
    Vector2D<double>(100, driveParams100_in().driveKi)};

vector<Vector2D<double>> driveParamsKd = {
    Vector2D<double>(5, driveParams5_in().driveKd),
    Vector2D<double>(10, driveParams10_in().driveKd),
    Vector2D<double>(20, driveParams20_in().driveKd),
    Vector2D<double>(30, driveParams30_in().driveKd),
    Vector2D<double>(50, driveParams50_in().driveKd),
    Vector2D<double>(100, driveParams100_in().driveKd)};

InterpolatedLUT turnParamsKpLUT(turnParamsKp);
InterpolatedLUT turnParamsKiLUT(turnParamsKi);
InterpolatedLUT turnParamsKdLUT(turnParamsKd);

InterpolatedLUT driveParamsKpLUT(driveParamsKp);
InterpolatedLUT driveParamsKiLUT(driveParamsKi);
InterpolatedLUT driveParamsKdLUT(driveParamsKd);

void modifyTurnParams(double turnError, TurnParams &params)
{
  params.turnKp = turnParamsKpLUT.interpolate(turnError);
  params.turnKi = turnParamsKiLUT.interpolate(turnError);
  params.turnKd = turnParamsKdLUT.interpolate(turnError);
}

void modifyDriveParams(double driveError, DriveParams &params)
{
  params.driveKp = driveParamsKpLUT.interpolate(driveError);
  params.driveKi = driveParamsKiLUT.interpolate(driveError);
  params.driveKd = driveParamsKdLUT.interpolate(driveError);
}