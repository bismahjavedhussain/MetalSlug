#pragma once
#include "ProjectileWeapon.h"

class HeavyMachineGun : public ProjectileWeapon 
{
    public:
    HeavyMachineGun();
    virtual Entity* fire(Soldier* owner, coordSyst aim) override;
    virtual Projectile* spawnProjectile(Soldier* owner, coordSyst aim) override;
    virtual Weapon* clone() override;
    const char* getAnimPrefix() const override { return "hmg"; }
};