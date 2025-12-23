#ifndef INTAKE_H
#define INTAKE_H

#include "vex.h"
#include "pneumatic.h"

class Intake
{
private:
public:
  int highPowerTime = 0;

  void scoreLongGoal()
  {
    spinFullIntake(vex::directionType::fwd);
    sloper.on();
    wait(3000, msec);
    sloper.off();
  }

  void spinBottomStage(vex::directionType direction, double speed = 12) { IntakeRight.spin(direction, speed, vex::voltageUnits::volt); };

  void spinTopStage(vex::directionType direction, double speed = 12) { IntakeLeft.spin(direction, speed, vex::voltageUnits::volt); };

  void spinFullIntake(vex::directionType direction, double speed = 12)
  {
    spinTopStage(direction, speed);
    spinBottomStage(direction, speed);
  };

  inline void stopFullIntake()
  {
    IntakeLeft.stop(vex::brakeType::coast);
    IntakeRight.stop(vex::brakeType::coast);
  };

  inline void stopBlocks() { sloper.off(); };
  inline void openBlocks() { sloper.on(); };
};

#endif