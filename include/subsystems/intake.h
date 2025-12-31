#ifndef INTAKE_H
#define INTAKE_H

#include "vex.h"
#include "pneumatic.h"

class Intake
{
private:
public:
  int highPowerTime = 0;

  void intakeDispenserUntilColor(vex::color allianceColor);
  void scoreLongGoal();

  void spinFullIntake(vex::directionType direction, double speed = 12);

  void stopFullIntake();

  inline void stopBlocks() { sloper.off(); };
  inline void openBlocks() { sloper.on(); };
};

#endif