#pragma once
#include "DamageSource.h"

class FireDamage : public DamageSource
{
    public:
    FireDamage(Entity* c = nullptr);
    int amount() override;
    bool canKillMummy() override;
};