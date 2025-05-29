#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "vex.h"

using namespace vex;
using namespace std;

/**
 * @brief Gets the current position of the robot using a combination of the Pilons
 * arc tracking strategy and Monte Carlo Localization
 */
class Odometry
{
private:
  double currentX;
  double currentY;
  double currentTheta;

  thread positionTrackThread;

public:
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

  /**
   * @brief Get the Current X Position of the robot
   *
   * @return Returns the value stored in the private variable
   */
  double getCurrentXPosition();

  /**
   * @brief Get the Current X Position of the robot
   *
   * @return Returns the value stored in the private variable
   */
  double getCurrentYPosition();

  /**
   * @brief Get the current orientation of the robot
   *
   * @return Returns the value stored in the private variable
   */
  double getAbsoluteHeading();

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
  void resetPosition(double xPosition, double yPosition, double theta);
};

#endif