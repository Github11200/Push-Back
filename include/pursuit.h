#ifndef PURSUIT_H
#define PURSUIT_H

#include "vex.h"
#include "types/pose.h"
#include "types/params.h"

typedef std::vector<Pose<double>> Path;

class Chassis;

class Pursuit
{
private:
  Pose<double> currentPosition;
  PursuitParams params;
  Path currentPath;
  Chassis *chassis;

public:
  Pursuit(Chassis *chassis, PursuitParams params);
  ~Pursuit();

  Path loadPathFromFile(std::string fileName);

  int findClosestPoint();
  double circleIntersect(Vector2D<double> point1, Vector2D<double> point2);
  Pose<double> findLookAheadPoint(Vector2D<double> lastLookAhead, int lastLookAheadIndex, int closestPointIndex);
  double getCurvature(Vector2D<double> lookaheadPoint);

  double fullStateFeedback(Vector2D<double> target, double targetVelocity, double currentVelocity);

  void followPath(Path path);
};

#endif