#include "InjuredDamageState.h"
#include "NormalDamageState.h"
#include "CriticalDamageState.h"
#include "DamagableEntity.h"

InjuredDamageState::InjuredDamageState() : DamageState() {}

void InjuredDamageState::enter(DamagableEntity* d)
{
    DamageState::enter(d);

    remainingTime = 1.0f;
}
void InjuredDamageState::update(DamagableEntity* d, float dt)
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
float InjuredDamageState::hueAlpha()
{
    return 0.3f;
}
DamageState* InjuredDamageState::next()
{
    if (remainingTime <= 0.0f)
    {
        return (new NormalDamageState());
    }
    else
    {
        return (new CriticalDamageState());
    }
}