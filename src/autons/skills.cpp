#include "autons.h"
#include "config.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::skills()
{
  // Set starting coordinates
  chassisReference->odometry->setPosition(-63, -16, 0);
  chassisReference->odometry->startPositionTrackThread(false);

  // Start up the intake
  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();

  // willyNilly.delayToggle(1100);

  // Drive through park zone
  // chassisReference->driveWithVoltage(12, 2200, 0, turnParams10_deg(), {});
  // chassisReference->driveWithVoltage(2, 500, 355, turnParams10_deg(), {});

  // Drive back against park zone and reset position
  // chassisReference->driveWithVoltage(-4, 1500, 5, turnParams10_deg(), {});
  // chassisReference->driveWithVoltage(-8, 800, 5, turnParams10_deg(), {});
  cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, 20, chassisReference->odometry->getPose().orientation.angle);
  cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->wallReset(DistanceSensor::PORT, Wall::LEFT);
  cout << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // // Go forwards a bit
  // chassisReference->driveToPoint(Pose<double>(-63, 23, 0), {}, turnParams10_deg(), {});

  // // Distance reset x-position against the wall
  // chassisReference->turnTo(Pose<double>(-23, 23, -360), {}, {});
  // chassisReference->driveWithVoltage(-5, 700, 0, turnParams10_deg(), {});
  // chassisReference->odometry->setPosition(-62, chassisReference->odometry->getPose().position.y, chassisReference->odometry->getPose().orientation.angle);

  // Slap down willynilly to grab center blocks
  willyNilly.delayToggle(1600);

  // Eat center blocks
  chassisReference->turnTo(Pose<double>(-23, 25, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-23, 25, 0), {}, turnParams10_deg(), {});
  cout << "center blocks position: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;

  // Align to middle goal
  chassisReference->turnTo(Pose<double>(-13, 14, -360), {}, {.forwards = false});
  intake.stopFullIntake();
  sloper.off();
  chassisReference->driveToPoint(Pose<double>(-13, 14, 0), {}, turnParams10_deg(), {.forwards = false});

  // Score in middle goal
  IntakeRear.spin(vex::directionType::fwd, 4, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(1200, msec);
  sloper.on();
  intake.stopFullIntake();

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 47, 0), {.driveTimeout = 2000}, turnParams10_deg(), {});

  // Ram into 1st loader
  chassisReference->turnTo(Pose<double>(-68, 47, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Curve towards alleyway
  chassisReference->driveToPose(Pose<double>(-23, 70, 60), {}, turnParams30_deg(), {.forwards = false}, 0.1);
  willyNilly.off();
  intake.stopFullIntake();

  // Drive through alleyway
  chassisReference->turnTo(Pose<double>(42, 62.5, -360), {}, {.forwards = false});
  cout << "x pod position before: " << chassisReference->odometry->getTrackersPositions().sideways << endl;
  cout << "Position before alleyway 1: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->driveToPoint(Pose<double>(42, 62.5, 0), {}, turnParams10_deg(), {.forwards = false});
  cout << "Position after alleyway 1: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  cout << "x pod position after: " << chassisReference->odometry->getTrackersPositions().sideways << endl;

  // Turn out of alleyway
  chassisReference->turnTo(Pose<double>(42, 51, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 50, 0), {}, turnParams10_deg(), {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(27, 51, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(27, 50, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});
  cout << "Position before resetting 1: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, 47, chassisReference->odometry->getPose().orientation.angle);

  // 1st score
  blocker.on();
  willyNilly.on();
  intake.spinFullIntake(vex::directionType::fwd, 12);
  wait(Config::kSkillsScoreTimeMs, msec);
  blocker.off();
  intake.stopFullIntake();

  // Ram into 2nd loader
  chassisReference->turnTo(Pose<double>(68, 47, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(27, 47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(27, 47, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});
  cout << "Position before resetting 2: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, 47, chassisReference->odometry->getPose().orientation.angle);

  // 2nd score
  blocker.on();
  wait(Config::kSkillsScoreTimeMs, msec);
  blocker.off();
  intake.stopFullIntake();
  willyNilly.off();

  // Back away from 1st goal
  chassisReference->driveToPoint(Pose<double>(39, 47, 0), {}, turnParams10_deg(), {});

  // Drive across the field towards 3rd dispenser
  chassisReference->turnTo(Pose<double>(39, -48, -360), {.turnTimeout = 500}, {});
  chassisReference->driveToPoint(Pose<double>(39, -48, 0), {}, turnParams10_deg(), {});
  willyNilly.on();

  // Ram into 3rd loader
  chassisReference->turnTo(Pose<double>(68, -48, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Curve through alleyway
  finger.on();
  chassisReference->driveToPose(Pose<double>(23, -68, 60), {}, turnParams30_deg(), {.forwards = false}, 0.1);
  willyNilly.off();
  intake.stopFullIntake();

  // Drive through alleyway
  chassisReference->turnTo(Pose<double>(-42, -63, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -63, 0), {}, turnParams10_deg(), {.forwards = false});

  // Turn out of alleyway
  chassisReference->turnTo(Pose<double>(-42, -48, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -48, 0), {}, turnParams10_deg(), {.forwards = false});
  finger.off();

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -48, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -48, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});
  cout << "Position before resetting 3: " << chassisReference->odometry->getPose().position.x << ", " << chassisReference->odometry->getPose().position.y << ", " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, -47, chassisReference->odometry->getPose().orientation.angle);

  // 3rd score
  blocker.on();
  willyNilly.on();
  intake.spinFullIntake(vex::directionType::fwd, 12);
  wait(Config::kSkillsScoreTimeMs, msec);
  blocker.off();
  intake.stopFullIntake();

  // Ram into 4th loader
  chassisReference->turnTo(Pose<double>(-68, -47, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

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
  chassisReference->turnTo(Pose<double>(-53, -34, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-53, -34, 0), {}, turnParams10_deg(), {});

  // Turn into alignment in front of the red parking zone
  chassisReference->turnTo(Pose<double>(-63, 0, -360), {}, {SwingDirection::SWING_RIGHT});

  // Park
  chassisReference->driveWithVoltage(12, 1500, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  wait(10000, msec);
}