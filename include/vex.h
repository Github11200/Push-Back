#ifndef VEX_H
#define VEX_H

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <limits.h>
#include <algorithm>
#include <ctime>
#include <sstream>

#include "v5.h"
#include "v5_vcs.h"
#include "robot-config.h"
#include "functional"
#include "utils/logger.h"

#define waitUntil(condition) \
  do                         \
  {                          \
    wait(5, msec);           \
  } while (!(condition))

#define repeat(iterations) \
  for (int iterator = 0; iterator < iterations; iterator++)

#endif