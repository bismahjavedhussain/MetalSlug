#include "FatPistol.h"
#include "FatBullet.h"
#include "Soldier.h"

FatPistol::FatPistol()
    : ProjectileWeapon(6, -1, 0.35f, -1, coordSyst(10.0f, -5.0f))
{
}

Entity* FatPistol::fire(Soldier* owner, coordSyst aim)
{
    if (!hasAmmo()) return nullptr;
    consumeAmmo();
    return spawnProjectile(owner, aim);
}
Projectile* FatPistol::spawnProjectile(Soldier* owner, coordSyst aim)
{
    FatBullet* b = new FatBullet(owner, damage, aim, 650.0f, 1600.0f);
    if (owner != nullptr)
    {
        coordSyst op = owner->getPosition();
        float ox = (aim.x < 0.0f) ? op.x - 8.0f
                                  : op.x + owner->getWidth() + 8.0f;
        float oy = op.y + owner->getHeight() * 0.40f;
        b->setPosition(ox, oy);
    }
    return b;
}

Weapon* FatPistol::clone()
{
    return new FatPistol(*this);
}
