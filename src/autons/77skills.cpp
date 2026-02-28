#include "autons.h"
#include "config.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::skills77()
{
  cout << Config::kForwardTrackerDistance << endl;
  cout << Config::kSidewaysTrackerDistance << endl;

  // Set starting coordinates
  chassisReference->odometry->setPosition(-45, 18, 90);
  chassisReference->odometry->startPositionTrackThread(false);

  sloper.on();

  intake.spinFullIntake(vex::directionType::fwd, 12);

  // Eat center blocks
  chassisReference->turnTo(Pose<double>(-23, 24, -360), {}, {});
  willyNilly.delayToggle(1200);
  chassisReference->driveToPoint(Pose<double>(-23, 24, 0), {.driveMaxVoltage = 7}, turnParams10_deg(), {});
  cout << "center blocks position: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // Align to middle goal
  chassisReference->turnTo(Pose<double>(-14, 14, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-14, 14, 0), {}, {}, {.forwards = false});

  // Score in middle goal
  sloper.off();
  IntakeRear.spin(vex::directionType::fwd, 6, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(800, msec);
  sloper.on();
  intake.stopFullIntake();
  willyNilly.on();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 48.25, 0), {.driveTimeout = 2000}, turnParams10_deg(), {});

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, 48.5, -360), {}, {});
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

  chassisReference->driveWithVoltage(4, 700, chassisReference->getAbsoluteHeading().angle, {}, {});
  blocker.off();
  chassisReference->driveWithVoltage(-4, 900, chassisReference->getAbsoluteHeading().angle, {}, {});

  // Back away from 1st goal
  chassisReference->driveToPoint(Pose<double>(39, 47, 0), {}, turnParams10_deg(), {});

  // Drive towards 3rd dispenser
  chassisReference->turnTo(Pose<double>(39, -49.5, -360), {.turnTimeout = 500}, {});
  chassisReference->driveToPoint(Pose<double>(39, -49.5, 0), {}, turnParams10_deg(), {});
  sloper.on();

  // Ram into 3rd loader
  chassisReference->turnTo(Pose<double>(68, -49.5, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(4, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(10, Config::kSkillsLoadLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Curve through alleyway
  chassisReference->driveToPoint(Pose<double>(25, -61, 90), {.driveTimeout = 1300}, {}, {.forwards = false});
  willyNilly.off();
  intake.stopFullIntake();

  // Drive through alleyway
  chassisReference->turnTo(Pose<double>(-42, -53, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -53, 0), {.driveTimeout = 1500}, {}, {.forwards = false});

  // Turn out of alleyway
  chassisReference->turnTo(Pose<double>(-42, -44, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -44, 0), {}, {}, {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -44, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -44, 0), {.driveTimeout = 1200}, {}, {.forwards = false});
  cout << "Position before resetting 3: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, -47, chassisReference->odometry->getPose().orientation.angle);
  cout << "Position after resetting 3: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // 3rd score
  blocker.on();
  willyNilly.on();
  intake.spinFullIntake(vex::directionType::fwd, 12);
  wait(Config::kSkillsScoreTimeMs, msec);
  intake.stopFullIntake();

  // Ram into 4th loader
  chassisReference->turnTo(Pose<double>(-68, -44, -360), {}, {});
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

  chassisReference->driveWithVoltage(4, 500, chassisReference->getAbsoluteHeading().angle, {}, {});
  blocker.off();
  chassisReference->driveWithVoltage(-4, 700, chassisReference->getAbsoluteHeading().angle, {}, {});

  // Drive forward a bit
  chassisReference->driveToPoint(Pose<double>(-54, -47, 0), {}, {}, {});
  // chassisReference->driveDistance(20, chassisReference->getAbsoluteHeading().angle, {.driveTimeout = 1200}, {}, {});

  // Drive towards red parking zone
  chassisReference->turnTo(Pose<double>(-63, -18, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-63, -18, 0), {.driveTimeout = 1200}, turnParams10_deg(), {});
  blocker.off();

  // Turn into alignment in front of the red parking zone
  chassisReference->turnTo(Pose<double>(0, 0, 0), {}, {});

  // Park
  intake.spinFullIntake(vex::directionType::rev, 12);
  chassisReference->driveWithVoltage(11, 1000, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  wait(10000, msec);
}

// First wall distance - 4.76378
// Second wall distance - 5.82677