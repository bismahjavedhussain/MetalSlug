#include "Weapon.h"

Weapon::Weapon(int dmg, int startAmmo, float rate, int max) : damage(dmg), ammo(startAmmo), fireRate(rate), maxAmmo(max) {}

void Weapon::consumeAmmo() 
{
    if (maxAmmo != -1 && ammo > 0) {
        ammo--;
    }
}

int Weapon::getAmmo() const 
{ 
    return (ammo);
}

bool Weapon::hasAmmo() const
{
    return (maxAmmo == -1 || ammo > 0);
}

float Weapon::getFireRate() const
{
    return (fireRate);
}

void Weapon::refillByPercent(float frac)
{
    if (maxAmmo == -1) return;
    int bump = (int)((float)maxAmmo * frac);
    ammo += bump;
    if (ammo > maxAmmo) ammo = maxAmmo;
}