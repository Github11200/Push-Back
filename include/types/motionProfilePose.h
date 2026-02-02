#ifndef MOTION_PROFILE_POSE_H
#define MOTION_PROFILE_POSE_H

#include "types/pose.h"

template <class T>
struct MotionProfilePose
{
  double time;
  Pose<double> pose;
  double velocity;
  double angularVelocity;
  double acceleration;

  MotionProfilePose() = default;
  MotionProfilePose(double time,
                    Pose<double> pose,
                    double velocity,
                    double angularVelocity,
                    double acceleration) : time(time),
                                           pose(pose),
                                           velocity(velocity),
                                           angularVelocity(angularVelocity),
                                           acceleration(acceleration) {}
};

#endif