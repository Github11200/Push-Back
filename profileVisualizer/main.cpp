#include "../include/types/angle.h"
#include "../include/types/vector.h"
#include "../include/types/pose.h"
#include "../include/odometry/odometry.h"
#include "../include/types/motionProfilePose.h"
#include <iostream>

using namespace std;

int main() {
  Angle<double> woah(50);
  cout << woah.angle << endl;
  return 0;
}
