using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller;

extern motor FrontRight;
extern motor FrontLeft;
extern motor MiddleRight;
extern motor MiddleLeft;
extern motor BackRight;
extern motor BackLeft;

extern vex::distance frontDistance;
extern vex::distance rightDistance;
extern vex::distance leftDistance;

extern motor_group Left;
extern motor_group Right;

extern bool stopPlease;

void vexcodeInit(void);