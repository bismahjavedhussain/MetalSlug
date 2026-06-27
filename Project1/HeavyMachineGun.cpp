#include "HeavyMachineGun.h"
#include "Soldier.h"
#include "Bullet.h"

HeavyMachineGun::HeavyMachineGun() : ProjectileWeapon(3, 200, 0.125f, 200, coordSyst(15.0f, -5.0f)) {}

Entity* HeavyMachineGun::fire(Soldier* owner, coordSyst aim)
{
    if (!hasAmmo()) 
    {
        return nullptr;
    }
    consumeAmmo();
    return (spawnProjectile(owner, aim));
}
Projectile* HeavyMachineGun::spawnProjectile(Soldier* owner, coordSyst aim)
{
    Bullet* b = new Bullet(owner, damage, aim, 1000.0f, 1000.0f);
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
Weapon* HeavyMachineGun::clone() 
{
    return new HeavyMachineGun(*this);
}