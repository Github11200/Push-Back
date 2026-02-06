#include "autons.h"
#include "config.h"
#include "subsystems/intake.h"
#include "vex.h"
#include "types/params.h"

void Autons::skills()
{
  DriveParams driveParams;
  TurnParams turnParams;

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

  // // Go forwards a bit
  // driveParams = driveParams5_in();
  // chassisReference->driveToPoint(Pose<double>(-63, 23, 0), driveParams, turnParams10_deg(), {});

  // // Distance reset x-position against the wall
  // turnParams = turnParams90_deg();
  // chassisReference->turnTo(Pose<double>(-23, 23, -360), turnParams, {});
  // chassisReference->driveWithVoltage(-5, 700, 0, turnParams10_deg(), {});
  // chassisReference->odometry->setPosition(-62, chassisReference->odometry->getPose().position.y, chassisReference->odometry->getPose().orientation.angle);

  // // Slap down willynilly to grab center blocks
  // willyNilly.delayToggle(1100);

  // // Eat center blocks
  // turnParams = turnParams10_deg();
  // driveParams = driveParams30_in();
  // chassisReference->turnTo(Pose<double>(-23, 23, -360), turnParams, {});
  // chassisReference->driveToPoint(Pose<double>(-23, 23, 0), driveParams, turnParams10_deg(), {});

  // // Align to middle goal
  // turnParams = turnParams135_deg();
  // driveParams = driveParams10_in();
  // chassisReference->turnTo(Pose<double>(-13, 13, -360), turnParams, {.forwards = false});
  // intake.stopFullIntake();
  // sloper.off();
  // chassisReference->driveToPoint(Pose<double>(-13, 13, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // // Score in middle goal
  // IntakeRear.spin(vex::directionType::fwd, 5, vex::voltageUnits::volt);
  // IntakeMiddle.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  // IntakeFront.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  // wait(1000, msec);
  // sloper.on();
  // intake.stopFullIntake();

  // // Drive in front of the loader
  // driveParams = driveParams30_in();
  // driveParams.driveTimeout = 2000;
  // chassisReference->driveToPoint(Pose<double>(-47, 47, 0), driveParams, turnParams10_deg(), {});

  // // Ram into 1st loader
  // turnParams = turnParams90_deg();
  // chassisReference->turnTo(Pose<double>(-68, 47, -360), turnParams, {});
  // intake.spinFullIntake(vex::directionType::fwd, 12);
  // chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});
  // chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});

  // // Curve towards alleyway
  // driveParams = driveParams50_in();
  // chassisReference->driveToPose(Pose<double>(-23, 61, 60), driveParams, turnParams30_deg(), {.forwards = false}, 0.1);
  // willyNilly.off();
  // intake.stopFullIntake();

  // // Drive through alleyway
  // turnParams = turnParams10_deg();
  // driveParams = driveParams50_in();
  // chassisReference->turnTo(Pose<double>(42, 61, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(42, 61, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // // Turn out of alleyway
  // turnParams = turnParams90_deg();
  // driveParams = driveParams10_in();
  // chassisReference->turnTo(Pose<double>(42, 47, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(42, 47, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // // Align to long goal
  // turnParams = turnParams90_deg();
  // driveParams = driveParams10_in();
  // chassisReference->turnTo(Pose<double>(27, 47, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(27, 47, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // // 1st score
  // blocker.on();
  // willyNilly.on();
  // wait(Config::kSkillsScoreTimeMs, msec);
  // blocker.off();
  // intake.stopFullIntake();

  // // Ram into 2nd loader
  // turnParams = turnParams10_deg();
  // chassisReference->turnTo(Pose<double>(68, 47, -360), turnParams, {});
  // intake.spinFullIntake(vex::directionType::fwd, 12);
  // chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});
  // chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});

  // // Align to long goal
  // turnParams = turnParams10_deg();
  // driveParams = driveParams30_in();
  // chassisReference->turnTo(Pose<double>(27, 47, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(27, 47, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // // 2nd score
  // blocker.on();
  // wait(Config::kSkillsScoreTimeMs, msec);
  // blocker.off();
  // intake.stopFullIntake();
  // willyNilly.off();

  // // Back away from 1st goal
  // driveParams = driveParams10_in();
  // chassisReference->driveToPoint(Pose<double>(39, 47, 0), driveParams, turnParams10_deg(), {});

  // // Drive across the field towards 3rd dispenser
  // driveParams = driveParams100_in();
  // turnParams = turnParams90_deg();
  // turnParams.turnTimeout = 500;
  // chassisReference->turnTo(Pose<double>(39, -47, -360), turnParams, {});
  // chassisReference->driveToPoint(Pose<double>(39, -47, 0), driveParams, turnParams10_deg(), {});
  // willyNilly.on();

  // // Ram into 3rd loader
  // turnParams = turnParams90_deg();
  // chassisReference->turnTo(Pose<double>(68, -47, -360), turnParams, {});
  // intake.spinFullIntake(vex::directionType::fwd, 12);
  // chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});
  // chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});

  // // Curve through alleyway
  // finger.on();
  // driveParams = driveParams50_in();
  // chassisReference->driveToPose(Pose<double>(23, -61, 60), driveParams, turnParams30_deg(), {.forwards = false}, 0.1);
  // willyNilly.off();
  // intake.stopFullIntake();

  // // Drive through alleyway
  // turnParams = turnParams10_deg();
  // driveParams = driveParams50_in();
  // chassisReference->turnTo(Pose<double>(-42, -61, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-42, -61, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // // Turn out of alleyway
  // turnParams = turnParams90_deg();
  // driveParams = driveParams10_in();
  // chassisReference->turnTo(Pose<double>(-42, -47, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-42, -47, 0), driveParams, turnParams10_deg(), {.forwards = false});
  // finger.off();

  // // Align to long goal
  // turnParams = turnParams90_deg();
  // driveParams = driveParams10_in();
  // chassisReference->turnTo(Pose<double>(-27, -47, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-27, -47, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // // 3rd score
  // blocker.on();
  // willyNilly.on();
  // wait(Config::kSkillsScoreTimeMs, msec);
  // blocker.off();
  // intake.stopFullIntake();

  // // Ram into 4th loader
  // turnParams = turnParams10_deg();
  // chassisReference->turnTo(Pose<double>(-68, -47, -360), turnParams, {});
  // intake.spinFullIntake(vex::directionType::fwd, 12);
  // chassisReference->driveWithVoltage(12, Config::kSkillsRamTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});
  // chassisReference->driveWithVoltage(5, Config::kSkillsLoadTimeMs, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});

  // // Align to long goal
  // turnParams = turnParams10_deg();
  // driveParams = driveParams30_in();
  // chassisReference->turnTo(Pose<double>(-27, -47, -360), turnParams, {.forwards = false});
  // chassisReference->driveToPoint(Pose<double>(-27, -47, 0), driveParams, turnParams10_deg(), {.forwards = false});

  // // 4th score
  // blocker.on();
  // wait(Config::kSkillsScoreTimeMs, msec);
  // blocker.off();
  // intake.stopFullIntake();
  // willyNilly.off();

  // // Drive towards red parking zone
  // turnParams = turnParams30_deg();
  // driveParams = driveParams30_in();
  // chassisReference->turnTo(Pose<double>(-53, -34, -360), turnParams, {});
  // chassisReference->driveToPoint(Pose<double>(-53, -34, 0), driveParams, turnParams10_deg(), {});

  // // Swing into alignment in front of the red parking zone
  // turnParams = turnParams60_deg();
  // chassisReference->turnTo(Pose<double>(-63, 0, -360), turnParams, {}, SwingDirection::SWING_LEFT);

  // // Park
  // chassisReference->driveWithVoltage(12, 1500, chassisReference->getAbsoluteHeading().angle, turnParams = turnParams10_deg(), {});
  // wait(10000, msec);
}