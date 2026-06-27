#pragma once
#include "Tile.h"

class AirTile : public Tile
{
public:
    bool isSolid()        override { return false; }
    bool isDestructible() override { return false; }
    bool isWater()        override { return false; }
};
