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
  TUNING = 5
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
  void tuning();

  void printMessage(std::string message);
  void prepareAuton();
  void runAuton(AutonName name);
};

#endif