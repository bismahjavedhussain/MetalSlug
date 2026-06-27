#include "SurvivalLevel.h"
#include "TileMap.h"
#include "Tile.h"
#include "AirTile.h"
#include "SolidTile.h"
#include "WaterTile.h"
#include "IndestructibleTile.h"
#include "AerialBiome.h"
#include "PlainsBiome.h"
#include "AquaticBiome.h"
#include "EnemySpawn.h"
#include "EntityManager.h"
#include "RebelSoldier.h"
#include "ShieldedSoldier.h"
#include "BazookaSoldier.h"
#include "Grenadier.h"
#include "Paratrooper.h"
#include "ParatrooperKind.h"
#include "MummyWarrior.h"
#include "Zombie.h"
#include "Martian.h"
#include "POWPrisoner.h"
#include "FlyingTara.h"
#include "M15ABradley.h"
#include "EnemySub.h"
#include "MetalSlug.h"
#include "SlugFlyer.h"
#include "SlugMariner.h"
#include "AmphibiousSlug.h"
#include "Entity.h"
#include "Enemy.h"
#include "PlayerSoldier.h"
#include "Camera.h"
#include "SpawnRecipe.h"
#include "TextureManager.h"
#include <iostream>


static const int LEVEL_W      = 250;
static const int LEVEL_H      = 30;
static const int TILE_SIZE_PX = 64;
static const int SEA_LEVEL    = 13;


static const int PLAINS_END   = 80;
static const int AERIAL_END   = 170;




static const int RIGHT_BOUNDARY_BLOCKS = 245;


static const int PLAINS_GROUND_ROW = 13;
static const int AERIAL_FLOOR_ROW_DEFAULT = 9;


static const int SEABED_ROW        = 28;
static const int BEDROCK_ROW       = 29;



static const int AERIAL_FLOOR_ROW = AERIAL_FLOOR_ROW_DEFAULT - 1;

static const int PLAINS_FLOOR_ROW = 12;
static const int AQUATIC_ROW      = 27;

static const bool DEV_SKIP_LEVEL_CLEAR = true;

SurvivalLevel::SurvivalLevel(int idx, EntityManager* em, TextureManager* tx)
    : Level(),
      fixedSpawnMarks(nullptr), spawnMarkCount(0),
      nextSpawnIndex(0), numOfSpawnBatches(0),
      complete(false), clearBonusAwarded(false),
      relocationCooldown(0.0f),
      cowardiceReserve(),
      respawnSideToggle(+1),
      recipeCount(0),
      entityMgr(em), textures(tx)
{
    levelIndex = idx;
    fixedSpawnMarks = new EnemySpawn[MAX_SPAWNS];
    for (int i = 0; i < MAX_RECIPES; ++i) recipes[i] = nullptr;
}

SurvivalLevel::~SurvivalLevel()
{


    if (fixedSpawnMarks != nullptr)
    {
        for (int i = 0; i < spawnMarkCount; ++i)
        {
            if (fixedSpawnMarks[i].masterCopy != nullptr)
            {
                delete fixedSpawnMarks[i].masterCopy;
                fixedSpawnMarks[i].masterCopy = nullptr;
            }
        }
        delete[] fixedSpawnMarks;
        fixedSpawnMarks = nullptr;
    }



    for (int i = 0; i < MAX_RECIPES; ++i)
    {
        if (recipes[i] != nullptr) { delete recipes[i]; recipes[i] = nullptr; }
    }
    recipeCount = 0;
}


void SurvivalLevel::placePlatform(int colStart, int colEnd, int row)
{
    if (tileMap == nullptr) return;
    for (int x = colStart; x <= colEnd; ++x)
        tileMap->setTile(x, row, new SolidTile());
}


void SurvivalLevel::buildJaggedAerial(int colStart, int colEnd)
{
    if (tileMap == nullptr) return;

    const int kStepWidths [10] = { 3, 4, 3, 4, 3, 4, 3, 4, 3, 4 };
    const int kStepHeights[10] = { 12, 11, 10, 11, 12, 10, 11, 12, 10, 11 };

    int patternIdx    = 0;
    int colsRemaining = kStepWidths [0];
    int currentTop    = kStepHeights[0];

    for (int x = colStart; x <= colEnd; ++x)
    {
        if (colsRemaining <= 0)
        {
            patternIdx    = (patternIdx + 1) % 10;
            colsRemaining = kStepWidths [patternIdx];
            currentTop    = kStepHeights[patternIdx];
        }


        for (int y = currentTop; y < BEDROCK_ROW; ++y)
            tileMap->setTile(x, y, new SolidTile());
        colsRemaining--;
    }
}

void SurvivalLevel::placeSeabedBump(int colStart, int colEnd, int topRow)
{
    if (tileMap == nullptr) return;
    for (int x = colStart; x <= colEnd; ++x)
        for (int y = topRow; y <= SEABED_ROW; ++y)
            tileMap->setTile(x, y, new SolidTile());
}

void SurvivalLevel::generateTerrain()
{
    if (tileMap != nullptr) delete tileMap;
    tileMap = new TileMap(LEVEL_W, LEVEL_H, TILE_SIZE_PX);
    tileMap->setSeaLevel(SEA_LEVEL);




    tileMap->addBiome(new AerialBiome (0,             9));
    tileMap->addBiome(new PlainsBiome (10,            12));
    tileMap->addBiome(new AquaticBiome(SEA_LEVEL,     LEVEL_H - 1, SEA_LEVEL));


    for (int x = 0; x < LEVEL_W; ++x)
        tileMap->setTile(x, BEDROCK_ROW, new IndestructibleTile());



    for (int x = 0; x < PLAINS_END; ++x)
        for (int y = PLAINS_GROUND_ROW; y < BEDROCK_ROW; ++y)
            tileMap->setTile(x, y, new SolidTile());


    buildJaggedAerial(PLAINS_END, AERIAL_END - 1);


    for (int x = AERIAL_END; x < LEVEL_W; ++x)
    {
        for (int y = SEA_LEVEL; y < SEABED_ROW; ++y)
            tileMap->setTile(x, y, new WaterTile());
        tileMap->setTile(x, SEABED_ROW, new SolidTile());
    }


    placePlatform(15, 17, 11);
    placePlatform(25, 28, 10);
    placePlatform(35, 37, 11);
    placePlatform(45, 48, 10);

    placePlatform( 92,  96, 1);
    placePlatform(108, 112, 0);
    placePlatform(124, 128, 1);
    placePlatform(140, 144, 0);
    placePlatform(156, 160, 1);
    placeSeabedBump(180, 182, 26);
    placeSeabedBump(193, 197, 24);
    placeSeabedBump(208, 211, 25);
    placeSeabedBump(220, 222, 26);
}

int SurvivalLevel::aerialFloorY() const { return AERIAL_FLOOR_ROW * TILE_SIZE_PX; }
int SurvivalLevel::plainsFloorY() const { return PLAINS_FLOOR_ROW * TILE_SIZE_PX; }
int SurvivalLevel::aquaticY    () const { return AQUATIC_ROW      * TILE_SIZE_PX; }


float SurvivalLevel::biomeX(int biomeIdx, float fraction) const
{
    int startCol = 0;
    int endCol   = LEVEL_W;
    if (biomeIdx == 0)      { startCol = 0;          endCol = PLAINS_END; }
    else if (biomeIdx == 1) { startCol = PLAINS_END; endCol = AERIAL_END; }
    else                    { startCol = AERIAL_END; endCol = LEVEL_W;    }
    int widthPx = (endCol - startCol) * TILE_SIZE_PX;
    return (float)(startCol * TILE_SIZE_PX) + fraction * (float)widthPx;
}


int SurvivalLevel::biomeFloorY(int biomeIdx) const
{
    if (biomeIdx == 0) return plainsFloorY();
    if (biomeIdx == 1) return aerialFloorY();
    return aquaticY();
}


int SurvivalLevel::biomeGroundTopY(int biomeIdx) const
{
    if (biomeIdx == 0) return PLAINS_GROUND_ROW       * TILE_SIZE_PX;
    if (biomeIdx == 1) return AERIAL_FLOOR_ROW_DEFAULT * TILE_SIZE_PX;
    return SEABED_ROW * TILE_SIZE_PX;
}

void SurvivalLevel::placeOnGround(Entity* e, int biomeIdx) const
{
    if (e == nullptr) return;
    coordSyst p = e->getPosition();

    float groundTop;
    if (biomeIdx == 0)
    {
        groundTop = (float)(PLAINS_GROUND_ROW * TILE_SIZE_PX);
    }
    else if (tileMap != nullptr)
    {
        int col = (int)((p.x + e->getWidth() * 0.5f) / TILE_SIZE_PX);
        if (col < 0)               col = 0;
        if (col >= LEVEL_W)        col = LEVEL_W - 1;

        int topRow = BEDROCK_ROW;
        for (int r = 3; r < BEDROCK_ROW; ++r)
        {
            Tile* t = tileMap->getTile(col, r);
            if (t != nullptr && t->isSolid()) { topRow = r; break; }
        }
        groundTop = (float)(topRow * TILE_SIZE_PX);
    }
    else
    {
        groundTop = (float)biomeGroundTopY(biomeIdx);
    }

    e->setPosition(p.x, groundTop - e->getHeight() - 2.0f);
}

void SurvivalLevel::slotPlace(int slot, int& biomeIdx, float& fraction) const
{
    biomeIdx = slot % 3;
    int withinBiome = slot / 3;
    fraction = 0.10f + 0.10f * (float)withinBiome;
    if (fraction > 0.90f) fraction = 0.90f;
}


void SurvivalLevel::spawnEnemies()
{
    if (entityMgr == nullptr || textures == nullptr) return;
    if      (levelIndex == 1) populateLevel1();
    else if (levelIndex == 2) populateLevel2();
    else if (levelIndex == 3) populateLevel3();

}

void SurvivalLevel::addRecipe(float triggerX, int biomeIdx, int count,
                              Entity* proto, bool aerial)
{
    if (recipeCount < MAX_RECIPES)
        recipes[recipeCount++] = new SpawnRecipe(triggerX, biomeIdx,
                                                 count, proto, aerial);
    else if (proto != nullptr)
        delete proto;
}



















void SurvivalLevel::spawnPlayerVehicles()
{
    if (entityMgr == nullptr || textures == nullptr) return;


    {
        MetalSlug* v = new MetalSlug(*textures, biomeX(0, 0.50f),
                                     (float)(plainsFloorY() - TILE_SIZE_PX));
        placeOnGround(v, 0);
        entityMgr->addEntity(v);
    }





    {
        SlugFlyer* v = new SlugFlyer(*textures, biomeX(1, 0.50f),
                                     (float)(aerialFloorY() - TILE_SIZE_PX));
        placeOnGround(v, 1);
        entityMgr->addEntity(v);
    }


    {
        SlugMariner* v = new SlugMariner(*textures, biomeX(2, 0.50f),
                                         (float)aquaticY());
        placeOnGround(v, 2);
        entityMgr->addEntity(v);
    }







    {
        AmphibiousSlug* v = new AmphibiousSlug(*textures, biomeX(2, 0.05f),
                                               (float)aquaticY());
        placeOnGround(v, 2);
        entityMgr->addEntity(v);
    }
}

void SurvivalLevel::update(float dt)
{
    if (tileMap != nullptr) tileMap->tickCraterFill(dt);




    if (relocationCooldown > 0.0f)
    {
        relocationCooldown -= dt;
        if (relocationCooldown < 0.0f) relocationCooldown = 0.0f;
    }
}

void SurvivalLevel::render(sf::RenderWindow& )
{


}










bool SurvivalLevel::isComplete()
{
    if (complete)        return true;
    if (entityMgr == nullptr) return false;

    bool       allEnemiesDead = true;
    bool       reachedRight   = false;
    const float boundaryPx    = (float)(RIGHT_BOUNDARY_BLOCKS * TILE_SIZE_PX);

    Entity** roster = entityMgr->getEntities();
    int n = entityMgr->getCount();
    for (int i = 0; i < n; ++i)
    {
        Entity* e = roster[i];
        if (e == nullptr) continue;


        Enemy* en = e->asEnemy();
        if (en != nullptr && en->getIsAlive())
        {
            allEnemiesDead = false;
        }


        if (e->isPlayer() && e->getIsAlive())
        {
            coordSyst pp = e->getPosition();
            if (pp.x >= boundaryPx) reachedRight = true;
        }
    }




    bool clearGate = DEV_SKIP_LEVEL_CLEAR
                     ? reachedRight
                     : (allEnemiesDead && reachedRight);
    if (clearGate)
    {
        complete          = true;
        clearBonusAwarded = false;
        return true;
    }
    return false;
}




bool SurvivalLevel::consumeClearBonus()
{
    if (complete && !clearBonusAwarded)
    {
        clearBonusAwarded = true;
        return true;
    }
    return false;
}








void SurvivalLevel::onPlayerAtRightBoundary(PlayerSoldier* p, EntityManager& em)
{
    if (p == nullptr) return;
    if (relocationCooldown > 0.0f) return;




    const float FAR_THRESHOLD = 900.0f;
    coordSyst pp = p->getPosition();

    Entity** roster = em.getEntities();
    int n = em.getCount();
    bool anyFar = false;
    for (int i = 0; i < n; ++i)
    {
        Entity* e = roster[i];
        if (e == nullptr) continue;
        Enemy* en = e->asEnemy();
        if (en == nullptr || !en->getIsAlive()) continue;
        coordSyst ep = en->getPosition();
        float dx = ep.x - pp.x;
        if (dx < 0.0f) dx = -dx;
        if (dx > FAR_THRESHOLD) { anyFar = true; break; }
    }
    if (!anyFar) return;

    relocateAliveEnemiesFarFromPlayer(p, em);
    relocationCooldown = 5.0f;
}






void SurvivalLevel::relocateAliveEnemiesFarFromPlayer(PlayerSoldier* p,
                                                      EntityManager& em)
{
    if (p == nullptr || tileMap == nullptr) return;

    const float FAR_THRESHOLD = 900.0f;
    coordSyst   pp = p->getPosition();



    const float OFFSETS[8] = {
        +260.0f, -260.0f, +340.0f, -340.0f,
        +420.0f, -420.0f, +500.0f, -500.0f
    };
    const int OFFSET_COUNT = 8;


    const float MIN_X = (float)(2 * TILE_SIZE_PX);
    const float MAX_X = (float)((LEVEL_W - 3) * TILE_SIZE_PX);

    Entity** roster = em.getEntities();
    int n = em.getCount();
    int placed = 0;

    for (int i = 0; i < n; ++i)
    {
        Entity* e = roster[i];
        if (e == nullptr) continue;
        Enemy* en = e->asEnemy();
        if (en == nullptr || !en->getIsAlive()) continue;

        coordSyst ep = en->getPosition();
        float dx = ep.x - pp.x;
        if (dx < 0.0f) dx = -dx;
        if (dx <= FAR_THRESHOLD) continue;

        float newX = pp.x + OFFSETS[placed % OFFSET_COUNT];
        if (newX < MIN_X) newX = MIN_X;
        if (newX > MAX_X) newX = MAX_X;



        int col = (int)(newX / TILE_SIZE_PX);
        int biomeIdx = 0;
        if (col >= AERIAL_END)      biomeIdx = 2;
        else if (col >= PLAINS_END) biomeIdx = 1;

        en->setPosition(newX, pp.y);
        placeOnGround(en, biomeIdx);
        ++placed;
    }
}






void SurvivalLevel::tickCowardiceStream(PlayerSoldier* p, EntityManager& em,
                                        Camera* cam, float dt)
{
    if (p == nullptr || cam == nullptr) return;

    tickSkipDetection(p, em, cam);
    tickRespawnFromReserve(p, em, cam, dt);
}






void SurvivalLevel::tickSkipDetection(PlayerSoldier* , EntityManager& em,
                                      Camera* cam)
{
    if (cam == nullptr) return;
    coordSyst camOff = cam->getOffset();
    float     camLeft = camOff.x;
    float     skipThreshold = camLeft - CowardiceReserve::SKIP_MARGIN;

    Entity** roster = em.getEntities();
    int n = em.getCount();
    for (int i = 0; i < n; ++i)
    {
        Entity* e = roster[i];
        if (e == nullptr) continue;
        Enemy* en = e->asEnemy();
        if (en == nullptr || !en->getIsAlive()) continue;
        if (en->getInReserve()) continue;





        float rightEdge = en->getPosition().x + en->getWidth();
        if (rightEdge < skipThreshold)
        {
            en->setInReserve(true);
            cowardiceReserve.enqueue(en);
        }
    }
}





void SurvivalLevel::tickRespawnFromReserve(PlayerSoldier* p, EntityManager& em,
                                           Camera* cam, float dt)
{
    if (!cowardiceReserve.tickSpawnReady(dt)) return;

    Enemy* en = cowardiceReserve.dequeue();
    if (en == nullptr) return;

    computeRespawnPosition(en, p, cam);






    en->setIsGrudgeful(true);


    en->setInReserve(false);



    (void)em;
}





void SurvivalLevel::computeRespawnPosition(Enemy* e, PlayerSoldier* p,
                                           Camera* cam)
{
    if (e == nullptr || cam == nullptr) return;

    coordSyst camOff = cam->getOffset();
    float camLeft  = camOff.x;
    float camRight = camLeft + cam->getViewWidth();

    float spawnX;
    if (respawnSideToggle > 0)
    {



        spawnX = camRight + CowardiceReserve::RESPAWN_MARGIN;
    }
    else
    {


        spawnX = camLeft - CowardiceReserve::RESPAWN_MARGIN - e->getWidth();
    }
    respawnSideToggle = -respawnSideToggle;


    const float MIN_X = (float)(2 * TILE_SIZE_PX);
    const float MAX_X = (float)((LEVEL_W - 3) * TILE_SIZE_PX);
    if (spawnX < MIN_X) spawnX = MIN_X;
    if (spawnX > MAX_X) spawnX = MAX_X;




    float seedY = (p != nullptr) ? p->getPosition().y : (float)plainsFloorY();
    e->setPosition(spawnX, seedY);




    if (e->isAerial()) return;



    int col = (int)(spawnX / TILE_SIZE_PX);
    int biomeIdx = 0;
    if (col >= AERIAL_END)      biomeIdx = 2;
    else if (col >= PLAINS_END) biomeIdx = 1;

    placeOnGround(e, biomeIdx);
}


























static const int L2_REBEL_COUNT     = 3;
static const int L2_BAZOOKA_COUNT   = 2;
static const int L2_SHIELDED_COUNT  = 2;
static const int L2_GRENADIER_COUNT = 2;
static const int L2_ZOMBIE_COUNT    = 4;










static const int L1_REBEL_COUNT     = 3;
static const int L1_BAZOOKA_COUNT   = 1;
static const int L1_SHIELDED_COUNT  = 2;
static const int L1_GRENADIER_COUNT = 1;
static const int L1_ZOMBIE_COUNT    = 3;

void SurvivalLevel::populateLevel1()
{
    if (textures == nullptr) return;
    TextureManager& tm = *textures;


    const float L1_INF_FRACS[4] = { 0.20f, 0.40f, 0.60f, 0.80f };
    for (int b = 0; b < 2; ++b)
    {
        addRecipe(biomeX(b, L1_INF_FRACS[0]), b, L1_REBEL_COUNT,
                  new RebelSoldier   (tm, 0.0f, (float)biomeFloorY(b), 0));
        addRecipe(biomeX(b, L1_INF_FRACS[1]), b, L1_BAZOOKA_COUNT,
                  new BazookaSoldier (tm, 0.0f, (float)biomeFloorY(b), 0));
        addRecipe(biomeX(b, L1_INF_FRACS[2]), b, L1_SHIELDED_COUNT,
                  new ShieldedSoldier(tm, 0.0f, (float)biomeFloorY(b), 0));
        addRecipe(biomeX(b, L1_INF_FRACS[3]), b, L1_GRENADIER_COUNT,
                  new Grenadier      (tm, 0.0f, (float)biomeFloorY(b), 0));
    }


    addRecipe(biomeX(1, 0.40f), 1, L1_REBEL_COUNT,
              new Paratrooper(tm, 0.0f, 0.0f, new RebelParatrooperKind(), 0),
               true);
    addRecipe(biomeX(1, 0.60f), 1,  1,
              new Martian(tm, 0.0f, (float)(4 * TILE_SIZE_PX)), true);


    const float L1_MUMMY_FRACS [2] = { 0.30f, 0.70f };
    const float L1_ZOMB_PLN[2]     = { 0.35f, 0.75f };
    for (int i = 0; i < 2; ++i)
        addRecipe(biomeX(0, L1_MUMMY_FRACS[i]), 0,  1,
                  new MummyWarrior(tm, 0.0f, (float)plainsFloorY()));
    for (int i = 0; i < 2; ++i)
        addRecipe(biomeX(0, L1_ZOMB_PLN[i]), 0, L1_ZOMBIE_COUNT,
                  new Zombie(tm, 0.0f, (float)plainsFloorY()));


    const float L1_ZOMB_AQU[2] = { 0.30f, 0.70f };
    for (int i = 0; i < 2; ++i)
        addRecipe(biomeX(2, L1_ZOMB_AQU[i]), 2, L1_ZOMBIE_COUNT,
                  new Zombie(tm, 0.0f, (float)aquaticY()));


    addRecipe(biomeX(1, 0.30f), 1,  2,
              new FlyingTara(tm, 0.0f, 4.0f * TILE_SIZE_PX), true);
    addRecipe(biomeX(1, 0.70f), 1, 2,
              new FlyingTara(tm, 0.0f, 4.0f * TILE_SIZE_PX), true);
    addRecipe(biomeX(2, 0.50f), 2, 1,
              new EnemySub(tm, 0.0f, (float)aquaticY()));


    addRecipe(biomeX(0, 0.50f), 0, 1,
              new POWPrisoner(tm, 0.0f, (float)plainsFloorY(),
                              (unsigned)(levelIndex * 31 + 11)));
    addRecipe(biomeX(1, 0.50f), 1, 1,
              new POWPrisoner(tm, 0.0f, (float)aerialFloorY(),
                              (unsigned)(levelIndex * 31 + 41)));
    addRecipe(biomeX(2, 0.50f), 2, 1,
              new POWPrisoner(tm, 0.0f, (float)aquaticY(),
                              (unsigned)(levelIndex * 31 + 67)));
}

void SurvivalLevel::populateLevel2()
{
    if (textures == nullptr) return;
    TextureManager& tm = *textures;



    const float L2_INF_FRACS[4] = { 0.20f, 0.40f, 0.60f, 0.80f };
    for (int b = 0; b < 3; ++b)
    {
        addRecipe(biomeX(b, L2_INF_FRACS[0]), b, L2_REBEL_COUNT,
                  new RebelSoldier   (tm, 0.0f, (float)biomeFloorY(b), 0));
        addRecipe(biomeX(b, L2_INF_FRACS[1]), b, L2_BAZOOKA_COUNT,
                  new BazookaSoldier (tm, 0.0f, (float)biomeFloorY(b), 0));
        addRecipe(biomeX(b, L2_INF_FRACS[2]), b, L2_SHIELDED_COUNT,
                  new ShieldedSoldier(tm, 0.0f, (float)biomeFloorY(b), 0));
        addRecipe(biomeX(b, L2_INF_FRACS[3]), b, L2_GRENADIER_COUNT,
                  new Grenadier      (tm, 0.0f, (float)biomeFloorY(b), 0));
    }


    for (int i = 0; i < 2; ++i)
        addRecipe(biomeX(1, 0.30f + 0.40f * (float)i), 1, L2_REBEL_COUNT,
                  new Paratrooper(tm, 0.0f, 0.0f, new RebelParatrooperKind(), 0),
                   true);
    for (int i = 0; i < 2; ++i)
        addRecipe(biomeX(1, 0.40f + 0.40f * (float)i), 1,  1,
                  new Martian(tm, 0.0f, (float)(4 * TILE_SIZE_PX)), true);


    const float L2_MUMMY_FRACS[3] = { 0.25f, 0.50f, 0.75f };
    for (int i = 0; i < 3; ++i)
        addRecipe(biomeX(0, L2_MUMMY_FRACS[i]), 0,  1,
                  new MummyWarrior(tm, 0.0f, (float)plainsFloorY()));
    const float L2_ZOMB_PLN[3] = { 0.30f, 0.55f, 0.80f };
    for (int i = 0; i < 3; ++i)
        addRecipe(biomeX(0, L2_ZOMB_PLN[i]), 0, L2_ZOMBIE_COUNT,
                  new Zombie(tm, 0.0f, (float)plainsFloorY()));


    const float L2_ZOMB_AQU[3] = { 0.20f, 0.50f, 0.80f };
    for (int i = 0; i < 3; ++i)
        addRecipe(biomeX(2, L2_ZOMB_AQU[i]), 2, L2_ZOMBIE_COUNT,
                  new Zombie(tm, 0.0f, (float)aquaticY()));


    addRecipe(biomeX(1, 0.30f), 1, 2,
              new FlyingTara(tm, 0.0f, 4.0f * TILE_SIZE_PX), true);
    addRecipe(biomeX(1, 0.70f), 1, 2,
              new FlyingTara(tm, 0.0f, 4.0f * TILE_SIZE_PX), true);
    addRecipe(biomeX(0, 0.50f), 0, 2,
              new FlyingTara(tm, 0.0f, 4.0f * TILE_SIZE_PX), true);
    addRecipe(biomeX(0, 0.35f), 0, 1,
              new M15ABradley(tm, 0.0f, (float)plainsFloorY()));
    addRecipe(biomeX(0, 0.75f), 0, 1,
              new M15ABradley(tm, 0.0f, (float)plainsFloorY()));
    addRecipe(biomeX(2, 0.50f), 2, 1,
              new EnemySub(tm, 0.0f, (float)aquaticY()));


    addRecipe(biomeX(0, 0.30f), 0, 1,
              new POWPrisoner(tm, 0.0f, (float)plainsFloorY(),
                              (unsigned)(levelIndex * 31 + 11)));
    addRecipe(biomeX(0, 0.70f), 0, 1,
              new POWPrisoner(tm, 0.0f, (float)plainsFloorY(),
                              (unsigned)(levelIndex * 31 + 23)));
    addRecipe(biomeX(1, 0.50f), 1, 1,
              new POWPrisoner(tm, 0.0f, (float)aerialFloorY(),
                              (unsigned)(levelIndex * 31 + 41)));
    addRecipe(biomeX(2, 0.50f), 2, 1,
              new POWPrisoner(tm, 0.0f, (float)aquaticY(),
                              (unsigned)(levelIndex * 31 + 67)));
}



static const int L3_REBEL_COUNTS    [3] = { 3, 4, 2 };
static const int L3_BAZOOKA_COUNTS  [3] = { 2, 1, 2 };
static const int L3_SHIELDED_COUNTS [3] = { 1, 2, 1 };
static const int L3_GRENADIER_COUNTS[3] = { 2, 1, 2 };
static const int L3_ZOMB_PLN_COUNTS [4] = { 4, 3, 5, 4 };
static const int L3_ZOMB_AQU_COUNTS [4] = { 3, 5, 4, 5 };

void SurvivalLevel::populateLevel3()
{
    if (textures == nullptr) return;
    TextureManager& tm = *textures;


    const float L3_INF_FRACS[4] = { 0.20f, 0.40f, 0.60f, 0.80f };
    for (int b = 0; b < 3; ++b)
    {
        addRecipe(biomeX(b, L3_INF_FRACS[0]), b, L3_REBEL_COUNTS    [b],
                  new RebelSoldier   (tm, 0.0f, (float)biomeFloorY(b), 0));
        addRecipe(biomeX(b, L3_INF_FRACS[1]), b, L3_BAZOOKA_COUNTS  [b],
                  new BazookaSoldier (tm, 0.0f, (float)biomeFloorY(b), 0));
        addRecipe(biomeX(b, L3_INF_FRACS[2]), b, L3_SHIELDED_COUNTS [b],
                  new ShieldedSoldier(tm, 0.0f, (float)biomeFloorY(b), 0));
        addRecipe(biomeX(b, L3_INF_FRACS[3]), b, L3_GRENADIER_COUNTS[b],
                  new Grenadier      (tm, 0.0f, (float)biomeFloorY(b), 0));
    }

    addRecipe(biomeX(1, 0.20f), 1, 3,
              new Paratrooper(tm, 0.0f, 0.0f, new RebelParatrooperKind(), 0),
               true);
    addRecipe(biomeX(1, 0.50f), 1, 2,
              new Paratrooper(tm, 0.0f, 0.0f, new BazookaParatrooperKind(), 0),
               true);
    addRecipe(biomeX(1, 0.80f), 1, 1,
              new Paratrooper(tm, 0.0f, 0.0f, new ShieldedParatrooperKind(), 0),
               true);

    const float L3_MARTIAN_FRACS[3] = { 0.25f, 0.50f, 0.75f };
    for (int i = 0; i < 3; ++i)
        addRecipe(biomeX(1, L3_MARTIAN_FRACS[i]), 1, 1,
                  new Martian(tm, 0.0f, (float)(4 * TILE_SIZE_PX)), true);


    const float L3_MUMMY_FRACS  [4] = { 0.15f, 0.40f, 0.65f, 0.90f };
    const float L3_ZOMB_PLN_FRACS[4] = { 0.20f, 0.45f, 0.70f, 0.85f };
    for (int i = 0; i < 4; ++i)
        addRecipe(biomeX(0, L3_MUMMY_FRACS[i]), 0, 1,
                  new MummyWarrior(tm, 0.0f, (float)plainsFloorY()));
    for (int i = 0; i < 4; ++i)
        addRecipe(biomeX(0, L3_ZOMB_PLN_FRACS[i]), 0, L3_ZOMB_PLN_COUNTS[i],
                  new Zombie(tm, 0.0f, (float)plainsFloorY()));


    const float L3_ZOMB_AQU_FRACS[4] = { 0.15f, 0.40f, 0.65f, 0.90f };
    for (int i = 0; i < 4; ++i)
        addRecipe(biomeX(2, L3_ZOMB_AQU_FRACS[i]), 2, L3_ZOMB_AQU_COUNTS[i],
                  new Zombie(tm, 0.0f, (float)aquaticY()));


    addRecipe(biomeX(1, 0.30f), 1, 2,
              new FlyingTara(tm, 0.0f, 4.0f * TILE_SIZE_PX), true);
    addRecipe(biomeX(1, 0.70f), 1, 2,
              new FlyingTara(tm, 0.0f, 4.0f * TILE_SIZE_PX), true);
    addRecipe(biomeX(0, 0.50f), 0, 2,
              new FlyingTara(tm, 0.0f, 4.0f * TILE_SIZE_PX), true);
    addRecipe(biomeX(0, 0.30f), 0, 1,
              new M15ABradley(tm, 0.0f, (float)plainsFloorY()));
    addRecipe(biomeX(0, 0.80f), 0, 1,
              new M15ABradley(tm, 0.0f, (float)plainsFloorY()));
    addRecipe(biomeX(2, 0.30f), 2, 1,
              new EnemySub(tm, 0.0f, (float)aquaticY()));
    addRecipe(biomeX(2, 0.70f), 2, 1,
              new EnemySub(tm, 0.0f, (float)aquaticY()));


    const float L3_POW_FRACS[2] = { 0.30f, 0.70f };
    for (int i = 0; i < 2; ++i)
        addRecipe(biomeX(0, L3_POW_FRACS[i]), 0, 1,
                  new POWPrisoner(tm, 0.0f, (float)plainsFloorY(),
                                  (unsigned)(levelIndex * 31 + 11 + i * 13)));
    for (int i = 0; i < 2; ++i)
        addRecipe(biomeX(1, L3_POW_FRACS[i]), 1, 1,
                  new POWPrisoner(tm, 0.0f, (float)aerialFloorY(),
                                  (unsigned)(levelIndex * 31 + 41 + i * 13)));
    for (int i = 0; i < 2; ++i)
        addRecipe(biomeX(2, L3_POW_FRACS[i]), 2, 1,
                  new POWPrisoner(tm, 0.0f, (float)aquaticY(),
                                  (unsigned)(levelIndex * 31 + 67 + i * 13)));
}

void SurvivalLevel::tickSpawnTriggers(Camera* cam)
{
    if (cam == nullptr || entityMgr == nullptr) return;
    if (recipeCount <= 0) return;

    coordSyst camOff = cam->getOffset();
    float cameraRight = camOff.x + cam->getViewWidth();

    const int MAX_FIRES_PER_FRAME = 4;
    int fired = 0;

    for (int i = 0; i < recipeCount; ++i)
    {
        if (fired >= MAX_FIRES_PER_FRAME) break;
        if (recipes[i] == nullptr || recipes[i]->isSpawned()) continue;
        if (recipes[i]->getTriggerX() <= cameraRight)
        {
            recipes[i]->fire(*entityMgr, *this);
            ++fired;
        }
    }
}
