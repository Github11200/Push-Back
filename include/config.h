#ifndef CONFIG_H
#define CONFIG_H

#include "odometry/odometry.h"

#include <cmath>

namespace Config
{
  inline constexpr double kInertialScaling = 356.418;
  inline constexpr TrackerSetup kTrackerSetup = TrackerSetup::TWO_TRACKER;

  inline constexpr double kForwardTrackerWheelDiameter = 2.72292;
  inline constexpr double kSidewaysTrackerWheelDiameter = 1.98839;

  inline constexpr double kForwardTrackerInchesToDegreesRatio = (M_PI * kForwardTrackerWheelDiameter) / 360.0;
  inline constexpr double kSidewaysTrackerInchesToDegreesRatio = (M_PI * kSidewaysTrackerWheelDiameter) / 360.0;

  inline constexpr double kForwardTrackerDistance = 0.126971;
  inline constexpr double kSidewaysTrackerDistance = 5.38079;

  inline constexpr double kFrontDistanceSensorDistance = 8.3175 - 5.4;
  inline constexpr double kLeftDistanceSensorDistance = 6.8845 - 0.3;
  inline constexpr double kRightDistanceSensorDistance = 6.8845 - 0.2;
  inline constexpr double kBackDistanceSensorDistance = 8.3175 - 3.4;

  inline constexpr bool kEnableLogs = true;

  inline constexpr int kSkillsScoreTimeMs = 1100;
  inline constexpr int kSkillsRamTimeMs = 200;
  inline constexpr int kSkillsLoadTimeMs = 1000;
}

#endif
