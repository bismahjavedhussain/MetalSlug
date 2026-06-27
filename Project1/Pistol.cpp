#include "Pistol.h"
#include "Soldier.h"
#include "Bullet.h"

Pistol::Pistol() : ProjectileWeapon(3, -1, 0.25f, -1, coordSyst(10.0f, -5.0f)) {
}

Entity* Pistol::fire(Soldier* owner, coordSyst aim) {
    if (!hasAmmo())
    {
        return nullptr;
    }
    consumeAmmo();
    return spawnProjectile(owner, aim);
}

Projectile* Pistol::spawnProjectile(Soldier* owner, coordSyst aim)
{
    Bullet* b = new Bullet(owner, damage, aim, 700.0f, 1600.0f);
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

Weapon* Pistol::clone()
{
    return new Pistol(*this);
}