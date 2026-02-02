#ifndef MOTION_PROFILE_POSE_H
#define MOTION_PROFILE_POSE_H

template <class T>
struct MotionProfilePose
{
  double time;
  double velocity;
  double acceleration;

  MotionProfilePose() = default;
  MotionProfilePose(double time,
                    double velocity,
                    double acceleration) : time(time),
                                           velocity(velocity),
                                           acceleration(acceleration) {}
};

#endif