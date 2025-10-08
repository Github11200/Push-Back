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

extern digital_out willyNilly;
extern digital_out winger;
extern digital_out sloper;
extern digital_out blocker;

extern bool stopPlease;

void vexcodeInit(void);