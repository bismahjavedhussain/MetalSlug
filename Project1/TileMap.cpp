#include "TileMap.h"
#include "Tile.h"
#include "Biome.h"
#include "AirTile.h"
#include "SolidTile.h"
#include "WaterTile.h"
#include "IndestructibleTile.h"
#include "coordSyst.h"
#include <cmath>


TileMap::TileMap(int w, int h, int tileSizePx): grid(nullptr), width(w), height(h),tileSize(tileSizePx),
  seaLevel(0), craterCount(0), biomeCount(0)
{
    grid = new Tile**[width];
    for (int x = 0; x < width; ++x)
    {
        grid[x] = new Tile*[height];
        for (int y = 0; y < height; ++y)
        {
            AirTile* a = new AirTile();
            a->setGrid(x, y);
            grid[x][y] = a;
        }
    }
    for (int i = 0; i < BIOME_CAP; ++i) 
    biomes[i] = nullptr;
}

TileMap::~TileMap()
{       if (grid != nullptr){
        for (int x = 0; x < width; ++x){
            for (int y = 0; y < height; ++y){  
                if (grid[x][y] != nullptr) 
                  delete grid[x][y];
            }
            delete[] grid[x];
        }
        delete[] grid;
        grid = nullptr;
    }
    for (int i = 0; i < biomeCount; ++i)
    {
        if (biomes[i] != nullptr)
        delete biomes[i];
        biomes[i] = nullptr;
    }}

Tile* TileMap::getTile(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    return nullptr;
    return grid[x][y];
}

void TileMap::setTile(int x, int y, Tile* t)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        if (t != nullptr)   
        delete t;
        return;
    }
    if (grid[x][y] != nullptr)         
    delete grid[x][y];
    if (t != nullptr) 
    t->setGrid(x, y);
    grid[x][y] = t;
}




void TileMap::fillCraterWithWater(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    return;
    Tile* t = grid[x][y];
    if (t != nullptr) 
    delete t;
    WaterTile* w = new WaterTile();
    w->setGrid(x, y);
    grid[x][y] = w;
}


void TileMap::tickCraterFill(float dt)
{     for (int i = 0; i < craterCount; ++i)
    {      if (craters[i].width <= 3 && craters[i].depth >= 1)
        {
            craters[i].exposureTime += dt;
            const float FILL_TIME = 5.0f;
            if (craters[i].exposureTime >= FILL_TIME)
            {
                fillCraterWithWater(craters[i].x, craters[i].y);

                craters[i] = craters[craterCount - 1];
                craterCount--;
                i--;
            }
        }
    }
}

void TileMap::addBiome(Biome* b)
{
    if (biomeCount < BIOME_CAP)
        biomes[biomeCount++] = b;
    else
        delete b;
}

Biome* TileMap::getBiomeAt(int , int gridY)
{
    for (int i = 0; i < biomeCount; ++i)
        if (biomes[i] != nullptr && biomes[i]->containsRow(gridY))
            return biomes[i];
    return nullptr;
}

int TileMap::topSolidRow(int x)
{
    if (x < 0 || x >= width) return height;
    for (int y = 0; y < height; ++y)
        if (grid[x][y] != nullptr && grid[x][y]->isSolid()) return y;
    return height;
}


void TileMap::render(sf::RenderWindow& rw, float camX, float camY,
                     float viewW, float viewH,
                     sf::Sprite& grassTop, sf::Sprite& dirt, sf::Sprite& stone,
                     sf::Sprite& bedrock,  sf::Sprite& water)
{
    int x0 = (int)(camX / tileSize);              if (x0 < 0)      x0 = 0;
    int y0 = (int)(camY / tileSize);              if (y0 < 0)      y0 = 0;
    int x1 = (int)((camX + viewW) / tileSize)+1;  if (x1 > width)  x1 = width;
    int y1 = (int)((camY + viewH) / tileSize)+1;  if (y1 > height) y1 = height;

    const int peakBand   = height / 3;
    const int DIRT_DEPTH = 4;

    for (int x = x0; x < x1; ++x)
    {
        for (int y = y0; y < y1; ++y)
        {
            Tile* t = grid[x][y];
            if (t == nullptr) continue;

            float drawX = (float)(x * tileSize) - camX;
            float drawY = (float)(y * tileSize) - camY;

            if (!t->isDestructible() && t->isSolid())
            {
                bedrock.setPosition(drawX, drawY);
                rw.draw(bedrock);
                continue;
            }
            if (t->isWater())
            {
                water.setPosition(drawX, drawY);
                rw.draw(water);
                continue;
            }
            if (!t->isSolid()) continue;

            Tile* above      = (y > 0) ? grid[x][y - 1] : nullptr;
            bool  aboveAir   = (above == nullptr) || (!above->isSolid() && !above->isWater());
            bool  aboveWater = (above != nullptr) && above->isWater();


            if (y < peakBand)
            {
                stone.setPosition(drawX, drawY);
                rw.draw(stone);
            }
            else if (aboveAir)
            {
                grassTop.setPosition(drawX, drawY);
                rw.draw(grassTop);
            }
            else if (aboveWater)
            {
                stone.setPosition(drawX, drawY);
                rw.draw(stone);
            }
            else
            {

                int  depth      = 0;
                bool waterAbove = false;
                for (int yy = y - 1; yy >= 0; --yy)
                {
                    Tile* tt = grid[x][yy];
                    if (tt == nullptr) break;
                    if (tt->isWater()) { waterAbove = true; break; }
                    if (!tt->isSolid()) break;
                    ++depth;
                    if (depth >= DIRT_DEPTH) break;
                }

                if (waterAbove)              { stone.setPosition(drawX, drawY); rw.draw(stone); }
                else if (depth < DIRT_DEPTH) { dirt .setPosition(drawX, drawY); rw.draw(dirt);  }
                else                         { stone.setPosition(drawX, drawY); rw.draw(stone); }
            }
        }
    }
}


