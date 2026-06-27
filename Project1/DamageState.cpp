#include "DamageState.h"

DamageState::DamageState() : owner(nullptr), remainingTime(0.0f){}

void DamageState::enter(DamagableEntity* d)
{ owner = d;
}
void DamageState::exit(DamagableEntity* d)
{

    owner = nullptr;
}
void DamageState::update(DamagableEntity* d, float dt)
{
    if (remainingTime > 0.0f) 
    {
        remainingTime -= dt;
    }
}