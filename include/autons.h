#ifndef AUTONS_H
#define AUTONS_H

#include "vex.h"

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

public:
  void printMessage(std::string message);
  void prepareAuton(AutonName name, vex::color allianceColor);
  void runAuton();
};

#endif