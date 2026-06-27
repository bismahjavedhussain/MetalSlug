#pragma once
#include "Grenade.h"


class HandGrenadePrototype : public Grenade
{
public:
    HandGrenadePrototype();
    Grenade*    clone()                                          override;
    Projectile* spawnProjectile(Entity* owner, coordSyst aim)    override;
};
