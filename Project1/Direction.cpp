#include "Direction.h"

int LeftDirection::getXSign()  { return -1; }
Direction* LeftDirection::flip(){ return new RightDirection(); }
Direction* LeftDirection::clone(){ return new LeftDirection();  }

int RightDirection::getXSign() { return +1; }
Direction* RightDirection::flip(){ return new LeftDirection();  }
Direction* RightDirection::clone(){ return new RightDirection(); }
