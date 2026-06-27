#pragma once
#include <SFML/Graphics.hpp>
#include "coordSyst.h"

class Tile;
class Biome;

 struct Crater          
{
    int   x;
    int   y;
    int   width;
    int   depth;
    float exposureTime;

    Crater() : x(0), y(0), width(0), depth(0), exposureTime(0.0f) {}
};


class TileMap
{

    
    static const int CRATER_CAP = 64;
    static const int BIOME_CAP  = 4;

    Tile*** grid;           

    int width;
    int height;
    int tileSize;
    int seaLevel;

    Crater craters[CRATER_CAP];
    int craterCount;

    Biome* biomes[BIOME_CAP];
    int biomeCount;

 public:
    TileMap(int w, int h, int tileSizePx);
    ~TileMap();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getTileSize() const { return tileSize; }
    int getSeaLevel() const { return seaLevel; }
    void setSeaLevel(int y) { 
    seaLevel = y; 
    }
    Tile* getTile(int x, int y);
    void  setTile(int x, int y, Tile* t);

    //void  destroyTilesInRadius(coordSyst center, float r);
    void  fillCraterWithWater(int x, int y);
    void  tickCraterFill(float dt);

    void  addBiome(Biome* b);
    Biome* getBiomeAt(int , int gridY); 

    
    int  topSolidRow(int x); 



    void render(sf::RenderWindow& rw, float camX, float camY, float viewW, float viewH,
                sf::Sprite& grassTop, sf::Sprite& dirt, sf::Sprite& stone,
                sf::Sprite& bedrock, sf::Sprite& water);
};
