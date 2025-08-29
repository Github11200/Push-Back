#ifndef LOGGER_H
#define LOGGER_H

#include "vex.h"
#include "types/pose.h"
#include "types/params.h"

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
    TURN_TO_POINT = 2,
    TURN_TO_ANGLE = 3,
    PURSUIT = 4
  };

  struct MotionData
  {
    MotionType motionType;
    Pose<double> target;
    DriveParams driveParams;
    TurnParams turnParams;
  };

  std::string messageTypeEnumToString(MessageType messageType);
  std::string motionTypeEnumToString(MotionType motionType);

  void sendPositionData(Pose<double> &currentPose);

  void sendMotionStart(MotionType motionType, Pose<double> target, MotionData data);

  void sendMotionData(MotionType motionType, double elapsedTime, double turnError, double driveError = __DBL_MAX__);
  void sendMotionEnd(double elapsedTime);

  void sendMessage(std::string message);

};

#endif