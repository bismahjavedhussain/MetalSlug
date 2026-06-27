#pragma once
#include "ProjectileWeapon.h"

class LaserGun : public ProjectileWeapon 
{
    public:
    LaserGun();
    virtual Entity* fire(Soldier* owner, coordSyst aim) override;
    virtual Projectile* spawnProjectile(Soldier* owner, coordSyst aim) override;
    virtual Weapon* clone() override;
    const char* getAnimPrefix() const override { return "laser"; }
};