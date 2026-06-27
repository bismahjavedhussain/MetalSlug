#include "HandGrenadePrototype.h"
#include "GrenadeProjectile.h"

HandGrenadePrototype::HandGrenadePrototype()
    : Grenade(192.0f, 5) {}

Grenade* HandGrenadePrototype::clone()
{
    return new HandGrenadePrototype(*this);
}
Projectile* HandGrenadePrototype::spawnProjectile(Entity* owner, coordSyst aim)
{
    const float THROW_SPEED = 350.0f;
    const float GRAVITY     = 1200.0f;
    GrenadeProjectile* g = new GrenadeProjectile(owner, damage, aim, THROW_SPEED, GRAVITY, blastRadius);
    if (owner != nullptr)
    {
        coordSyst op = owner->getPosition();
        float ox = (aim.x < 0.0f) ? op.x - 8.0f : op.x + owner->getWidth() + 8.0f;
        float oy = op.y + owner->getHeight() * 0.30f;
        g->setPosition(ox, oy);
    }
    return g;
}
