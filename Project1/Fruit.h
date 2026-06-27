#pragma once
#include "Collectible.h"
#include "TextureManager.h"


class Fruit : public Collectible
{
    int saturationRestore;
public:
    Fruit(TextureManager& tm, float spawnX, float spawnY);
    void onPickup(PlayerSoldier* p, PlayState& ps) override;
};
