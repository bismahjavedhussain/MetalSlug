#pragma once
#include "Weapon.h"

class Knife : public Weapon
{
    
    private:
    float meleeRange;
    float meleeCooldown;
    public:
    Knife();
    virtual Entity* fire(Soldier* owner, coordSyst aim) override;
    virtual Weapon* clone() override;
};