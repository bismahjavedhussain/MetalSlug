#pragma once
#include "Tile.h"

class IndestructibleTile : public Tile
{
public:
    bool isSolid()        override { return true; }
    bool isDestructible() override { return false; }
    bool isWater()        override { return false; }
};
