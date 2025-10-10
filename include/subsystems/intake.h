#ifndef INTAKE_H
#define INTAKE_H

#include "vex.h"
#include "pneumatic.h"

class Intake
{
private:
public:
  inline void spinBottomStage(vex::directionType direction) { BottomIntake.spin(direction, 12, vex::voltageUnits::volt); };
  inline void spinTopStage(vex::directionType direction)
  {
    if (direction == vex::directionType::fwd && TopIntake.velocity(pct) > 10)
      TopIntake.spin(direction, 12, vex::voltageUnits::volt);
  };

  inline void spinFullIntake(vex::directionType direction)
  {
    spinBottomStage(direction);
    spinTopStage(direction);
  };

  inline void stopBlocks() { sloper.off(); };
  inline void openBlocks() { sloper.on(); };
};

#endif