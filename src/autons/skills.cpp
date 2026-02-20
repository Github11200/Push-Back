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
  chassisReference->odometry->setPosition(-62.1196, 20, 0);
  chassisReference->odometry->startPositionTrackThread(false);

  sloper.on();

  // Eat center blocks
  intake.spinFullIntake(vex::directionType::fwd);
  chassisReference->turnTo(Pose<double>(-23, 24, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-23, 24, 0), {.driveMaxVoltage = 7}, turnParams10_deg(), {});
  cout << "center blocks position: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // Align to middle goal
  intake.stopFullIntake();
  chassisReference->turnTo(Pose<double>(-11, 14, -360), {}, {.forwards = false});
  sloper.off();
  chassisReference->driveToPoint(Pose<double>(-11, 14, 0), {}, {}, {.forwards = false});

  // Score in middle goal
  IntakeRear.spin(vex::directionType::fwd, 8, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(800, msec);
  sloper.on();
  intake.stopFullIntake();
  willyNilly.on();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 48.5, 0), {.driveTimeout = 2000}, turnParams10_deg(), {});

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, 49, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(10, Config::kSkillsLoadLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Curve towards alleyway
  chassisReference->driveToPoint(Pose<double>(-40, 64, 0), {.driveTimeout = 1300}, {}, {.forwards = false});
  willyNilly.off();
  intake.stopFullIntake();

  // Drive through alleyway
  chassisReference->turnTo(Pose<double>(42, 64, -360), {}, {.forwards = false});
  cout << "x pod position before: " << chassisReference->odometry->getTrackersPositions().sideways << endl;
  cout << "Position before alleyway 1: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->driveToPoint(Pose<double>(42, 64, 0), {}, turnParams10_deg(), {.forwards = false});
  cout << "Position after alleyway 1: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  cout << "x pod position after: " << chassisReference->odometry->getTrackersPositions().sideways << endl;

  // Turn out of alleyway
  chassisReference->turnTo(Pose<double>(42, 50.5, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 50.5, 0), {}, turnParams10_deg(), {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(27, 50.5, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(27, 50.5, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});
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
  chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
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
  blocker.off();

  // // Align to blue park zone
  // chassisReference->turnTo(Pose<double>(64, 35, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(64, 35, 0), {}, turnParams10_deg(), {});

  // // Drive through park zone
  // chassisReference->turnTo(Pose<double>(66, -27, -360), {}, {});
  // chassisReference->driveWithVoltage(12, 1200, 170, turnParams10_deg(), {});
  // chassisReference->driveWithVoltage(7, 2000, 170, turnParams10_deg(), {});

  // // Drive back against park zone and reset position
  // chassisReference->driveWithVoltage(-4, 1500, 185, turnParams10_deg(), {});
  // chassisReference->driveWithVoltage(-8, 800, 185, turnParams10_deg(), {});
  // cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  // chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, -20, chassisReference->odometry->getPose().orientation.angle);
  // cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  // chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::RIGHT);
  // cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // // Eat center blocks
  // chassisReference->turnTo(Pose<double>(23, -23, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(23, -23, 0), {.driveMaxVoltage = 7}, turnParams10_deg(), {});
  // cout << "center blocks position: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // // Align to middle goal
  // intake.stopFullIntake();
  // chassisReference->turnTo(Pose<double>(12, -11, -360), {}, {.forwards = false});
  // sloper.off();
  // chassisReference->driveToPoint(Pose<double>(12, -11, 135), {}, turnParams10_deg(), {.forwards = false});

  // // Score in middle goal
  // IntakeRear.spin(vex::directionType::fwd, 6, vex::voltageUnits::volt);
  // IntakeMiddle.spin(vex::directionType::fwd, 10, vex::voltageUnits::volt);
  // IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  // wait(2000, msec);
  // sloper.on();
  // intake.stopFullIntake();
  willyNilly.on();

  // Drive towards 3rd dispenser
  chassisReference->turnTo(Pose<double>(47, -47, -360), {.turnTimeout = 500}, {});
  chassisReference->driveToPoint(Pose<double>(47, -48, 0), {}, turnParams10_deg(), {});

  // Ram into 3rd loader
  chassisReference->turnTo(Pose<double>(68, -47, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(10, Config::kSkillsLoadLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Curve through alleyway
  chassisReference->driveToPoint(Pose<double>(40, -62, 90), {.driveTimeout = 1300}, {}, {.forwards = false});
  willyNilly.off();
  intake.stopFullIntake();

  // Drive through alleyway
  chassisReference->turnTo(Pose<double>(-42, -60, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -60, 0), {.driveSettleError = 3, .driveSettleTime = 0}, {}, {.forwards = false});

  // Turn out of alleyway
  chassisReference->turnTo(Pose<double>(-42, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -47, 0), {}, {}, {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {.driveTimeout = 1200}, {}, {.forwards = false});
  cout << "Position before resetting 3: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, -47, chassisReference->odometry->getPose().orientation.angle);

  // 3rd score
  blocker.on();
  willyNilly.on();
  intake.spinFullIntake(vex::directionType::fwd, 12);
  wait(Config::kSkillsScoreTimeMs, msec);
  intake.stopFullIntake();

  // Ram into 4th loader
  chassisReference->turnTo(Pose<double>(-68, -46, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  blocker.off();
  chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(10, Config::kSkillsLoadLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});
  cout << "Position before resetting 4: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, -47, chassisReference->odometry->getPose().orientation.angle);

  // 4th score
  blocker.on();
  wait(Config::kSkillsScoreTimeMs, msec);
  blocker.off();
  intake.stopFullIntake();
  willyNilly.off();

  // Drive towards red parking zone
  chassisReference->turnTo(Pose<double>(-55, -34, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-55, -34, 0), {}, turnParams10_deg(), {});

  // Turn into alignment in front of the red parking zone
  chassisReference->turnTo(Pose<double>(-63, 0, -360), {}, {SwingDirection::SWING_RIGHT});

  // Park
  intake.spinFullIntake(vex::directionType::rev, 12);
  chassisReference->driveWithVoltage(12, 1300, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  wait(10000, msec);
}