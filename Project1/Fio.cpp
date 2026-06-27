#include "Fio.h"
#include "Weapon.h"
#include "EntityAnims.h"
#include "TextureManager.h"

Fio::Fio(TextureManager& tm)
    : PlayerSoldier(30)
{
    fireRateMultiplier    = 1.10f;
    meleeDamageMultiplier = 0.75f;
    ammoPickupMultiplier  = 1.50f;
    inventory.addGrenades(-2);

    setupFioNormal(m_normal, tm);
}

void Fio::specialPowerUp()
{
    powerUpActive = true;
    powerUpTimer  = 10.0f;

}

void Fio::pickupWeapon(Weapon* w)
{
    if (w != nullptr)
    {
        w->refillByPercent(0.5f);
    }
    PlayerSoldier::pickupWeapon(w);
}
