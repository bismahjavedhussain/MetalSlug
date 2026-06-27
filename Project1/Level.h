#pragma once
#include <SFML/Graphics.hpp>

class TileMap;
class EntityManager;
class PlayerSoldier;
class SurvivalLevel;
class BossLevel;
class Level
{
protected:
    TileMap* tileMap;  
    int      levelIndex;

public:
    Level();
    virtual ~Level();

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& rw)   = 0;
    virtual void generateTerrain() = 0;
    virtual void spawnEnemies() = 0;
    virtual void spawnPlayerVehicles() = 0;
    virtual bool isComplete()   = 0;
    virtual bool consumeClearBonus() { return false; }






    virtual void onPlayerAtRightBoundary(PlayerSoldier* ,
                                         EntityManager& ) {}

    TileMap* getTileMap()  { return tileMap; }
    int      getIndex() const { return levelIndex; }
    void     setIndex(int i)  { levelIndex = i; }
    virtual SurvivalLevel* asSurvivalLevel() { return nullptr; }
    virtual BossLevel* asBossLevel() { return nullptr; }
};
