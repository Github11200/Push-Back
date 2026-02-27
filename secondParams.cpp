TurnParams turnParams10_deg()
{
  TurnParams turnParams;
  turnParams.turnKp = 0.5185;
  turnParams.turnKd = 2.2;
  turnParams.turnKi = 0.01;
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