#include "NormalDamageState.h"
#include "InjuredDamageState.h"

NormalDamageState::NormalDamageState() : DamageState() {}

void NormalDamageState::enter(DamagableEntity* d)
{
    DamageState::enter(d);
    remainingTime = 0.0f;
}

float NormalDamageState::hueAlpha()
{
    return 0.0f;
}
DamageState* NormalDamageState::next()
{
    return new InjuredDamageState();
}