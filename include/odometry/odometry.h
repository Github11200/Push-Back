#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "types/pose.h"
#include "vex.h"
#include "logger.h"

using namespace vex;
using namespace std;

class Chassis;

struct TrackerPositions
{
  double forward;
  double sideways;

  TrackerPositions() : forward(0), sideways(0) {}
  TrackerPositions(double forward, double sideways) : forward(forward), sideways(sideways) {}
};

enum TrackerSetup
{
  ZERO_TRACKER,
  FORWARD_TRACKER,
  SIDEWAYS_TRACKER,
  TWO_TRACKER
};

/**
 * @brief Gets the current position of the robot using a combination of the Pilons
 * arc tracking strategy and Monte Carlo Localization
 */
class Odometry
{
private:
  Chassis *chassis;

  TrackerPositions previousTrackerPositions;
  Angle<double> previousHeading;

  Pose<double> currentPose;

  thread *positionTrackThread;
  bool isTracking = false;
  TrackerSetup trackerSetup;

  double forwardTrackerCenterDistance;
  double sidewaysTrackerCenterDistance;

public:
  Odometry(Chassis *chassis, double forwardTrackerCenterDistance, double sidewaysTrackerCenterDistance);
  ~Odometry();

  TrackerPositions getTrackersPositions();

  /**
   * @brief Stops the position tracking thread, this function should typically be
   * run when drive control starts
   */
  void startPositionTrackThread();

  /**
   * @brief Starts the position tracking thread, typcially at the start of auton
   *
   */
  void stopPositionTrackThread();

  // Returns the currentPoseVariable
  Pose<double>
  getPose();

  /**
   * @brief Does the odometry math to update position
   * Uses the Pilons arc method outline here: https://wiki.purduesigbots.com/software/odometry
   * Also uses Monte Carlo Localization: https://www.ri.cmu.edu/pub_files/pub1/dellaert_frank_1999_2/dellaert_frank_1999_2.pdf
   * Updates the private x and y position variables which can later be accessed
   */
  void updatePosition();

  /**
   * @brief Resets the robot position, usually done during initialization at the start of the match
   *
   * @param xPosition The new x position
   * @param yPosition The new y position
   * @param theta The new orientation (e.g. what orientation the robot would be starting at for the start of the match)
   */
  void setPosition(double xPosition, double yPosition, double theta);
};

extern Odometry odometry;

#endif