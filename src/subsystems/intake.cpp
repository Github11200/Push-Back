#include "subsystems/intake.h"

using namespace std;
using namespace vex;

void Intake::intakeDispenserUntilColor(vex::color allianceColor)
{
  vex::color oppositeAllianceColor = allianceColor == vex::color::red ? vex::color::blue : vex::color::red;
  uint32_t startTime = vex::timer::system();

  while (vex::timer::system() - startTime < 2000 && IntakeOptical.color() != oppositeAllianceColor)
    spinFullIntake(vex::directionType::fwd);
  stopFullIntake();
}

void Intake::scoreLongGoal()
{
  spinFullIntake(vex::directionType::fwd);
  sloper.on();
  blocker.on();
  wait(1500, msec);
  sloper.off();
}

void Intake::spinFullIntake(vex::directionType direction, double speed)
{
  IntakeLeft.spin(direction, speed, vex::voltageUnits::volt);
  IntakeRight.spin(direction, speed, vex::voltageUnits::volt);
}

void Intake::stopFullIntake()
{
  IntakeLeft.stop(vex::brakeType::coast);
  IntakeRight.stop(vex::brakeType::coast);
}