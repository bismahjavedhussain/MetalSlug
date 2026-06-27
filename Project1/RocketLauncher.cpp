#include "RocketLauncher.h"
#include "Soldier.h"
#include "Rocket.h"


RocketLauncher::RocketLauncher() : ProjectileWeapon(5, 30, 2.0f, 30, coordSyst(20.0f, -10.0f)), reloadTimer(0.0f) {}

Entity* RocketLauncher::fire(Soldier* owner, coordSyst aim)
{
    if (!hasAmmo()) 
    {
        return nullptr;
    }
    consumeAmmo();
    return spawnProjectile(owner, aim);
}

Projectile* RocketLauncher::spawnProjectile(Soldier* owner, coordSyst aim)
{
    float blastRad = 96.0f;
    Rocket* r = new Rocket(owner, damage, aim, 300.0f, 1200.0f, blastRad);
    if (owner != nullptr)
    {
        coordSyst op = owner->getPosition();
        float ox = (aim.x < 0.0f) ? op.x - 8.0f
                                  : op.x + owner->getWidth() + 8.0f;
        float oy = op.y + owner->getHeight() * 0.40f;
        r->setPosition(ox, oy);
    }
    return r;
}

Weapon* RocketLauncher::clone() 
{
    return new RocketLauncher(*this);
}