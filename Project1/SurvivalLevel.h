#pragma once
#include "Level.h"
#include "CowardiceReserve.h"

class EnemyManager;
class EntityManager;
class TextureManager;
class Entity;
class Camera;
class Enemy;
class SpawnRecipe;
struct EnemySpawn;


class SurvivalLevel : public Level
{
    static const int MAX_SPAWNS = 64;

    EnemySpawn* fixedSpawnMarks;
    int         spawnMarkCount;
    int         nextSpawnIndex;
    int         numOfSpawnBatches;
    bool        complete;
    bool        clearBonusAwarded;
    float       relocationCooldown;
    CowardiceReserve cowardiceReserve;
    int              respawnSideToggle;
    static const int MAX_RECIPES = 80;
    SpawnRecipe*  recipes[MAX_RECIPES];
    int           recipeCount;

    EntityManager*  entityMgr;
    TextureManager* textures;

    void buildJaggedAerial(int colStart, int colEnd);
    void placePlatform   (int colStart, int colEnd, int row);
    void placeSeabedBump (int colStart, int colEnd, int topRow);

    float biomeX        (int biomeIdx, float fraction) const;
    int   biomeFloorY   (int biomeIdx) const;
    int   biomeGroundTopY(int biomeIdx) const;
    int   aerialFloorY  () const;
    int   plainsFloorY  () const;
    int   aquaticY      () const;
    void  slotPlace     (int slot, int& biomeIdx, float& fraction) const;


    void  relocateAliveEnemiesFarFromPlayer(PlayerSoldier* p, EntityManager& em);
    void  populateLevel1();
    void  populateLevel2();
    void  populateLevel3();

    void  addRecipe(float triggerX, int biomeIdx, int count,
                    Entity* proto, bool aerial = false);

    void  tickSkipDetection      (PlayerSoldier* p, EntityManager& em, Camera* cam);
    void  tickRespawnFromReserve (PlayerSoldier* p, EntityManager& em, Camera* cam, float dt);

    void  computeRespawnPosition (Enemy* e, PlayerSoldier* p, Camera* cam);

public:
    SurvivalLevel(int idx, EntityManager* em, TextureManager* tm);
    ~SurvivalLevel() override;

    void update(float dt)                  override;
    void render(sf::RenderWindow& rw)      override;
    void generateTerrain()                 override;
    void spawnEnemies()                    override;
    void spawnPlayerVehicles()             override;
    bool isComplete()                      override;
    bool consumeClearBonus()               override;
    void onPlayerAtRightBoundary(PlayerSoldier* p, EntityManager& em) override;



    SurvivalLevel* asSurvivalLevel() override { return this; }

    void tickCowardiceStream(PlayerSoldier* p, EntityManager& em,
                             Camera* cam, float dt);


    void  placeOnGround (Entity* e, int biomeIdx) const;
    void tickSpawnTriggers(Camera* cam);
};
