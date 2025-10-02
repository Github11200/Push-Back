#ifndef BEZIER_H
#define BEZIER_H

class Bezier
{
private:
public:
    double distanceAlongPath(double t);
    double firstOrderDerivative(double t);
    double secondOrderDerivative(double t);
};

#endif