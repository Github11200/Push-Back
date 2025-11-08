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
  SOLO = 3
};

enum Side
{
  LEFT = 0,
  RIGHT = 1
};

class Autons
{
private:
  vex::color allianceColor;
  Side side;
  Chassis *chassisReference;
  Intake intake;

public:
  Autons(Chassis *chassis);

  void testing();
  void high();
  void low();
  void solo();

  void printMessage(std::string message);
  void prepareAuton();
  void runAuton(AutonName name, Side side);
};

#endif