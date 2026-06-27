#pragma once
#include "PlayerSoldier.h"

class TextureManager;
class Fio : public PlayerSoldier
{
public:
    Fio(TextureManager& tm);

    void specialPowerUp() override;
    void pickupWeapon(Weapon* w) override;
    float superchargedFireRate() const override { return powerUpActive ? 2.0f : 1.0f; }
};
