#include "Level.h"
#include "TileMap.h"

Level::Level() : tileMap(nullptr), levelIndex(0) {}

Level::~Level()
{
    if (tileMap != nullptr)
    {
        delete tileMap;
        tileMap = nullptr;
    }
}
