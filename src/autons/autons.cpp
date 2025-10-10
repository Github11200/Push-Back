#include "autons.h"

Autons::Autons(Chassis *chassis)
{
  this->chassisReference = chassis;
}

void Autons::printMessage(string message)
{
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(allianceColor);
  Brain.Screen.drawRectangle(0, 0, 479, 239);
  Brain.Screen.setPenWidth(10);
  Brain.Screen.print("%s\n", message.c_str());
  Brain.Screen.newLine();

  Controller.Screen.clearScreen();
  Controller.Screen.print("%s\n", message.c_str());
}

void Autons::prepareAuton(AutonName name, vex::color allianceColor)
{
  this->allianceColor = allianceColor;
  switch (name)
  {
  case AutonName::TESTING:
    printMessage("Running the TESTING auton.");
    autonToRun = testing;
    break;
  default:
    break;
  }

  chassisReference->calibrateInertial();
  chassisReference->resetEncoders();
  Logger::sendMessage("Done resetting and calibrating. Send it.");
}

void Autons::runAuton()
{
  this->autonToRun();
}