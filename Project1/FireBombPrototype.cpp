#include "FireBombPrototype.h"
#include "FireBombProjectile.h"


FireBombPrototype::FireBombPrototype()
    : Grenade(192.0f, 5) {}

Grenade* FireBombPrototype::clone()
{
    return new FireBombPrototype(*this);
}

Projectile* FireBombPrototype::spawnProjectile(Entity* owner, coordSyst aim)
{
    const float THROW_SPEED  = 350.0f;
    const float GRAVITY      = 1200.0f;
    const float POOL_RADIUS  = 192.0f;
    const float POOL_DURATION = 10.0f;
    FireBombProjectile* fb = new FireBombProjectile(owner, damage, aim,
                                                    THROW_SPEED, GRAVITY, blastRadius,
                                                    POOL_RADIUS, POOL_DURATION);
    if (owner != nullptr)
    {
        coordSyst op = owner->getPosition();
        float ox = (aim.x < 0.0f) ? op.x - 8.0f
                                  : op.x + owner->getWidth() + 8.0f;
        float oy = op.y + owner->getHeight() * 0.30f;
        fb->setPosition(ox, oy);
    }
    return fb;
}
