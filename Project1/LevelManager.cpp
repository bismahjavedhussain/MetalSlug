#include "LevelManager.h"
#include "Level.h"
#include "SurvivalLevel.h"
#include "BossLevel.h"
#include "EntityManager.h"

LevelManager::LevelManager(EntityManager* em, TextureManager* tm)
    : currentLevel(nullptr), currentLevelIdx(0),
      entityMgr(em), textures(tm) {}

LevelManager::~LevelManager()
{
    unloadCurrent();
}
void LevelManager::loadLevel(int idx, GameMode* )
{
    if (idx >= 4)
    {
        loadBossLevel();
        return;
    }

    unloadCurrent();
    if (entityMgr != nullptr) entityMgr->clearTransientEntities();
    currentLevelIdx = idx;

    SurvivalLevel* sl = new SurvivalLevel(idx, entityMgr, textures);
    sl->setIndex(idx);
    sl->generateTerrain();
    sl->spawnPlayerVehicles();
    sl->spawnEnemies();
    currentLevel = sl;
}

void LevelManager::unloadCurrent()
{
    if (currentLevel != nullptr)
    {
        delete currentLevel;
        currentLevel = nullptr;
    }
}
void LevelManager::advance()
{
    if (currentLevelIdx < 3)
        loadLevel(currentLevelIdx + 1, nullptr);
    else
        loadBossLevel();
}

void LevelManager::loadBossLevel()
{
    unloadCurrent();

    if (entityMgr != nullptr) entityMgr->clearTransientEntities();
    currentLevelIdx = 4;
    BossLevel* bl = new BossLevel(entityMgr, textures);
    bl->generateTerrain();
    bl->spawnPlayerVehicles();
    bl->spawnEnemies();
    currentLevel = bl;
}
