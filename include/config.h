#ifndef CONFIG_H
#define CONFIG_H

#include "odometry/odometry.h"

#include <cmath>

namespace Config
{
  inline constexpr double kInertialScaling = 359.8;
  inline constexpr TrackerSetup kTrackerSetup = TrackerSetup::TWO_TRACKER;

  inline constexpr double kForwardTrackerWheelDiameter = 2.749489;
  inline constexpr double kSidewaysTrackerWheelDiameter = 1.97717;

  inline constexpr double kDriveWheelDiameters = 3.25;
  inline constexpr double kDriveGearRatio = 36 / static_cast<double>(48);

  inline constexpr double kForwardTrackerInchesToDegreesRatio = (M_PI * kForwardTrackerWheelDiameter) / 360.0;
  inline constexpr double kSidewaysTrackerInchesToDegreesRatio = (M_PI * kSidewaysTrackerWheelDiameter) / 360.0;

  inline constexpr double kMotorsInchesToDegreesRatio = (M_PI * kDriveWheelDiameters * kDriveGearRatio) / 360.0;

  inline constexpr double kForwardTrackerDistance = 0.249837;
  inline constexpr double kSidewaysTrackerDistance = 2.99544;

  // Get the tracking center then subtract the distance sensor reading from that
  inline constexpr double kFrontDistanceSensorDistance = 14 - 2;
  inline constexpr double kLeftDistanceSensorDistance = 14 - 2;
  inline constexpr double kRightDistanceSensorDistance = 14 - 2;

  inline constexpr bool kEnableLogs = true;

  // Set to true to enable controller-driven PID tuning via TuningUtil::run().
  // When true, usercontrol enters tuning mode instead of normal driver operation.
  inline constexpr bool kTuningMode = false;

  inline constexpr int kSkillsScoreTimeMs = 1100;
  inline constexpr int kSkillsRamTimeMs = 300;
  inline constexpr int kSkillsLoadTimeMs = 2500;
  inline constexpr int kSkillsLoadLoadTimeMs = 0;
}

#endif
