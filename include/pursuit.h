#ifndef PURSUIT_H
#define PURSUIT_H

#include "chassis.h"

typedef vector<Pose<double>> Path;

class Pursuit : Chassis
{
private:
  Pose<double> currentPosition;
  PursuitParams params;
  Path currentPath;

public:
  Pursuit(PursuitParams params);

  Path loadPathFromFile(string fileName);

  int findClosestPoint();
  double circleIntersect(Vector2D<double> point1, Vector2D<double> point2);
  Pose<double> findLookAheadPoint(Vector2D<double> lastLookAhead, int lastLookAheadIndex, int closestPointIndex);
  double getCurvature(Vector2D<double> lookaheadPoint);

  double fullStateFeedback(Vector2D<double> target, double targetVelocity, double currentVelocity);

  void followPath(Path path);
};

#endif