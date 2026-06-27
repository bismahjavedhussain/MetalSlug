#pragma once
#include "GrenadeProjectile.h"

class FirePool;
class FireBombProjectile : public GrenadeProjectile
{
private:
    float     poolRadius;
    float     poolDuration;
    FirePool* pendingPool;

public:
    FireBombProjectile(Entity* shooter, int dmg, coordSyst dir, float spd, float grav,
                       float bRadius, float pRadius, float pDur);
    ~FireBombProjectile() override;

    virtual void onImpact() override;
    FirePool*    takePendingPool();

    FireBombProjectile* asFireBombProjectile() override { return this; }
    Entity* takePendingSpawn() override;
};
