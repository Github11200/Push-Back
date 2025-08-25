#ifndef LOGGER_H
#define LOGGER_H

#include "vex.h"
#include "types/pose.h"

namespace Logger
{

  enum MessageType
  {
    POSITION = 0,
    MOTION_START = 1,
    MOTION_END = 2,
    MESSAGE = 3
  };

  std::string getPrefix(MessageType messageType);

  void sendPositionData(Pose<double> currentPose);
  void sendMotionStart(Pose<double> target);
  void sendMotionEnd();
  void sendMessage();
};

#endif