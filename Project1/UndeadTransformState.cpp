#include "UndeadTransformState.h"
#include "NormalTransformState.h"
#include "Soldier.h"

UndeadTransformState::UndeadTransformState() : TransformationState(10.0f) {}

void UndeadTransformState::enter(Soldier* s)
{
    owner = s;
    if (s != nullptr) s->scaleBaseSpeed(0.5f);
}

void UndeadTransformState::exit(Soldier* s)
{
    if (s != nullptr) s->scaleBaseSpeed(2.0f);
}

void UndeadTransformState::update(Soldier* s, float dt)
{
    duration -= dt;
    if (duration <= 0.0f)
        s->changeState(new NormalTransformState());
}
