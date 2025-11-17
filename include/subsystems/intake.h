#ifndef INTAKE_H
#define INTAKE_H

#include "vex.h"
#include "pneumatic.h"

class Intake
{
private:
public:
  int highPowerTime = 0;

  void spinBottomStage(vex::directionType direction) { BottomIntake.spin(direction, 12, vex::voltageUnits::volt); };
  void spinTopStage(vex::directionType direction)
  {
    // std::cout << "hptdd: " << highPowerTime << std::endl;
    // if (TopIntake.power(watt) > 4.5)
    //   ++highPowerTime;
    // else if (highPowerTime > 0 && highPowerTime <= 20)
    //   --highPowerTime;

    // if (highPowerTime >= 20)
    //   TopIntake.stop(coast);
    // else if (highPowerTime < 20)
    TopIntake.spin(direction, 12, vex::voltageUnits::volt);
  };

  void spinFullIntake(vex::directionType direction)
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