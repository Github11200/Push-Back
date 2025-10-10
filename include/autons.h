#ifndef AUTONS_H
#define AUTONS_H

#include "vex.h"
#include "subsystems/pneumatic.h"
#include "chassis.h"

enum AutonName
{
  TESTING = 0
};

void testing();
void left();
void right();

class Autons
{
private:
  vex::color allianceColor;
  std::function<void(void)> autonToRun;
  Chassis *chassisReference;

public:
  Autons(Chassis *chassis);

  void printMessage(std::string message);
  void prepareAuton(AutonName name, vex::color allianceColor);
  void runAuton();
};

#endif