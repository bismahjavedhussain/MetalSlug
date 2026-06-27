#include "Marco.h"
#include "EntityAnims.h"
#include "TextureManager.h"

Marco::Marco(TextureManager& tm)
    : PlayerSoldier(30)
{
    fireRateMultiplier = 1.25f;
    inventory.addGrenades(-2);
    setupMarcoNormal          (m_normal, tm);
    setupMarcoTransformations (m_normal, tm);

    width  = 40.f;
    height = 64.f;
}

void Marco::specialPowerUp()
{
    powerUpActive = true;
    powerUpTimer  = 10.f;
}
