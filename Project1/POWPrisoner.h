#pragma once
#include "Collectible.h"
#include "TextureManager.h"


class POWPrisoner : public Collectible
{
    unsigned        crateSeed;
    TextureManager* texMgr;

public:
    POWPrisoner(TextureManager& tm, float spawnX, float spawnY, unsigned seed);
    void onPickup(PlayerSoldier* p, PlayState& ps) override;




    bool requiresKeyPress() const override { return true; }



    Entity* clone() override;
};
