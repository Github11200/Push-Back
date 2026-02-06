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

  // Drive through park zone
  chassisReference->driveWithVoltage(12, 2000, 0, turnParams10_deg(), {});

  // Drive back against park zone and distance reset y-position
  chassisReference->driveWithVoltage(-5, 1000, 0, turnParams10_deg(), {});
  chassisReference->odometry->setPosition(chassisReference->odometry->getPose().position.x, 16, chassisReference->odometry->getPose().orientation.angle);

  // Go forwards a bit
  chassisReference->driveToPoint(Pose<double>(-63, 23, 0), {}, turnParams10_deg(), {});

  // Distance reset x-position against the wall
  chassisReference->turnTo(Pose<double>(-23, 23, -360), {}, {});
  chassisReference->driveWithVoltage(-5, 700, 0, turnParams10_deg(), {});
  chassisReference->odometry->setPosition(-62, chassisReference->odometry->getPose().position.y, chassisReference->odometry->getPose().orientation.angle);

  // Slap down willynilly to grab center blocks
  willyNilly.delayToggle(1100);

  // Eat center blocks
  chassisReference->turnTo(Pose<double>(-23, 23, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-23, 23, 0), {}, turnParams10_deg(), {});

  // Align to middle goal
  chassisReference->turnTo(Pose<double>(-13, 13, -360), {}, {.forwards = false});
  intake.stopFullIntake();
  sloper.off();
  chassisReference->driveToPoint(Pose<double>(-13, 13, 0), {}, turnParams10_deg(), {.forwards = false});

  // Score in middle goal
  IntakeRear.spin(vex::directionType::fwd, 5, vex::voltageUnits::volt);
  IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  wait(1000, msec);
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
  chassisReference->driveToPose(Pose<double>(-23, 61, 60), {}, turnParams30_deg(), {.forwards = false}, 0.1);
  willyNilly.off();
  intake.stopFullIntake();

  // Drive through alleyway
  chassisReference->turnTo(Pose<double>(42, 61, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 61, 0), {}, turnParams10_deg(), {.forwards = false});

  // Turn out of alleyway
  chassisReference->turnTo(Pose<double>(42, 47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(42, 47, 0), {}, turnParams10_deg(), {.forwards = false});

  // Align to long goal
  chassisReference->turnTo(Pose<double>(27, 47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(27, 47, 0), {}, turnParams10_deg(), {.forwards = false});

  // 1st score
  blocker.on();
  willyNilly.on();
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
  chassisReference->driveToPoint(Pose<double>(27, 47, 0), {}, turnParams10_deg(), {.forwards = false});

  // 2nd score
  blocker.on();
  wait(Config::kSkillsScoreTimeMs, msec);
  blocker.off();
  intake.stopFullIntake();
  willyNilly.off();

  // Back away from 1st goal
  chassisReference->driveToPoint(Pose<double>(39, 47, 0), {}, turnParams10_deg(), {});

  // Drive across the field towards 3rd dispenser
  chassisReference->turnTo(Pose<double>(39, -47, -360), {.turnTimeout = 500}, {});
  chassisReference->driveToPoint(Pose<double>(39, -47, 0), {}, turnParams10_deg(), {});
  willyNilly.on();

  // Ram into 3rd loader
  chassisReference->turnTo(Pose<double>(68, -47, -360), {}, {});
  intake.spinFullIntake(vex::directionType::fwd, 12);
  chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Curve through alleyway
  finger.on();
  chassisReference->driveToPose(Pose<double>(23, -61, 60), {}, turnParams30_deg(), {.forwards = false}, 0.1);
  willyNilly.off();
  intake.stopFullIntake();

  // Drive through alleyway
  chassisReference->turnTo(Pose<double>(-42, -61, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -61, 0), {}, turnParams10_deg(), {.forwards = false});

  // Turn out of alleyway
  chassisReference->turnTo(Pose<double>(-42, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-42, -47, 0), {}, turnParams10_deg(), {.forwards = false});
  finger.off();

  // Align to long goal
  chassisReference->turnTo(Pose<double>(-27, -47, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {}, turnParams10_deg(), {.forwards = false});

  // 3rd score
  blocker.on();
  willyNilly.on();
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
  chassisReference->driveToPoint(Pose<double>(-27, -47, 0), {}, turnParams10_deg(), {.forwards = false});

  // 4th score
  blocker.on();
  wait(Config::kSkillsScoreTimeMs, msec);
  blocker.off();
  intake.stopFullIntake();
  willyNilly.off();

  // Drive towards red parking zone
  chassisReference->turnTo(Pose<double>(-53, -34, -360), {}, {});
  chassisReference->driveToPoint(Pose<double>(-53, -34, 0), {}, turnParams10_deg(), {});

  // Swing into alignment in front of the red parking zone
  chassisReference->turnTo(Pose<double>(-63, 0, -360), {}, {}, SwingDirection::SWING_LEFT);

  // Park
  chassisReference->driveWithVoltage(12, 1500, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  wait(10000, msec);
}