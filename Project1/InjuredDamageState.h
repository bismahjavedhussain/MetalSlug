#pragma once
#include "DamageState.h"


class HealthyState;
class CriticalState;
class InjuredDamageState : public DamageState
{
    public:
    InjuredDamageState();
    virtual void enter(DamagableEntity* d) override;
    virtual void update(DamagableEntity* d, float dt) override;
    virtual float hueAlpha() override;
    virtual DamageState* next() override;
    virtual ~InjuredDamageState() = default;
};