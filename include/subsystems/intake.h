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
    // TODO: Add in the safety code so it doesn't keep trying to spin
    TopIntake.spin(direction, 12, vex::voltageUnits::volt);
  };

  inline void spinFullIntake(vex::directionType direction)
  {
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