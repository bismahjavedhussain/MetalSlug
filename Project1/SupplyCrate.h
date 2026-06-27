#pragma once
#include "Collectible.h"
#include "TextureManager.h"

class Weapon;
class Grenade;
class SupplyCrate : public Collectible
{
private:
    Weapon*   containedWeapon;
    int       containedHandGrenades;
    int       containedFireBombs;
    Grenade*  containedGrenadePrototype;

public:


    SupplyCrate(TextureManager& tm, float spawnX, float spawnY, unsigned seed);
    ~SupplyCrate() override;

    void onPickup(PlayerSoldier* p, PlayState& ps) override;
};
