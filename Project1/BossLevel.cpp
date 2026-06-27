#include "BossLevel.h"
#include "BossPhase.h"
#include "TileMap.h"
#include "AirTile.h"
#include "SolidTile.h"
#include "WaterTile.h"
#include "IndestructibleTile.h"
#include "AerialBiome.h"
#include "PlainsBiome.h"
#include "AquaticBiome.h"
#include "EntityManager.h"
#include "Entity.h"
#include "PlayerSoldier.h"
#include "Boss.h"
#include "IronNokana.h"
#include "HairBusterRiberts.h"
#include "SeaSatan.h"
#include "UltimateBoss.h"
#include "MetalSlug.h"
#include "SlugFlyer.h"
#include "SlugMariner.h"
#include "AmphibiousSlug.h"
#include "SupplyCrate.h"
#include "TextureManager.h"
#include <iostream>

static const int LEVEL_W      = 250;
static const int LEVEL_H      = 30;
static const int TILE_SIZE_PX = 64;
static const int SEA_LEVEL    = 13;
static const int PLAINS_END   = 80;
static const int AERIAL_END   = 170;
static const int PLAINS_FLOOR_ROW   = 12;
static const int PLAINS_GROUND_ROW  = 13;
static const int AERIAL_FLOOR_ROW   = 8;
static const int SEABED_ROW         = 28;
static const int BEDROCK_ROW        = 29;
static const int AQUATIC_ROW        = 27;
static const float BOSS_H_PX        = 96.0f;
static const float BOSS_GROUND_Y    = (float)(PLAINS_GROUND_ROW * TILE_SIZE_PX) - BOSS_H_PX;
static const float BOSS_AERIAL_Y    = (float)(4 * TILE_SIZE_PX);
static const float BOSS_AQUATIC_Y   = (float)(SEABED_ROW * TILE_SIZE_PX) - BOSS_H_PX;

static int aerialFloorY()  { return AERIAL_FLOOR_ROW * TILE_SIZE_PX; }
static int plainsFloorY()  { return PLAINS_FLOOR_ROW * TILE_SIZE_PX; }
static int aquaticY()      { return AQUATIC_ROW      * TILE_SIZE_PX; }

BossLevel::BossLevel(EntityManager* em, TextureManager* tm)
    : Level(),
      groundBoss(nullptr), aerialBoss(nullptr), aquaticBoss(nullptr),
      ultimateBoss(nullptr),
      activeBoss(nullptr),
      currentPhase(nullptr),
      activeBatchAlive(0),
      activeBatchOriginalSize(0),
      entityMgr(em), textures(tm),
      complete(false),
      clearBonusAwarded(false)
{
    levelIndex = 4;
}

BossLevel::~BossLevel()
{
    groundBoss   = nullptr;
    aerialBoss   = nullptr;
    aquaticBoss  = nullptr;
    ultimateBoss = nullptr;
    activeBoss   = nullptr;
    if (currentPhase != nullptr) { delete currentPhase; currentPhase = nullptr; }
}

int BossLevel::getPhase() const
{
    return currentPhase != nullptr ? currentPhase->phaseId() : 0;
}
void BossLevel::generateTerrain()
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
    {
        const int kStepWidths [10] = { 3, 4, 3, 4, 3, 4, 3, 4, 3, 4 };
        const int kStepHeights[10] = {12,11,10,11,12,10,11,12,10,11 };
        int patternIdx    = 0;
        int colsRemaining = kStepWidths [0];
        int currentTop    = kStepHeights[0];
        for (int x = PLAINS_END; x < AERIAL_END; ++x)
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


    for (int x = AERIAL_END; x < LEVEL_W; ++x)
    {
        for (int y = SEA_LEVEL; y < SEABED_ROW; ++y)
            tileMap->setTile(x, y, new WaterTile());
        tileMap->setTile(x, SEABED_ROW, new SolidTile());
    }

    const int blendedStart = LEVEL_W - 15;
    for (int x = blendedStart; x < LEVEL_W; ++x)
        tileMap->setTile(x, PLAINS_GROUND_ROW, new SolidTile());
}

void BossLevel::spawnPlayerVehicles()
{
    if (entityMgr == nullptr || textures == nullptr) return;
    const float spanW = (float)(LEVEL_W * TILE_SIZE_PX);
    entityMgr->addEntity(new MetalSlug      (*textures, (float)(25  * TILE_SIZE_PX), (float)plainsFloorY() - 64.0f));
    entityMgr->addEntity(new SlugFlyer      (*textures, (float)(120 * TILE_SIZE_PX), (float)aerialFloorY() + 64.0f));
    entityMgr->addEntity(new SlugMariner    (*textures, (float)(AERIAL_END * TILE_SIZE_PX), (float)SEA_LEVEL * TILE_SIZE_PX));
    entityMgr->addEntity(new AmphibiousSlug (*textures, (float)(215 * TILE_SIZE_PX), (float)plainsFloorY() - 64.0f));
}

void BossLevel::spawnEnemies()
{
    if (currentPhase != nullptr) { delete currentPhase; }
    currentPhase = new BossPhase1Ground();
    currentPhase->enter(this);
    if (entityMgr != nullptr)
    {
        Entity** roster = entityMgr->getEntities();
        int n = entityMgr->getCount();
        //for (int i = 0; i < n; ++i)
        //{
        //    Entity* e = roster[i];
        //    if (e == nullptr || !e->getIsAlive()) continue;
        //    if (e->isPlayer()) continue;
        //    if (e->asVehicle() != nullptr) continue;
        //    const char* kind = "Entity";
        //    if      (e->asBoss()        != nullptr) kind = "Boss";
        //    else if (e->asEnemy()       != nullptr) kind = "Enemy";
        //    else if (e->asProjectile()  != nullptr) kind = "Projectile";
        //    else if (e->asCollectible() != nullptr) kind = "Collectible";
        //    coordSyst p = e->getPosition();
        //    std::cout << "  idx=" << i << " kind=" << kind
        //              << " pos=(" << p.x << ", " << p.y << ")" << std::endl;
        //}
    }
}

void BossLevel::enterPhase1()
{
    if (entityMgr == nullptr || textures == nullptr) return;

    float spawnX = (float)(50 * TILE_SIZE_PX);

    groundBoss = new IronNokana(*textures, spawnX, BOSS_GROUND_Y);
    entityMgr->addEntity(groundBoss);
    activeBoss = groundBoss;

}

void BossLevel::enterPhase2()
{
    if (entityMgr == nullptr || textures == nullptr) return;

    float spawnX = (float)(125 * TILE_SIZE_PX);

    aerialBoss = new HairBusterRiberts(*textures, spawnX, BOSS_AERIAL_Y);
    entityMgr->addEntity(aerialBoss);
    activeBoss = aerialBoss;

}

void BossLevel::enterPhase3()
{
    if (entityMgr == nullptr || textures == nullptr) return;

    float spawnX = (float)(210 * TILE_SIZE_PX);

    aquaticBoss = new SeaSatan(*textures, spawnX, BOSS_AQUATIC_Y);
    entityMgr->addEntity(aquaticBoss);
    activeBoss = aquaticBoss;

}
void BossLevel::enterPhase4()
{
    if (entityMgr == nullptr || textures == nullptr)
     return;

    float fusionX = (float)(240 * TILE_SIZE_PX);

    ultimateBoss = new UltimateBoss(*textures, fusionX,
                                    BOSS_GROUND_Y,
                                    BOSS_AERIAL_Y,
                                    BOSS_AQUATIC_Y);
    entityMgr->addEntity(ultimateBoss);
    activeBoss = ultimateBoss;

}

void BossLevel::drainBossActions(Boss* b, float )
{
    if (b == nullptr || entityMgr == nullptr)
     return;
    if (Entity* shot = b->takePendingShot())
    {
        entityMgr->addEntity(shot);
    }
    if (b->consumeMinionRequest())
    {
        b->spawnMinions(entityMgr);
        activeBatchOriginalSize = b->getMinionBatchSize();
        activeBatchAlive        = activeBatchOriginalSize;
    }
    if (b->consumeCrateRequest())
    {
        coordSyst at = b->getPosition();
        spawnSupplyCrateAt(at.x + b->getWidth() * 0.5f, at.y - 32.0f);
    }
}

void BossLevel::spawnSupplyCrateAt(float x, float y)
{
    if (entityMgr == nullptr || textures == nullptr) return;
    entityMgr->addEntity(new SupplyCrate(*textures, x, y, 0xB055C0DE));
}

bool BossLevel::bossDead(Boss* b) const
{
    return b == nullptr || !b->getIsAlive();
}

void BossLevel::update(float dt)
{
    if (tileMap != nullptr) tileMap->tickCraterFill(dt);
    float activePlayerX = 0.0f;
    bool  havePlayerX   = false;
    if (entityMgr != nullptr)
    {
        Entity** roster = entityMgr->getEntities();
        int n = entityMgr->getCount();
        for (int i = 0; i < n; ++i)
        {
            Entity* e = roster[i];
            if (e == nullptr || !e->isPlayer()) continue;
            PlayerSoldier* ps = e->asPlayerSoldier();
            if (ps == nullptr || !ps->getIsActiveSlot()) continue;
            activePlayerX = ps->getPosition().x + ps->getWidth() * 0.5f;
            havePlayerX   = true;
            break;
        }
    }
    if (havePlayerX && activeBoss != nullptr)
    {
        activeBoss->setChaseTarget(activePlayerX);
    }


    if (activeBoss != nullptr)
        drainBossActions(activeBoss, dt);

    {  float playerX = -1.0f;
        if (entityMgr != nullptr)
        {
            Entity** roster = entityMgr->getEntities();
            int n = entityMgr->getCount();
            for (int i = 0; i < n; ++i)
            {
                Entity* e = roster[i];
                if (e == nullptr || !e->isPlayer()) continue;
                PlayerSoldier* ps = e->asPlayerSoldier();
                if (ps == nullptr || !ps->getIsActiveSlot()) continue;
                playerX = ps->getPosition().x;
                break;
            }
        }
        const float RIGHT_EDGE_TRIGGER_X = (float)((LEVEL_W - 5) * TILE_SIZE_PX);
        if (playerX > RIGHT_EDGE_TRIGGER_X && activeBoss != nullptr
            && activeBoss->getIsAlive() && activeBoss != (Boss*)ultimateBoss)
        {
            activeBoss->takeDamage(9999, nullptr);
            if (activeBoss->getIsAlive())
            {
            }
        }
    }

    if (currentPhase != nullptr)
    {
        int prevPhase = currentPhase->phaseId();
        BossPhase* next = currentPhase->tick(this);
        if (next != nullptr)
        {
            delete currentPhase;
            currentPhase = next;
            currentPhase->enter(this);
        }
    }

    if (activeBoss != nullptr && activeBatchAlive > 0 && entityMgr != nullptr)
    {
        Entity** roster = entityMgr->getEntities();
        int n = entityMgr->getCount();
        int aliveMinions = 0;


        for (int i = 0; i < n; ++i)
        {
            Entity* e = roster[i];
            if (e == nullptr || !e->getIsAlive()) continue;
            if (e == (Entity*)activeBoss) continue;
            ++aliveMinions;
        }
        if (aliveMinions == 0)
        {
            activeBoss->requestCrateDrop();
            activeBatchAlive        = 0;
            activeBatchOriginalSize = 0;
        }
    }
}

void BossLevel::render(sf::RenderWindow& )
{

}

bool BossLevel::isComplete()
{
    return complete;
}

bool BossLevel::consumeClearBonus()
{
    if (!complete || clearBonusAwarded) return false;
    clearBonusAwarded = true;
    return true;
}
