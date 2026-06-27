#pragma once
#pragma once
#include "DamageState.h"
class NormalDamageState;

class DeadDamageState : public DamageState 
{
    public:
    DeadDamageState();
    virtual ~DeadDamageState() = default;
    virtual void enter(DamagableEntity* d) override;
    virtual void update(DamagableEntity* d, float dt) override;
    virtual float hueAlpha() override;
    virtual DamageState* next() override;
};