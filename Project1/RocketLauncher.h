#pragma once
#include "ProjectileWeapon.h"

class RocketLauncher : public ProjectileWeapon
{
    private:

    float reloadTimer;
    public:
    RocketLauncher();
    virtual Entity* fire(Soldier* owner, coordSyst aim) override;
    virtual Projectile* spawnProjectile(Soldier* owner, coordSyst aim) override;
    virtual Weapon* clone() override;
    const char* getAnimPrefix() const override { return "rocket"; }
};