#ifndef TUNING_UTIL_H
#define TUNING_UTIL_H

#include "chassis.h"

// Controller button layout in tuning mode:
//   Up    - next preset
//   Left  - previous preset
//   Right - toggle DRIVE / TURN category
//   A     - run selected move with current params (resets odom first)
//   X     - reset odometry only
//   R1    - cycle selected param forward  (Kp → Kd → Ki)
//   R2    - cycle selected param backward (Ki → Kd → Kp)
//   L1    - increment selected param (hold to repeat)
//   L2    - decrement selected param (hold to repeat)
//
// PID params are stored individually per preset and initialized from params.cpp.
// Edits are live — pressing A immediately uses the modified values.

class TuningUtil
{
public:
    static void run(Chassis *chassis);
};

#endif
