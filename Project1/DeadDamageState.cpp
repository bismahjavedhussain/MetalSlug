#include "NormalDamageState.h"
#include "DeadDamageState.h"
#include "DamagableEntity.h"


DeadDamageState::DeadDamageState() : DamageState() {}
void DeadDamageState::enter(DamagableEntity* d)
{
    DamageState::enter(d);
    remainingTime = 4.5f;

    if (owner != nullptr)
    {  

		owner->die();
    }
}
void DeadDamageState::update(DamagableEntity* d, float dt)
{
    DamageState::update(d, dt);
    if (remainingTime <= 0.0f)
    {
        if (owner != nullptr) 
        {
            owner->advanceDamageState();
        }
    }
}
float DeadDamageState::hueAlpha()
{
    return 1.0f;
}
DamageState* DeadDamageState::next() 
{ return new NormalDamageState();
}