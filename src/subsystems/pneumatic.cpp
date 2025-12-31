#include "subsystems/pneumatic.h"

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
  this->pistonPort = std::make_unique<vex::triport::port>(vex::triport::port(enumToTriport(port)));
}

// Pneumatic::~Pneumatic()
// {
//   delete pistonPort;
// }

digital_out Pneumatic::getPiston()
{
  return digital_out(*(this->pistonPort));
}

void Pneumatic::delayToggle(int milliseconds)
{
  static Pneumatic *thisPointer = this;
  Brain.Timer.event([]()
                    { thisPointer->on(); },
                    milliseconds);
}

Pneumatic willyNilly(Port::A);
Pneumatic finger(Port::C);
Pneumatic sloper(Port::B);
Pneumatic blocker(Port::A);