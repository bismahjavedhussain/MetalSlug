#pragma once

class Level;
class GameMode;
class EntityManager;
class TextureManager;


class LevelManager
{
    Level*          currentLevel;
    int             currentLevelIdx;
    EntityManager*  entityMgr;
    TextureManager* textures;

public:
    LevelManager(EntityManager* em, TextureManager* tm);
    ~LevelManager();

    void  loadLevel(int idx, GameMode* mode);
    void  unloadCurrent();
    void  advance();
    void  loadBossLevel();

    Level* getCurrent()      { return currentLevel; }
    int    getCurrentIdx() const { return currentLevelIdx; }
};
