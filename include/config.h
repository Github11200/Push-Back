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

  inline constexpr double kDriveWheelDiameters = 3.25;
  inline constexpr double kDriveGearRatio = 36 / static_cast<double>(48);

  inline constexpr double kForwardTrackerInchesToDegreesRatio = (M_PI * kForwardTrackerWheelDiameter) / 360.0;
  inline constexpr double kSidewaysTrackerInchesToDegreesRatio = (M_PI * kSidewaysTrackerWheelDiameter) / 360.0;

  inline constexpr double kMotorsInchesToDegreesRatio = (M_PI * kDriveWheelDiameters * kDriveGearRatio) / 360.0;

  inline constexpr double kForwardTrackerDistance = 0.2516505;
  inline constexpr double kSidewaysTrackerDistance = 4.06826;

  inline constexpr double kFrontDistanceSensorDistance = 8.3175 - 5.4;
  inline constexpr double kLeftDistanceSensorDistance = 6.8845 - 1.45;
  inline constexpr double kRightDistanceSensorDistance = 6.8845 - 0.2;
  inline constexpr double kBackDistanceSensorDistance = 8.3175 - 3.4;

  inline constexpr bool kEnableLogs = true;

  inline constexpr int kSkillsScoreTimeMs = 1100;
  inline constexpr int kSkillsRamTimeMs = 300;
  inline constexpr int kSkillsLoadTimeMs = 2500;
  inline constexpr int kSkillsLoadLoadTimeMs = 0;
}

#endif
