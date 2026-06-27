#pragma once
#include "Collectible.h"
#include "TextureManager.h"


class Turkey : public Collectible
{
    int saturationRestore;
public:
    Turkey(TextureManager& tm, float spawnX, float spawnY);
    void onPickup(PlayerSoldier* p, PlayState& ps) override;
};
