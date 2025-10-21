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
  this->pistonPort = new vex::triport::port(enumToTriport(port));
}

digital_out Pneumatic::getPiston()
{
  return digital_out(*(this->pistonPort));
}

void Pneumatic::killThread(vex::thread *currentDelayThread)
{
  while (!currentDelayThread->joinable())
    wait(5, msec);
  currentDelayThread->join();
  delete currentDelayThread;
}

void Pneumatic::delayToggle(int milleseconds)
{
  static Pneumatic *thisPointer = this;
  static int staticMilleseconds = milleseconds;
  thread *delayThread = new thread([]()
                                   {
    wait(staticMilleseconds, msec);
    thisPointer->on(); });
  killThread(delayThread);
}

Pneumatic willyNilly(Port::D);
Pneumatic finger(Port::B);
Pneumatic sloper(Port::A);
Pneumatic blocker(Port::C);