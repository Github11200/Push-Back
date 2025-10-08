#include "../../include/driver/pneumatic.h"

using namespace std;
using namespace vex;

Pneumatic::Pneumatic(digital_out& piston_in) {
  this->piston = piston_in;
}

void Pneumatic::toggle() {
  // piston.set(!piston.value());
}