#include "ProjectileWeapon.h"

ProjectileWeapon::ProjectileWeapon(int dmg, int startAmmo, float rate, int max, coordSyst offset) : Weapon(dmg, startAmmo, rate, max), muzzleOffset(offset) {}

Projectile* ProjectileWeapon::spawnProjectile(Soldier* owner, coordSyst aim) 
{
    return nullptr;
}