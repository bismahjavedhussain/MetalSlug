#pragma once
#include "coordSyst.h"

class Entity;
class Projectile;
class Grenade
{
protected:
    float blastRadius;
    int   damage;

public:
    Grenade(float radius = 96.0f, int dmg = 5)
        : blastRadius(radius), damage(dmg) {}
    virtual ~Grenade() = default;

    virtual Grenade*    clone()                                              = 0;
    virtual Projectile* spawnProjectile(Entity* owner, coordSyst aim)        = 0;

    float getBlastRadius() const { return blastRadius; }
    int   getDamage()      const { return damage;      }
};
