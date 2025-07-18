#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <limits.h>
#include <algorithm>
#include "v5.h"
#include "v5_vcs.h"
#include "robot-config.h"
#include "functional"

#include "types/params.h"
#include "types/vector.h"
#include "types/angle.h"
#include "types/pose.h"

#include "utils.h"
#include "odometry/odometry.h"
#include "pid/pid.h"

#include "chassis.h"

#define waitUntil(condition) \
  do                         \
  {                          \
    wait(5, msec);           \
  } while (!(condition))

#define repeat(iterations) \
  for (int iterator = 0; iterator < iterations; iterator++)