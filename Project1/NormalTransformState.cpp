#include "NormalTransformState.h"

NormalTransformState::NormalTransformState() : TransformationState(0.0f) {}
void NormalTransformState::enter(Soldier* s)
{ 
	owner = s;
}
void NormalTransformState::exit(Soldier* s) {}
void NormalTransformState::update(Soldier* s, float dt) {}