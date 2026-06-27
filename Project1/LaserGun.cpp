#include "LaserGun.h"
#include "Soldier.h"
#include "EnergyBeam.h"
#include <cmath>

LaserGun::LaserGun() : ProjectileWeapon(999, 50, 0.5f, 50, coordSyst(20.0f, 0.0f)) {}

Entity* LaserGun::fire(Soldier* owner, coordSyst aim) 
{
    if (!hasAmmo())
    {
        return nullptr;
    }
    consumeAmmo();
    return spawnProjectile(owner, aim);
}
Projectile* LaserGun::spawnProjectile(Soldier* owner, coordSyst aim)
{
    float beamRange    = 2000.0f;
    float beamLifetime = 0.20f;
    float beamSpeed    = 4000.0f;
    bool  isInstaKill  = true;

    EnergyBeam* beam = new EnergyBeam(owner, damage, aim, beamSpeed,
                                      beamRange, beamLifetime, isInstaKill);
    if (owner != nullptr)
    {
        coordSyst op = owner->getPosition();
        float ox = (aim.x < 0.0f) ? op.x - 8.0f
                                  : op.x + owner->getWidth() + 8.0f;
        float oy = op.y + owner->getHeight() * 0.40f;
        beam->setPosition(ox, oy);
    }
    return beam;
}

Weapon* LaserGun::clone()
{
    return new LaserGun(*this);
}