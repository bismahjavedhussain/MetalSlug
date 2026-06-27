#pragma once
#include "PlayerSoldier.h"

class TextureManager;
class Eri : public PlayerSoldier
{
public:
    Eri(TextureManager& tm);

    void specialPowerUp() override;
    void throwGrenade()   override;
    void meleeAttack()    override;
};
