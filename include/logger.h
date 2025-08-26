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

  enum MotionType
  {
    DRIVE_TO_POINT = 0,
    DRIVE_TO_POSE = 1,
    TURN_TO = 2,
    PURSUIT = 3
  };

  std::string messageTypeEnumToString(MessageType messageType);
  std::string motionTypeEnumToString(MotionType motionType);

  void sendPositionData(Pose<double> &currentPose);
  void sendMotionStart(MotionType motionType, Pose<double> target, std::string extraParams);
  void sendMotionEnd(double elapsedTime);
  void sendMessage(std::string message);

};

#endif