#pragma once
#include "DamageState.h"


class InjuredDamageState;
class DeadDamageState;

class CriticalDamageState : public DamageState {
    public:
    CriticalDamageState();

    virtual ~CriticalDamageState() = default;

    virtual void enter(DamagableEntity* d) override;
    virtual void update(DamagableEntity* d, float dt) override;
    virtual float hueAlpha() override;
    virtual DamageState* next() override;
};
