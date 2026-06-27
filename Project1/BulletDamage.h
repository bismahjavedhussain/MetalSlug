#pragma once
#include "DamageSource.h"


class BulletDamage : public DamageSource
{
    public:
    BulletDamage(Entity* c = nullptr);
    int amount() override;
};