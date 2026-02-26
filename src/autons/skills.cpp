#include "autons.h"
#include "config.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::skills()
{
  cout << Config::kForwardTrackerDistance << endl;
  cout << Config::kSidewaysTrackerDistance << endl;

  // Set starting coordinates
  chassisReference->odometry->setPosition(-45, 18, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  sloper.on();

  intake.spinFullIntake(vex::directionType::fwd, 12);

  // Eat center blocks
  chassisReference->turnTo(Pose<double>(-23, 22, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-23, 22, 0), {.driveMaxVoltage = 7}, turnParams10_deg(), {});
  cout << "center blocks position: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // Align to middle goal
  chassisReference->turnTo(Pose<double>(-13, 13, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-13, 13, 0), {}, {}, {.forwards = false});

  // Score in middle goal
  sloper.off();
  IntakeRear.spin(vex::directionType::fwd, 8, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(800, msec);
  sloper.on();
  intake.stopFullIntake();
  willyNilly.on();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 48, 0), {.driveTimeout = 2000}, turnParams10_deg(), {});

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, 48.25, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, (Config::kSkillsRamTimeMs - 100), chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {}); // decreased since the robot is closer to the loader this time
  chassisReference->driveWithVoltage(4, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(10, Config::kSkillsLoadLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Curve towards alleyway
  chassisReference->driveToPoint(Pose<double>(-25, 62, 0), {.driveTimeout = 1300}, {}, {.forwards = false});
  willyNilly.off();
  intake.stopFullIntake();

  // Drive through alleyway
  chassisReference->turnTo(Pose<double>(42, 60, -360), {}, {.forwards = false});
  cout << "x pod position before: " << chassisReference->odometry->getTrackersPositions().sideways << endl;
  cout << "Position before alleyway 1: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->driveToPoint(Pose<double>(42, 60, 0), {.driveTimeout = 1500}, turnParams10_deg(), {.forwards = false});
  cout << "Position after alleyway 1: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  cout << "x pod position after: " << chassisReference->odometry->getTrackersPositions().sideways << endl;

  // Turn out of alleyway
  chassisReference->turnTo(Pose<double>(42, 48, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 48, 0), {}, turnParams10_deg(), {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(27, 48, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(27, 48, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});
  cout << "Position before resetting 1: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, 47, chassisReference->odometry->getPose().orientation.angle);

  // 1st score
  blocker.on();
  willyNilly.on();
  intake.spinFullIntake(vex::directionType::fwd, 12);
  wait(Config::kSkillsScoreTimeMs, msec);
  intake.stopFullIntake();

  // Ram into 2nd loader
  chassisReference->turnTo(Pose<double>(68, 47, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  blocker.off();
  chassisReference->driveWithVoltage(4, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(10, Config::kSkillsLoadLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(27, 47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(27, 47, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});
  cout << "Position before resetting 2: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, 47, chassisReference->odometry->getPose().orientation.angle);

  // 2nd score
  blocker.on();
  wait(Config::kSkillsScoreTimeMs, msec);
  willyNilly.off();

  // Back away from 1st goal
  chassisReference->driveToPoint(Pose<double>(39, 47, 0), {}, turnParams10_deg(), {});

  // Align to blue park zone
  chassisReference->turnTo(Pose<double>(65, 30, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(65, 30, 0), {}, turnParams10_deg(), {});

  // Drive through park zone
  chassisReference->turnTo(Pose<double>(66, -27, -360), {}, {});
  blocker.off();
  chassisReference->driveWithVoltage(9, 2000, 170, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(7, 900, 170, turnParams10_deg(), {});

  // Drive back against park zone and reset position
  chassisReference->driveWithVoltage(-4, 1500, 185, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(-8, 800, 200, turnParams10_deg(), {});
  cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, -20, chassisReference->odometry->getPose().orientation.angle);
  cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->turnTo(Pose<double>(0, 0, 180), {}, {});
  chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::RIGHT);
  cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // Eat center blocks
  chassisReference->turnTo(Pose<double>(23, -20, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(23, -20, 0), {}, turnParams10_deg(), {});
  cout << "center blocks position: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // Align to middle goal
  intake.stopFullIntake();
  chassisReference->turnTo(Pose<double>(13.2, -10.2, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(13.2, -10.2, 135), {}, turnParams10_deg(), {.forwards = false});
  sloper.off();

  // Score in middle goal
  IntakeRear.spin(vex::directionType::fwd, 3.5, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 8, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(2000, msec);
  sloper.on();
  intake.stopFullIntake();
  willyNilly.on();

  // Drive towards 3rd dispenser
  chassisReference->turnTo(Pose<double>(39, -49.5, -360), {.turnTimeout = 500}, {});
  chassisReference->driveToPoint(Pose<double>(39, -49.5, 0), {}, turnParams10_deg(), {});

  // Ram into 3rd loader
  chassisReference->turnTo(Pose<double>(68, -49.5, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(4, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(10, Config::kSkillsLoadLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Curve through alleyway
  chassisReference->driveToPoint(Pose<double>(25, -62, 90), {}, {}, {.forwards = false});
  willyNilly.off();
  intake.stopFullIntake();

  // Drive through alleyway
  chassisReference->turnTo(Pose<double>(-42, -55, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -55, 0), {.driveTimeout = 1500}, {}, {.forwards = false});

  // Turn out of alleyway
  chassisReference->turnTo(Pose<double>(-42, -43.75, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -43.75, 0), {}, {}, {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -43.75, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -43.75, 0), {.driveTimeout = 1200}, {}, {.forwards = false});
  cout << "Position before resetting 3: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, -47, chassisReference->odometry->getPose().orientation.angle);

  // 3rd score
  blocker.on();
  willyNilly.on();
  intake.spinFullIntake(vex::directionType::fwd, 12);
  wait(Config::kSkillsScoreTimeMs, msec);
  intake.stopFullIntake();

  // Ram into 4th loader
  chassisReference->turnTo(Pose<double>(-68, -45, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  blocker.off();
  chassisReference->driveWithVoltage(4, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(10, Config::kSkillsLoadLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});
  cout << "Position before resetting 4: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, -47, chassisReference->odometry->getPose().orientation.angle);

  // 4th score
  blocker.on();
  wait(Config::kSkillsScoreTimeMs, msec);
  intake.stopFullIntake();
  willyNilly.off();

  // Drive towards red parking zone
  chassisReference->turnTo(Pose<double>(-63, -30, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-63, -30, 0), {}, turnParams10_deg(), {});
  blocker.off();

  // Turn into alignment in front of the red parking zone
  chassisReference->turnTo(Pose<double>(0, 0, 355), {}, {});

  // Park
  intake.spinFullIntake(vex::directionType::rev, 12);
  chassisReference->driveWithVoltage(12, 1440, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  wait(10000, msec);
}