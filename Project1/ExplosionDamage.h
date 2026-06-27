#pragma once
#include "DamageSource.h"

class ExplosionDamage : public DamageSource 
{
    private:
    float radius;
    public:
    ExplosionDamage(Entity* c, float r);
    int amount() override;
    bool canKillMummy() override;
    bool isExplosive() override;
};