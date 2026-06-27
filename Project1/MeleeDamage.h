#pragma once
#include "DamageSource.h"

class MeleeDamage : public DamageSource 
{
    public:
    MeleeDamage(Entity* c = nullptr);
    int amount() override;
};