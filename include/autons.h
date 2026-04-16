#ifndef AUTONS_H
#define AUTONS_H

#include "vex.h"
#include "subsystems/pneumatic.h"
#include "subsystems/intake.h"
#include "chassis.h"

enum AutonName
{
  TESTING = 0,
  HIGH = 1,
  LOW = 2,
  SOLO = 3,
  SKILLS = 4,
  TUNING = 5,
  RUSH_HIGH = 6,
  RUSH_LOW = 7,
  SKILLS_77 = 8,
  FOUR_BALL_LOW = 9,
  MID_GOALS = 10,
  FOUR_BALL_HIGH = 11
};

enum Side
{
  LEFT_SIDE = 0,
  RIGHT_SIDE = 1
};

class Autons
{
private:
  std::unique_ptr<Chassis> chassisReference;
  Intake intake;

public:
  Autons(std::unique_ptr<Chassis> chassis);

  void testing();
  void high();
  void low();
  void solo();
  void skills();
  void skills77();
  void tuning();
  void rush_high();
  void rush_low();
  void fourBallLow();
  void fourBallHigh();
  void midGoals();

  void printMessage(std::string message);
  void prepareAuton();
  void runAuton(AutonName name);
};

#endif