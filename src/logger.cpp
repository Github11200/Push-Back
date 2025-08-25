#include "logger.h"

using namespace std;

namespace Logger
{

  string getPrefix(MessageType messageType)
  {
    switch (messageType)
    {
    case POSITION:
      return "position,";
    case MOTION_START:
      return "motionStart,";
    case MOTION_END:
      return "motionEnd,";
    default:
      return "";
    }
  }

  void sendPositionData(Pose<double> currentPose)
  {
    cout << "position," << currentPose.position.x << "," << currentPose.position.y << "," << currentPose.orientation.angle << "%";
  }

  void sendMotionStart() {}
  void sendMotionEnd() {}
  void sendMessage() {}
};