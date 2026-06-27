#include "Tarma.h"
#include "EntityAnims.h"
#include "TextureManager.h"



Tarma::Tarma(TextureManager& tm)
    : PlayerSoldier(24),
      vehicleFireRateMult(1.25f),
      vehicleDurabilityMult(1.20f)
{
    speedMultiplier = 0.8f;
    setupTarmaNormal(m_normal, tm);
}

void Tarma::specialPowerUp()
{
    powerUpActive  = true;
    powerUpTimer   = 20.0f;
    isInvelnerable = true;
}

void Tarma::onPowerUpExpire()
{
    isInvelnerable = false;
}




bool Tarma::onVehicleDestroyed()
{
    return true;
}
