#include "../../include/utils/logger.h"

using namespace std;

namespace Logger
{

  string messageTypeEnumToString(MessageType messageType)
  {
    switch (messageType)
    {
    case POSITION:
      return "position,";
    case MOTION_START:
      return "motionStart,";
    case MOTION_END:
      return "motionEnd,";
    case MESSAGE:
      return "message,";
    default:
      return "";
    }
  }

  string motionTypeEnumToString(MotionType motionType)
  {
    switch (motionType)
    {
    case DRIVE_TO_POINT:
      return "driveToPoint,";
    case DRIVE_TO_POSE:
      return "driveToPose,";
    case TURN_TO_POINT:
      return "turnToPoint,";
    case TURN_TO_ANGLE:
      return "turnToAngle,";
    case PURSUIT:
      return "pursuit,";
    default:
      return "";
    }
  }

  void sendPositionData(Pose<double> &currentPose) { cout << "position," << currentPose.position.x << "," << currentPose.position.y << "," << currentPose.orientation.angle << "%" << endl; }

  void sendMotionStart(MotionType motionType, Pose<double> target, MotionData data)
  {
    string motionStartString = motionTypeEnumToString(motionType) +
                               to_string(data.target.position.x) +
                               to_string(data.target.position.y) +
                               to_string(data.target.orientation.angle) +
                               to_string(data.turnParams.Kp) +
                               to_string(data.turnParams.Ki) +
                               to_string(data.turnParams.Kd) +
                               to_string(data.turnParams.turnMaxVoltage);

    // Add in the drive data as well if you are doing a drive to point/pose
    if (data.motionType == MotionType::DRIVE_TO_POINT || data.motionType == MotionType::DRIVE_TO_POSE)
    {
      motionStartString += to_string(data.driveParams.driveKp) +
                           to_string(data.driveParams.driveKi) +
                           to_string(data.driveParams.driveKd) +
                           to_string(data.driveParams.driveMaxVoltage);
    }

    cout << "motionStart," << motionStartString << "%" << endl;
  }

  void sendMotionData(MotionType motionType, double elapsedTime, double turnError, double driveError)
  {
    string motionDataString = motionTypeEnumToString(motionType) +
                              to_string(elapsedTime) +
                              to_string(turnError);

    if (driveError != __DBL_MAX__)
      motionDataString += to_string(driveError);
    cout << "motionData," << motionDataString << "%" << endl;
  }

  void sendMotionEnd(double elapsedTime) { cout << "motionEnd," << elapsedTime << "%" << endl; }

  void sendMessage(string message)
  {
    cout << "message," << message << "%" << endl;
  }
};