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

  void spinBottomStage(vex::directionType direction)
  {
    BottomIntake.spin(direction, 12, vex::voltageUnits::volt);
  };

  void spinTopStage(vex::directionType direction) { TopIntake.spin(direction, 12, vex::voltageUnits::volt); };

  void spinFullIntake(vex::directionType direction)
  {
    // if (direction == vex::directionType::fwd)
    // {
    //   spinFullIntake(vex::directionType::rev);
    //   wait(200, msec);
    // }
    spinTopStage(direction);
    spinBottomStage(direction);
  };

  inline void stopFullIntake()
  {
    TopIntake.stop(vex::brakeType::coast);
    BottomIntake.stop(vex::brakeType::coast);
  };

  inline void stopBlocks() { sloper.off(); };
  inline void openBlocks() { sloper.on(); };
};

#endif