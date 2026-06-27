#pragma once
#include "PlayerSoldier.h"

class TextureManager;
class Marco : public PlayerSoldier
{
public:
    Marco(TextureManager& tm);

    void specialPowerUp() override;
    bool dualFireWhilePoweredUp() const override { return true; }




    bool meleePiercesShield() const override { return true; }
};
