#include "../../include/subsystems/pneumatic.h"

using namespace std;
using namespace vex;

vex::triport::port enumToTriport(Port port)
{
  switch (port)
  {
  case A:
    return Brain.ThreeWirePort.A;
  case B:
    return Brain.ThreeWirePort.B;
  case C:
    return Brain.ThreeWirePort.C;
  case D:
    return Brain.ThreeWirePort.D;
  case E:
    return Brain.ThreeWirePort.E;
  case F:
    return Brain.ThreeWirePort.F;
  case G:
    return Brain.ThreeWirePort.G;
  case H:
    return Brain.ThreeWirePort.H;
  default:
    break;
  }
}

Pneumatic::Pneumatic(Port port)
{
  vex::triport::port triportValue = enumToTriport(port);
  this->piston = new digital_out(triportValue);
}

Pneumatic willyNilly(Port::A);
Pneumatic finger(Port::B);
Pneumatic sloper(Port::C);
Pneumatic blocker(Port::D);