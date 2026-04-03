// =============================================================================
//  TuningUtil — Controller-driven PID tuning
// =============================================================================
//
//  ENABLE:  set Config::kTuningMode = true in config.h
//
//  NAVIGATION
//    Up     — next preset
//    Left   — previous preset
//    Right  — toggle DRIVE / TURN category (resets index to 0)
//
//  PARAM EDITING
//    R1     — cycle selected param forward  (Kp → Kd → Ki)
//    R2     — cycle selected param backward (Ki → Kd → Kp)
//    L1     — increment selected param  (hold to repeat)
//    L2     — decrement selected param  (hold to repeat)
//
//    Step sizes:
//      Kp  +/- 0.100
//      Kd  +/- 0.100
//      Ki  +/- 0.001
//
//  EXECUTION
//    A      — reset odom to (0,0,0) and run selected move with current params
//    X      — reset odometry only (no move)
//
//  DISPLAY  (3-row controller screen)
//    Row 1  — preset name + [D] or [T] category tag
//    Row 2  — selected param with current value  e.g. ">>Kp: 0.9280"
//    Row 3  — the other two params               e.g. "Kd:4.050  Ki:0.000"
//
//  STORAGE
//    Each preset stores its own Kp/Kd/Ki independently (mirrors params.cpp).
//    Values are initialised from params.cpp on entry and persist for the
//    duration of the driver period.
// =============================================================================

#include "tuningUtil.h"
#include "config.h"
#include "types/params.h"
#include "utils/logger.h"
#include "vex.h"

using namespace vex;

// ---------------------------------------------------------------------------
// Preset tables
// ---------------------------------------------------------------------------

struct DrivePreset
{
  const char *label;
  double distance;
  DriveParams (*initParams)();
};

struct TurnPreset
{
  const char *label;
  double angle;
  TurnParams (*initParams)();
};

static const DrivePreset kDrivePresets[] = {
    {"Drive  5in", 5,   driveParams5_in},
    {"Drive 10in", 10,  driveParams10_in},
    {"Drive 20in", 20,  driveParams20_in},
    {"Drive 30in", 30,  driveParams30_in},
    {"Drive 50in", 50,  driveParams50_in},
    {"Drive100in", 100, driveParams100_in},
};

static const TurnPreset kTurnPresets[] = {
    {"Turn  10deg", 10,  turnParams10_deg},
    {"Turn  30deg", 30,  turnParams30_deg},
    {"Turn  45deg", 45,  turnParams45_deg},
    {"Turn  60deg", 60,  turnParams60_deg},
    {"Turn  90deg", 90,  turnParams90_deg},
    {"Turn 135deg", 135, turnParams135_deg},
    {"Turn 180deg", 180, turnParams180_deg},
};

static constexpr int kDriveCount = sizeof(kDrivePresets) / sizeof(kDrivePresets[0]);
static constexpr int kTurnCount  = sizeof(kTurnPresets)  / sizeof(kTurnPresets[0]);

// ---------------------------------------------------------------------------
// Mutable per-preset param storage — each preset stores its own values,
// initialized from the same functions as params.cpp.
// ---------------------------------------------------------------------------

static DriveParams gDriveParams[kDriveCount];
static TurnParams  gTurnParams[kTurnCount];

static void initParams()
{
  for (int i = 0; i < kDriveCount; ++i)
    gDriveParams[i] = kDrivePresets[i].initParams();
  for (int i = 0; i < kTurnCount; ++i)
    gTurnParams[i] = kTurnPresets[i].initParams();
}

// ---------------------------------------------------------------------------
// Param field selection
// ---------------------------------------------------------------------------

enum ParamField { KP = 0, KD = 1, KI = 2, PARAM_FIELD_COUNT = 3 };

// Per-field step sizes for L1 (+) / L2 (-)
static constexpr double kDriveSteps[PARAM_FIELD_COUNT] = {0.100, 0.100, 0.001};
static constexpr double kTurnSteps[PARAM_FIELD_COUNT]  = {0.100, 0.100, 0.001};

static double &driveField(DriveParams &p, ParamField f)
{
  if (f == KD) return p.driveKd;
  if (f == KI) return p.driveKi;
  return p.driveKp;
}

static double &turnField(TurnParams &p, ParamField f)
{
  if (f == KD) return p.turnKd;
  if (f == KI) return p.turnKi;
  return p.turnKp;
}

// ---------------------------------------------------------------------------
// Display
// ---------------------------------------------------------------------------

enum TuningCategory { TUNING_DRIVE, TUNING_TURN };

static void printScreen(TuningCategory cat, int idx, ParamField field)
{
  double kp, kd, ki;
  if (cat == TUNING_DRIVE) {
    kp = gDriveParams[idx].driveKp;
    kd = gDriveParams[idx].driveKd;
    ki = gDriveParams[idx].driveKi;
  } else {
    kp = gTurnParams[idx].turnKp;
    kd = gTurnParams[idx].turnKd;
    ki = gTurnParams[idx].turnKi;
  }

  const char *label = (cat == TUNING_DRIVE) ? kDrivePresets[idx].label : kTurnPresets[idx].label;
  const char *tag   = (cat == TUNING_DRIVE) ? "[D]" : "[T]";

  Controller.Screen.clearScreen();

  // Row 1: preset label + category tag
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("%-10s %s", label, tag);

  // Row 2: selected param (large / prominent)
  Controller.Screen.setCursor(2, 1);
  if (field == KP)
    Controller.Screen.print(">>Kp: %-10.4f", kp);
  else if (field == KD)
    Controller.Screen.print(">>Kd: %-10.4f", kd);
  else
    Controller.Screen.print(">>Ki: %-10.4f", ki);

  // Row 3: the other two params
  Controller.Screen.setCursor(3, 1);
  if (field == KP)
    Controller.Screen.print("Kd:%.3f  Ki:%.3f", kd, ki);
  else if (field == KD)
    Controller.Screen.print("Kp:%.3f  Ki:%.3f", kp, ki);
  else
    Controller.Screen.print("Kp:%.3f  Kd:%.3f", kp, kd);
}

static void waitForRelease(const vex::controller::button &btn)
{
  while (btn.pressing()) wait(20, msec);
}

// ---------------------------------------------------------------------------
// TuningUtil::run
//
// Controller mapping:
//   Up    — next preset
//   Left  — previous preset
//   Right — toggle TUNING_DRIVE / TUNING_TURN category
//   A     — reset odom to (0,0,0) and run selected move with current params
//   X     — reset odometry only
//   R1    — cycle selected param forward  (Kp → Kd → Ki)
//   R2    — cycle selected param backward (Ki → Kd → Kp)
//   L1    — increment selected param by step (hold to repeat)
//   L2    — decrement selected param by step (hold to repeat)
// ---------------------------------------------------------------------------

void TuningUtil::run(Chassis *chassis)
{
  if (!Config::kTuningMode) return;

  Logger::sendMessage("TuningUtil started");

  initParams();

  chassis->odometry->startPositionTrackThread(true);
  chassis->odometry->setPosition(0, 0, 0);

  TuningCategory cat = TUNING_DRIVE;
  int       index = 0;
  ParamField field = KP;

  printScreen(cat, index, field);

  while (true)
  {
    // ---- Up: next preset ------------------------------------------------
    if (Controller.ButtonUp.pressing())
    {
      int maxIdx = (cat == TUNING_DRIVE) ? kDriveCount : kTurnCount;
      index = (index + 1) % maxIdx;
      printScreen(cat, index, field);
      waitForRelease(Controller.ButtonUp);
    }

    // ---- Left: previous preset ------------------------------------------
    else if (Controller.ButtonLeft.pressing())
    {
      int maxIdx = (cat == TUNING_DRIVE) ? kDriveCount : kTurnCount;
      index = (index - 1 + maxIdx) % maxIdx;
      printScreen(cat, index, field);
      waitForRelease(Controller.ButtonLeft);
    }

    // ---- Right: toggle TUNING_DRIVE / TUNING_TURN category -----------------
    else if (Controller.ButtonRight.pressing())
    {
      cat   = (cat == TUNING_DRIVE) ? TUNING_TURN : TUNING_DRIVE;
      index = 0;
      printScreen(cat, index, field);
      waitForRelease(Controller.ButtonRight);
    }

    // ---- R1: next param field (Kp → Kd → Ki) ----------------------------
    else if (Controller.ButtonR1.pressing())
    {
      field = static_cast<ParamField>((field + 1) % PARAM_FIELD_COUNT);
      printScreen(cat, index, field);
      waitForRelease(Controller.ButtonR1);
    }

    // ---- R2: prev param field (Ki → Kd → Kp) ----------------------------
    else if (Controller.ButtonR2.pressing())
    {
      field = static_cast<ParamField>((field - 1 + PARAM_FIELD_COUNT) % PARAM_FIELD_COUNT);
      printScreen(cat, index, field);
      waitForRelease(Controller.ButtonR2);
    }

    // ---- L1: increment selected param (hold to repeat) ------------------
    else if (Controller.ButtonL1.pressing())
    {
      double step = (cat == TUNING_DRIVE) ? kDriveSteps[field] : kTurnSteps[field];
      if (cat == TUNING_DRIVE)
        driveField(gDriveParams[index], field) += step;
      else
        turnField(gTurnParams[index], field) += step;
      printScreen(cat, index, field);
      wait(150, msec);
    }

    // ---- L2: decrement selected param (hold to repeat) ------------------
    else if (Controller.ButtonL2.pressing())
    {
      double step = (cat == TUNING_DRIVE) ? kDriveSteps[field] : kTurnSteps[field];
      if (cat == TUNING_DRIVE)
        driveField(gDriveParams[index], field) -= step;
      else
        turnField(gTurnParams[index], field) -= step;
      printScreen(cat, index, field);
      wait(150, msec);
    }

    // ---- X: reset odometry only -----------------------------------------
    else if (Controller.ButtonX.pressing())
    {
      chassis->odometry->setPosition(0, 0, 0);
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Odom reset");
      wait(600, msec);
      printScreen(cat, index, field);
      waitForRelease(Controller.ButtonX);
    }

    // ---- A: run selected move with current params -----------------------
    else if (Controller.ButtonA.pressing())
    {
      waitForRelease(Controller.ButtonA);

      chassis->odometry->setPosition(0, 0, 0);
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Running...");

      if (cat == TUNING_DRIVE)
      {
        chassis->driveToPoint(
            Pose<double>(0, kDrivePresets[index].distance, 0),
            gDriveParams[index],
            gTurnParams[0],
            {.sendPositionData = true});
      }
      else
      {
        chassis->turnTo(
            Pose<double>(0, 0, kTurnPresets[index].angle),
            gTurnParams[index],
            {.sendPositionData = true});
      }

      printScreen(cat, index, field);
    }

    wait(20, msec);
  }
}
