#include "SupplyCrate.h"
#include "PlayerSoldier.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Grenade.h"
#include "HeavyMachineGun.h"
#include "FlameShot.h"
#include "RocketLauncher.h"
#include "LaserGun.h"
#include "EntityAnims.h"


static unsigned lcg(unsigned& seed)
{
    seed = seed * 1664525u + 1013904223u;
    return seed;
}

static Weapon* rollWeapon(unsigned& seed)
{
    unsigned r = lcg(seed) % 100u;
    if (r < 30) return new HeavyMachineGun();
    if (r < 60) return new FlameShot();
    if (r < 90) return new RocketLauncher();
    return new LaserGun();
}

SupplyCrate::SupplyCrate(TextureManager& tm, float spawnX, float spawnY, unsigned seed)
    : Collectible(),
      containedWeapon(nullptr),
      containedHandGrenades(0),
      containedFireBombs(0),
      containedGrenadePrototype(nullptr)
{
    setupSupplyCrateAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 48.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 32.0f;
    position.x = spawnX;
    position.y = spawnY;

    containedWeapon       = rollWeapon(seed);

    containedHandGrenades = 3 + (int)(lcg(seed) % 3u);
    containedFireBombs    = 1 + (int)(lcg(seed) % 3u);
}

SupplyCrate::~SupplyCrate()
{
    if (containedWeapon != nullptr)            { delete containedWeapon;            containedWeapon = nullptr; }
    if (containedGrenadePrototype != nullptr)  { delete containedGrenadePrototype;  containedGrenadePrototype = nullptr; }
}

void SupplyCrate::onPickup(PlayerSoldier* p, PlayState& )
{
    if (p == nullptr || consumed) 
    return;
    Inventory& inv = p->getInventory();
    Grenade* myProto = inv.getGrenadePrototype();
    if (myProto != nullptr)
    {
        const int handGrenadesGiven = containedHandGrenades + containedFireBombs;
        inv.addGrenades(handGrenadesGiven);
    }

    if (containedWeapon != nullptr)
    {
        Weapon* w = containedWeapon;
        containedWeapon = nullptr;
        p->pickupWeapon(w);
    }

    consumed = true;
    isAlive  = false;
}
