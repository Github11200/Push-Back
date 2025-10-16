#ifndef AUTONS_H
#define AUTONS_H

#include "vex.h"
#include "subsystems/pneumatic.h"
#include "chassis.h"

enum AutonName
{
  TESTING = 0
};

class Autons
{
private:
  vex::color allianceColor;
  Chassis *chassisReference;

public:
  Autons(Chassis *chassis);

  void testing();
  void left();
  void right();

  void printMessage(std::string message);
  void prepareAuton();
  void runAuton(AutonName name, vex::color allianceColor);
};

#endif