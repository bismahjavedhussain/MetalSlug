#include "CriticalDamageState.h"
#include "InjuredDamageState.h"
#include "DeadDamageState.h"
#include "DamagableEntity.h"


CriticalDamageState::CriticalDamageState() : DamageState() {}

void CriticalDamageState::enter(DamagableEntity* d) 
{
    DamageState::enter(d);
    remainingTime = 1.0f;
}

void CriticalDamageState::update(DamagableEntity* d, float dt) 
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

float CriticalDamageState::hueAlpha() 
{
    return 0.8f;
}

DamageState* CriticalDamageState::next() {
    if (remainingTime <= 0.0f)
    {
        return new InjuredDamageState();
    }
    else 
    {
        return new DeadDamageState();
    }
}