#pragma once

#include "Entity.h"
class Soldier;

class Weapon
{
    protected:
    int damage;
    int ammo;
    float fireRate;
    int maxAmmo;

    public:
    Weapon(int dmg, int startAmmo, float rate, int max);
    virtual ~Weapon() = default;


    virtual Entity* fire(Soldier* owner, coordSyst aim) = 0;


    virtual Weapon* clone() = 0;
    void consumeAmmo();
    int getAmmo() const;
    bool hasAmmo() const;
    float getFireRate() const;




    void refillByPercent(float frac);



    virtual const char* getAnimPrefix() const { return "pistol"; }
};