#pragma once
#include "PlayerSoldier.h"

class TextureManager;


class Tarma : public PlayerSoldier
{
    float vehicleFireRateMult;
    float vehicleDurabilityMult;

public:
    Tarma(TextureManager& tm);

    void specialPowerUp() override;
    void onPowerUpExpire() override;
    bool onVehicleDestroyed() override;



    float getVehicleFireRateMult()    const override { return vehicleFireRateMult;   }
    float getVehicleDurabilityMult()  const override { return vehicleDurabilityMult; }
};
