#pragma once
#include "Tile.h"

class SolidTile : public Tile
{
public:
    bool isSolid()        override { return true; }
    bool isDestructible() override { return true; }
    bool isWater()        override { return false; }
    void onExplosion(float blastRadius) override;
};
