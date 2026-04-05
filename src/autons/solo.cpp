#include "autons.h"
#include "vex.h"
#include "types/params.h"

void Autons::solo()
{
  chassisReference->odometry->setPosition(-45, 0, 180);
  chassisReference->odometry->startPositionTrackThread(true);

  cout << DriveParams().driveSettleTime << endl;
  cout << Config::kSidewaysTrackerDistance << endl;

  intake.spinFullIntake(vex::directionType::fwd);
  sloper.on();

  // Push our alliance
  chassisReference->driveToPoint(Pose<double>(-45, -5, 0), {.driveTimeout = 700}, turnParams10_deg(), {});

  // Drive in front of the loader
  chassisReference->driveToPoint(Pose<double>(-47, 47, 0), {.driveTimeout = 1200}, turnParams10_deg(), {.forwards = false});

  // Ram into 1st loader
  willyNilly.on();
  chassisReference->turnTo(Pose<double>(-68, 47, -360), {.turnTimeout = 700}, {});
  chassisReference->driveWithVoltage(12, 200, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 650, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Go up to long goal
  chassisReference->turnTo(Pose<double>(-26, 47, -360), {.turnTimeout = 200}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-26, 47, 0), {.driveTimeout = 1050}, turnParams10_deg(), {.forwards = false});
  willyNilly.off();

  // Score
  blocker.on();
  wait(800, msec);

  // Back away from 1st long goal
  // chassisReference->driveToPoint(Pose<double>(-37, -47, 0), {.driveSettleError = 3, .driveSettleTime = 0}, {}, {});

  // chassisReference->turnTo(Pose<double>(-10, -10, -360), {.turnSettleError = 5, .turnSettleTime = 0}, {});
  // chassisReference->driveToPoint(Pose<double>(-18.5, -18.5, 0), {}, {}, {});

  // chassisReference->driveToPose(Pose<double>(-18, -18, 45), {.driveSettleError = 0.1}, {.turnSettleError = 0.1}, {}, 0.4, 0, 0);

  cout << "X: " << chassisReference->odometry->getPose().position.x << endl;
  cout << "Y: " << chassisReference->odometry->getPose().position.y << endl;
  cout << "Angle: " << chassisReference->odometry->getPose().orientation.angle << endl;
  chassisReference->turnTo(Pose<double>(-23, 23, -360), {.turnTimeout = 700}, {});
  // Turn by clipping onto the goal
  IntakeFront.spin(vex::directionType::fwd, 12, volt);

  willyNilly.delayToggle(800);
  chassisReference->driveToPoint(Pose<double>(-25, -21, 0), {.driveSettleError = 1, .driveSettleTime = 100, .driveTimeout = 1100}, {}, {});

  blocker.off();

  // Go up to low goal
  willyNilly.delayToggle(100);
  chassisReference->turnTo(Pose<double>(-13, -11, -360), {}, {});
  intake.stopFullIntake();
  IntakeFront.spin(vex::directionType::fwd, 12, volt);
  chassisReference->driveToPoint(Pose<double>(-13, -11, 0), {.driveTimeout = 1000}, {}, {});
  razer.on();
  willyNilly.off();

  // // This fixes the angle before outtaking
  // chassisReference->turnTo(Pose<double>(-23, -23, -360), {.turnTimeout = 100}, {.forwards = false});

  // Score in low goal
  intake.spinFullIntake(vex::directionType::rev, 12);
  wait(200, msec);
  IntakeFront.spin(vex::directionType::rev, 7, volt);
  wait(1000, msec);
  razer.off();
  finger.on();
  blocker.on();

  // Back up from low goal
  chassisReference->driveToPoint(Pose<double>(-23, -23, 0), {.driveTimeout = 400}, {}, {.forwards = false});
  intake.spinFullIntake(vex::directionType::fwd, 12);

  cout << "X: " << chassisReference->odometry->getPose().position.x << endl;
  cout << "Y: " << chassisReference->odometry->getPose().position.y << endl;
  cout << "Angle: " << chassisReference->odometry->getPose().orientation.angle << endl;

  // Eat other middle blocks
  chassisReference->turnTo(Pose<double>(-21, 18, -360), {.turnTimeout = 300}, {});
  willyNilly.delayToggle(850);
  // finger.on();
  chassisReference->driveToPoint(Pose<double>(-21, 18, 0), {.driveMinVoltage = 8, .driveSettleError = 10, .driveSettleTime = 0}, {}, {});
  blocker.off();

  // Go towards loader entrance point
  // willyNilly.on();
  // chassisReference->turnTo(Pose<double>(-47, 47, -360), {.turnTimeout = 600}, {});
  // chassisReference->driveToPoint(Pose<double>(-47, 47, 0), {.driveTimeout = 800, .driveSlew = 12}, {}, {});

  // CurvedMotionProfile motionProfile;
  // // Vector2D<double> points[4] = {
  // //     Vector2D<double>(0, 0), Vector2D<double>(0, 20),
  // //     Vector2D<double>(0, 20), Vector2D<double>(20, 20)};
  // Vector2D<double> points[4] = {
  //     Vector2D<double>(-23, -23), Vector2D<double>(-22.3, 30),
  //     Vector2D<double>(-22.3, 46.5), Vector2D<double>(-68, 46.5)};
  // motionProfile.curve = CubicBezier(points);
  // motionProfile.distanceBetweenPoints = 0.25;
  // motionProfile.initialVelocity = 25;
  // motionProfile.finalVelocity = 0;
  // motionProfile.maximumAcceleration = 15;
  // motionProfile.maximumVelocity = 50;
  // motionProfile.kV = 0.005;
  // motionProfile.kA = 0.02;

  // RamseteParams params;
  // params.beta = 45;
  // params.zeta = 0.4;

  // chassisReference->curvedMotionProfile(motionProfile, params);

  // return;

  chassisReference->driveToPose(Pose<double>(-47, 44, 270), {.driveSettleError = 0.1, .driveTimeout = 1400}, {.turnSettleError = 0.1, .turnTimeout = 1300}, {}, 0.22); //.turnSettleError = 0.3, {}, 0.8, 0, 2.4
  willyNilly.on();

  // Ram into 2nd loader
  chassisReference->turnTo(Pose<double>(-68, 45, -360), {}, {});
  // chassisReference->driveToPoint(Pose<double>(-80, 48, 0), driveParams, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(12, 300, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});
  chassisReference->driveWithVoltage(5, 600, chassisReference->getAbsoluteHeading().angle, turnParams10_deg(), {});

  // Line up to long goal
  chassisReference->turnTo(Pose<double>(-24, 47.5, -360), {}, {.forwards = false});
  chassisReference->driveToPoint(Pose<double>(-24, 47.5, 0), {.driveTimeout = 1200}, {}, {.forwards = false});
  willyNilly.off();

  // Score and NOT chill >:(
  blocker.on();
  wait(10000, msec);
}