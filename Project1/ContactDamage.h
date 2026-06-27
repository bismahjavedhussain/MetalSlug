#pragma once
#include "DamageSource.h"

class ContactDamage : public DamageSource
{
    public:
    ContactDamage(Entity* c = nullptr);
    int amount() override;
};
