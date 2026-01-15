#include "autons.h"
#include "vex.h"
#include "types/params.h"

using namespace vex;
using namespace std;

// 2.7330
// 2.78542

// 2.74552
// 2.73952
// 2.73999

///// Sideways
// 5.09216
// 5.01728
// 4.99967

///// Forwards
// 0.0071588
// 0.0335398
// 0.0544831

void Autons::tuning()
{
  /*=============================================================
  |                   Part 1 - Wheel Diameters                  |
  |                                                             |
  | Call the getWheelDiameters functions for both the           |
  | forward and sideways trackers. Get the updated diameters    |
  | and plug those back into the function around 3 times. Once  |
  | it's tuned PLUG THE VALUES INTO THE DEGREES TO INCHES RATIO |
  | INSIDE main.cpp otherwise the next step won't work.         |
  =============================================================*/
  // chassisReference->odometry->getWheelDiameters(0, 2.71795); // Forward tracker
  // chassisReference->odometry->getWheelDiameters(1, 1.98922); // Sideways tracker

  /*=============================================================
  |                   Part 2 - Wheel Offsets                    |
  | Tune the wheel offsets next by simply calling the function. |
  | You have to rotate the bot around using the joysticks and   |
  | it will record how far the encoders travelled. It will use  |
  | the wheel diameters from before so make sure thoser are     |
  | accurate and tuned well.                                    |
  =============================================================*/
  chassisReference->odometry->getWheelOffsets();

  /*=============================================================
  |                    Part 3 - Gyro Scaling                    |
  | Rotate the bot around 10 times, get the degrees from the    |
  | inertial and divide that by 3600 to get the gyro scale.     |
  =============================================================*/
  // int iterations = 5;
  // double differences = 0;
  // for (int i = 0; i < iterations; ++i)
  // {
  //   chassisReference->calibrateInertial();
  //   Logger::sendMessage("Rotate the bot 5 times. Then press A.");
  //   while (!Controller.ButtonA.pressing())
  //     wait(50, msec);
  //   wait(500, msec);
  //   differences += 360 - Inertial.heading(deg);
  //   cout << (360 - Inertial.heading(deg)) << endl;
  // }
  // cout << "Gryo scale: " << (360 * iterations - (differences / iterations)) / iterations << endl;

  /*=============================================================
  |                   Part 4 - Test odometry                    |
  | Simply make sure the odom is accurate now by moving the bot |
  | around, curving it, etc. Use the joysticks for this. Use    |
  | the visualizer to see where the bot thinks it is.           |
  =============================================================*/
  // chassisReference->odometry->startPositionTrackThread(true);

  /*=============================================================
  |                   Part 5 - Tune the PIDs                     |
  | Tune the PIDs in the order given below. Up the P until it    |
  | oscillates, then dampen it with the D, and, if necessary,    |
  | add the I.                                                   |
  =============================================================*/

  // -----------------------------
  // Turn tuning (small -> large)
  // Uncomment one line at a time to test each turn with the corresponding TurnParams
  // Note: target.pose orientation uses absolute angles (degrees)
  // -----------------------------

  // Turn 10 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 10), turnParams10_deg(), {});

  // Turn 30 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 30), turnParams30_deg(), {});

  // Turn 45 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 45), turnParams45_deg(), {});

  // Turn 60 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 60), turnParams60_deg(), {});

  // Turn 90 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 90), turnParams90_deg(), {});

  // Turn 135 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 135), turnParams135_deg(), {});

  // Turn 180 degrees
  // chassisReference->turnTo(Pose<double>(0, 0, 180), turnParams180_deg(), {});

  // -----------------------------
  // Drive distance tuning (small -> large)
  // Uncomment one line at a time to test each distance with the corresponding DriveParams
  // -----------------------------

  // Drive 5 inches forward
  // chassisReference->driveToPoint(Pose<double>(0, 5, 0), driveParams5_in(), turnParams10_deg(), {});

  // Drive 10 inches forward
  // chassisReference->driveToPoint(Pose<double>(0, 10, 0), driveParams10_in(), turnParams10_deg(), {});

  // Drive 20 inches forward
  // chassisReference->driveToPoint(Pose<double>(0, 20, 0), driveParams20_in(), turnParams10_deg(), {});
  // chassisReference->driveDistance(20, 0, driveParams20_in(), turnParams10_deg(), {});

  // Drive 30 inches forward
  // chassisReference->driveDistance(30, 0, driveParams30_in(), turnParams10_deg(), {});

  // Drive 50 inches forward
  // chassisReference->driveDistance(50, 0, driveParams50_in(), turnParams10_deg(), {});
}