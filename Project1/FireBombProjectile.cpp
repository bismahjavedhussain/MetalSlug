#include "FireBombProjectile.h"
#include "FirePool.h"

FireBombProjectile::FireBombProjectile(Entity* shooter, int dmg, coordSyst dir, float spd,
                                       float grav, float bRadius,
                                       float pRadius, float pDur)
    : GrenadeProjectile(shooter, dmg, dir, spd, grav, bRadius),
      poolRadius(pRadius), poolDuration(pDur),
      pendingPool(nullptr) {}

FireBombProjectile::~FireBombProjectile()
{
    if (pendingPool != nullptr)
    {
        delete pendingPool;
        pendingPool = nullptr;
    }
}
void FireBombProjectile::onImpact()
{
    if (pendingPool == nullptr)
    {
        coordSyst centre = position;
        centre.x += width  * 0.5f;
        centre.y += height * 0.5f;
        pendingPool = new FirePool(centre, poolRadius, poolDuration);
    }
    isAlive = false;
}

FirePool* FireBombProjectile::takePendingPool()
{
    FirePool* p = pendingPool;
    pendingPool = nullptr;
    return p;
}

Entity* FireBombProjectile::takePendingSpawn()
{
    return takePendingPool();
}
