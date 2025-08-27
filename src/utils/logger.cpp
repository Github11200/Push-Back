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
    case TURN_TO:
      return "turnTo,";
    case PURSUIT:
      return "pursuit,";
    default:
      return "";
    }
  }

  void sendPositionData(Pose<double> &currentPose) { cout << "position," << currentPose.position.x << "," << currentPose.position.y << "," << currentPose.orientation.angle << "%" << endl; }

  void sendMotionStart(MotionType motionType, Pose<double> &target, string &extraParams)
  {
    string motionTypeString = motionTypeEnumToString(motionType);
    cout << "motionStart," << motionTypeString << target.position.x << "," << target.position.y << "," << target.orientation.angle << "," << extraParams << "%";
  }

  void sendMotionEnd(double elapsedTime) { cout << "motionEnd," << elapsedTime << "%"; }

  void sendMessage(string message)
  {
    cout << "message," << message << "%";
  }
};