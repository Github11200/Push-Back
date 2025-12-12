#include "utils/logger.h"

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

  void sendMotionStart(MotionType motionType, MotionData data)
  {
    stringstream motionStartString;
    motionStartString << motionTypeEnumToString(motionType)
                      << data.target.position.x
                      << data.target.position.y
                      << data.target.orientation.angle
                      << data.turnParams.turnKp
                      << data.turnParams.turnKi
                      << data.turnParams.turnKd
                      << data.turnParams.turnMaxVoltage;

    // Add in the drive data as well if you are doing a drive to point/pose
    if (motionType == MotionType::DRIVE_TO_POINT || motionType == MotionType::DRIVE_TO_POSE)
    {
      motionStartString << data.driveParams.driveKp
                        << data.driveParams.driveKi
                        << data.driveParams.driveKd
                        << data.driveParams.driveMaxVoltage;
    }

    cout << "motionStart," << motionStartString.str() << "%" << endl;
  }

  void sendMotionData(MotionType motionType, double elapsedTime, double turnError, double driveError)
  {
    stringstream motionDataString;
    motionDataString << motionTypeEnumToString(motionType)
                     << elapsedTime
                     << turnError;

    // If the drive error is a __DBL_MAX__ then it means it's a turn to point or turn to angle which doesn't have drive error
    if (driveError != __DBL_MAX__)
      motionDataString << driveError;
    cout << "motionData," << motionDataString.str() << "%" << endl;
  }

  void sendMotionEnd(double elapsedTime) { cout << "motionEnd," << elapsedTime << "%" << endl; }

  void sendMessage(string message)
  {
    cout << "message," << message << "%" << endl;
  }
};