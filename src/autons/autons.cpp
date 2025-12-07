#include "autons.h"

Autons::Autons(std::unique_ptr<Chassis> chassis)
{
  this->chassisReference = std::move(chassis);
}

void Autons::printMessage(string message)
{
  Brain.Screen.clearScreen();
  // Brain.Screen.setFillColor(allianceColor);
  Brain.Screen.drawRectangle(0, 0, 479, 239);
  Brain.Screen.setPenWidth(10);
  Brain.Screen.print("%s\n", message.c_str());
  Brain.Screen.newLine();

  Controller.Screen.clearScreen();
  Controller.Screen.print("%s\n", message.c_str());
}

void Autons::prepareAuton()
{
  chassisReference->calibrateInertial();
  chassisReference->resetEncoders();
  Logger::sendMessage("Done resetting and calibrating. Send it.");
}

void Autons::runAuton(AutonName name)
{
  switch (name)
  {
  case AutonName::TESTING:
    Logger::sendMessage("Running the TESTING auton.");
    testing();
    break;
  case AutonName::HIGH:
    Logger::sendMessage("Running the HIGH goal auton.");
    high();
    break;
  case AutonName::LOW:
    Logger::sendMessage("Running the LOW goal auton.");
    low();
    break;
  case AutonName::SOLO:
    Logger::sendMessage("Running the SOLO awp auton.");
    solo();
    break;
  case AutonName::SKILLS:
    Logger::sendMessage("Running the SKILLS auton.");
    skills();
    break;
  default:
    break;
  }
}

// Autons::~Autons()
// {
//   delete chassisReference;
// }