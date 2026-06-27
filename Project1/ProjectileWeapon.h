#pragma once
#include "Weapon.h"

class Projectile;

class ProjectileWeapon : public Weapon
{
    protected:
    coordSyst muzzleOffset;
    public:
    ProjectileWeapon(int dmg, int startAmmo, float rate, int max, coordSyst offset);
    virtual Projectile* spawnProjectile(Soldier* owner, coordSyst aim);
};