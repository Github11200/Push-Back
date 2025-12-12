// #include "chassis.h"

// using namespace std;
// using namespace vex;

// void Chassis::driveWithDistanceSensor(double finalDistance, double heading, DriveParams driveParams, TurnParams turnParams, Settings settings)
// {
//   PID drivePID(settings.updateTime, driveParams);
//   PID turnPID(settings.updateTime, turnParams);

//   while (!drivePID.isSettled())
//   {
//     double error = frontDistance.objectDistance(vex::distanceUnits::in) - finalDistance;
//     Angle<double> turnError = odometry->getPose().orientation.angleTo(heading);

//     double driveOutput = drivePID.compute(error);
//     double turnOutput = turnPID.compute(turnError.angle);

//     driveOutput = clamp<double>(driveOutput, driveParams.driveMinVoltage, driveParams.driveMaxVoltage);
//     turnOutput = clamp<double>(turnOutput, turnParams.turnMinVoltage, turnParams.turnMaxVoltage);

//     Pair motorOutputs = getMotorVelocities(driveOutput, turnOutput);
//     Left.spin(fwd, motorOutputs.left, volt);
//     Right.spin(fwd, motorOutputs.right, volt);

//     wait(settings.updateTime, msec);
//   }

//   Left.stop(brake);
//   Right.stop(brake);
// }