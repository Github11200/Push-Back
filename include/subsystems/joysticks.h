#ifndef JOYSTICKS_H
#define JOYSTICKS_H

#include "vex.h"
#include "../utils/utils.h"

class Joysticks
{
private:
    void control(double power, double turning);

public:
    void arcade();
    void tank();
};

#endif