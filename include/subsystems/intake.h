#ifndef INTAKE_H
#define INTAKE_H

#include "vex.h"
#include "pneumatic.h"

class Intake
{
private:
public:
  void spinFrontStage();
  void spinTopStage();

  inline void stopBlocks() { sloper.off(); };
  inline void openBlocks() { sloper.on(); };
};

#endif