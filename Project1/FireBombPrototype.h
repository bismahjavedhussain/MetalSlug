#pragma once
#include "Grenade.h"

class FireBombPrototype : public Grenade
{
public:
    FireBombPrototype();
    Grenade*    clone()                                          override;
    Projectile* spawnProjectile(Entity* owner, coordSyst aim)    override;
};
