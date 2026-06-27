#pragma once
#include "Tile.h"



class WaterTile : public Tile
{
public:
    bool isSolid()        override { return false; }
    bool isDestructible() override { return false; }
    bool isWater()        override { return true; }
    void onEntityEnter(Entity* e) override;   
};
