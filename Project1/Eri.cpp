#include "Eri.h"
#include "FireBombPrototype.h"
#include "Direction.h"
#include "Projectile.h"
#include "EntityAnims.h"
#include "TextureManager.h"

Eri::Eri(TextureManager& tm)
    : PlayerSoldier(30)
{
    canMelee              = false;
    fireRateMultiplier    = 0.8f;
    blastRadiusMultiplier = 1.5f;
    inventory.addGrenades(10);
    inventory.setGrenadePrototype(new FireBombPrototype());
    setupEriNormal(m_normal, tm);
}

void Eri::specialPowerUp()
{
    powerUpActive = true;
    powerUpTimer  = 10.0f;
}

void Eri::throwGrenade()
{
    Grenade* g = inventory.consumeGrenade();
    if (g == nullptr) return;
    m_grenTimer = 0.6f;
    coordSyst aim;
    aim.x = (facing != nullptr) ? (float)facing->getXSign() : 1.0f;
    aim.y = -0.6f;
    Projectile* p = g->spawnProjectile(this, aim);
    if (p != nullptr) pendingProjectile = p;
    delete g;

    if (powerUpActive)
    {

        Grenade* g2 = inventory.getGrenadePrototype();
        if (g2 != nullptr)
        {

            coordSyst aim2;
            aim2.x = aim.x * 1.4f;
            aim2.y = aim.y;
            Grenade* shot2 = g2->clone();
            Projectile* p2 = shot2->spawnProjectile(this, aim2);
            if (pendingProjectile == nullptr) pendingProjectile = p2;
            else if (p2 != nullptr) delete p2;
            delete shot2;
        }
    }
}

void Eri::meleeAttack()
{

}
