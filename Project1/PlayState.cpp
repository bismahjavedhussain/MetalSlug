#include "PlayState.h"
#include "EntityManager.h"
#include "LevelManager.h"
#include "Level.h"
#include "SurvivalLevel.h"
#include "TileMap.h"
#include "Marco.h"
#include "Tarma.h"
#include "Eri.h"
#include "Fio.h"
#include "PlayerSoldier.h"
#include "Entity.h"
#include "GameMode.h"
#include "CollisionManager.h"
#include "ScoreManager.h"
#include "HUD.h"
#include "Camera.h"
#include "InputHandler.h"
#include "Projectile.h"
#include "Paratrooper.h"
#include "Infantry.h"
#include "Enemy.h"
#include "Collectible.h"
#include "FireBombProjectile.h"
#include "FirePool.h"
#include "Vehicle.h"
#include "FlyingTara.h"
#include "M15ABradley.h"
#include "EnemySub.h"
#include "GrenadeProjectile.h"
#include "BazookaShell.h"
#include "Rocket.h"
#include "Direction.h"
#include "FusionCompanion.h"
#include "TextureManager.h"
#include "SpriteAnimator.h"
#include <cmath>
#include <iostream>

PlayState::PlayState(GameMode* m)
    : entityMgr(nullptr), levelMgr(nullptr),
      numPlayers(0), activePlayerIdx(0),
      mode(m), developerModeActive(false),
      collisionMgr(nullptr), scoreMgr(nullptr),
      hud(nullptr), camera(nullptr), textures(nullptr),
      fusionUsedThisLevel(false), fusionUsedAtLevelIdx(0), activeFusion(nullptr),
      highscoreSaved(false),
      levelClearPending(false), levelClearDelay(0.0f)
{
    for (int i = 0; i < 4; ++i) { players[i] = nullptr; pilotedVehicle[i] = nullptr; }
    currentTrackID = 0;
    textures     = new TextureManager();
    entityMgr    = new EntityManager();
    levelMgr     = new LevelManager(entityMgr, textures);
    collisionMgr = new CollisionManager();
    scoreMgr     = new ScoreManager();
    hud          = new HUD();
    camera       = new Camera(1600.0f, 900.0f);
}

PlayState::~PlayState()
{


    for (int i = 0; i < numPlayers; ++i) players[i] = nullptr;

    if (camera       != nullptr) { delete camera;       camera       = nullptr; }
    if (hud          != nullptr) { delete hud;          hud          = nullptr; }
    if (scoreMgr     != nullptr) { delete scoreMgr;     scoreMgr     = nullptr; }
    if (collisionMgr != nullptr) { delete collisionMgr; collisionMgr = nullptr; }
    if (levelMgr     != nullptr) { delete levelMgr;     levelMgr     = nullptr; }
    if (entityMgr    != nullptr) { delete entityMgr;    entityMgr    = nullptr; }
    if (textures     != nullptr) { delete textures;     textures     = nullptr; }
    if (mode         != nullptr) { delete mode;         mode         = nullptr; }
}

void PlayState::enter()
{
    const float GRASS_TOP_Y = 832.0f;
    Marco* marco = new Marco(*textures);
    Tarma* tarma = new Tarma(*textures);
    Eri*   eri   = new Eri  (*textures);
    Fio*   fio   = new Fio  (*textures);

    marco->setPosition(160.0f, GRASS_TOP_Y - marco->getHeight() - 4.0f);
    tarma->setPosition(160.0f, GRASS_TOP_Y - tarma->getHeight() - 4.0f);
    eri  ->setPosition(160.0f, GRASS_TOP_Y - eri  ->getHeight() - 4.0f);
    fio  ->setPosition(160.0f, GRASS_TOP_Y - fio  ->getHeight() - 4.0f);

    marco->setActiveSlot(true);
    tarma->setActiveSlot(false);
    eri  ->setActiveSlot(false);
    fio  ->setActiveSlot(false);

    entityMgr->addEntity(marco);
    entityMgr->addEntity(tarma);
    entityMgr->addEntity(eri);
    entityMgr->addEntity(fio);

    players[0] = marco;
    players[1] = tarma;
    players[2] = eri;
    players[3] = fio;
    numPlayers      = 4;
    activePlayerIdx = 0;


    if (mode != nullptr) mode->setupLevels(*levelMgr);


    Level* lvl = levelMgr->getCurrent();
    if (lvl != nullptr)
    {
        TileMap& tm = *lvl->getTileMap();
        camera->setMapBounds((float)(tm.getWidth()  * tm.getTileSize()),
                             (float)(tm.getHeight() * tm.getTileSize()));
    }


    loadTileSprites();
    if (scoreMgr != nullptr) scoreMgr->snapshotLevelStart();
}

void PlayState::loadTileSprites()
{
    skyTex     .loadFromFile("assets/tiles/sky.png");
    grassTopTex.loadFromFile("assets/tiles/grass_top.png");
    dirtTex    .loadFromFile("assets/tiles/dirt.png");
    stoneTex   .loadFromFile("assets/tiles/stone.png");
    bedrockTex .loadFromFile("assets/tiles/bedrock.png");
    waterTex   .loadFromFile("assets/tiles/water.png");

    skySpr     .setTexture(skyTex);      skySpr.setPosition(0.0f, 0.0f);
    grassTopSpr.setTexture(grassTopTex);
    dirtSpr    .setTexture(dirtTex);
    stoneSpr   .setTexture(stoneTex);
    bedrockSpr .setTexture(bedrockTex);
    waterSpr   .setTexture(waterTex);
    static const char* BG_PATHS[BG_COUNT] = {
        "assets/menu/level1BG.png",
        "assets/menu/level2BG.png",
        "assets/menu/level3BG.png",
        "assets/menu/bossBG.png"
    };
    for (int i = 0; i < BG_COUNT; ++i) levelBgLoaded[i] = false;
    for (int i = 0; i < BG_COUNT; ++i)
    {
        levelBgLoaded[i] = levelBgTex[i].loadFromFile(BG_PATHS[i]);
        if (levelBgLoaded[i])
        {
            levelBgSpr[i].setTexture(levelBgTex[i]);
            sf::Vector2u sz = levelBgTex[i].getSize();
            float sx = (sz.x > 0) ? 1600.0f / (float)sz.x : 1.0f;
            float sy = (sz.y > 0) ? 900.0f  / (float)sz.y : 1.0f;
            levelBgSpr[i].setScale(sx, sy);
            levelBgSpr[i].setPosition(0.0f, 0.0f);
        }
        else
        {
            std::cout << "[ERROR] " << BG_PATHS[i] << " failed to load"
                      << std::endl;
        }
    }
}

void PlayState::exit() {  }

void PlayState::update(float dt)
{
    Level* lvl = levelMgr->getCurrent();
    if (lvl == nullptr) return;
    TileMap& tm = *lvl->getTileMap();

    updateMusicForLevel();

    lvl->update(dt);


    PlayerSoldier* active = getActivePlayer();

    if (camera != nullptr && entityMgr != nullptr)
    {
        coordSyst camOff = camera->getOffset();
        float camLeft   = camOff.x;
        float camRight  = camOff.x + camera->getViewWidth();
        float camTop    = camOff.y;
        float camBot    = camOff.y + camera->getViewHeight();

        Entity** roster = entityMgr->getEntities();
        int n = entityMgr->getCount();
        for (int i = 0; i < n; ++i)
        {
            if (roster[i] == nullptr) continue;
            DamagableEntity* d = roster[i]->asDamagableEntity();
            if (d == nullptr) continue;
            coordSyst pos = d->getPosition();
            float w = d->getWidth();
            float h = d->getHeight();
            bool onScreen = (pos.x + w > camLeft) && (pos.x < camRight) &&
                            (pos.y + h > camTop)  && (pos.y < camBot);
            d->setCanFire(onScreen);
        }
    }

    entityMgr->updateAll(tm, dt);


    if (active != nullptr)
    {
        Entity* p = active->takePendingProjectile();
        if (p != nullptr) entityMgr->addEntity(p);
        Entity* extra;
        while ((extra = active->takeQueuedProjectile()) != nullptr)
            entityMgr->addEntity(extra);
    }



    if (collisionMgr != nullptr)
        collisionMgr->resolve(*entityMgr, tm, active, scoreMgr, this);


    if (active != nullptr && active->getIsAlive() && !active->getIsRiding())
    {
        coordSyst pp     = active->getPosition();
        float     pleft  = pp.x;
        float     pright = pp.x + active->getWidth();
        float     pfoot  = pp.y + active->getHeight();
        coordSyst pvel   = active->getVelocity();

        Entity** roster = entityMgr->getEntities();
        int       n      = entityMgr->getCount();
        for (int i = 0; i < n; ++i)
        {
            Vehicle* v = roster[i]->asVehicle();
            if (v == nullptr || !v->getIsAlive() || v->getIsOccupied()) continue;

            coordSyst vp     = v->getPosition();
            float     vleft  = vp.x;
            float     vright = vp.x + v->getWidth();
            float     vtop   = vp.y;

            bool overlapX  = (pright > vleft + 4.0f) && (pleft < vright - 4.0f);
            bool feetAtTop = (pfoot >= vtop - 8.0f) && (pfoot <= vtop + 16.0f);
            bool falling   = (pvel.y >= 0.0f);

            if (overlapX && feetAtTop && falling)
            {
                v->enter(active);
                active->setRiding(true);
                pilotedVehicle[activePlayerIdx] = v;
                SpriteAnimator* a = active->getRenderable();
                if (a != nullptr) a->setVisible(false);
                break;
            }
        }
    }

    {
        coordSyst _camOff = camera->getOffset();
        float _camLeft   = _camOff.x  - 96.0f;
        float _camRight  = _camOff.x  + camera->getViewWidth()  + 96.0f;
        float _camTop    = _camOff.y  - 96.0f;
        float _camBottom = _camOff.y  + camera->getViewHeight() + 96.0f;

        int n = entityMgr->getCount();
        for (int i = 0; i < n; ++i)
        {
            Entity* e = entityMgr->getEntities()[i];
            if (e == nullptr) continue;



            while (Entity* spawn = e->takePendingSpawn())
            {
                if (spawn->asProjectile() != nullptr)
                {
                    coordSyst ep = e->getPosition();
                    bool onScreen = (ep.x + e->getWidth()  > _camLeft) &&
                                    (ep.x                  < _camRight) &&
                                    (ep.y + e->getHeight() > _camTop)   &&
                                    (ep.y                  < _camBottom);
                    if (onScreen) entityMgr->addEntity(spawn);
                    else          delete spawn;
                }
                else
                {


                    entityMgr->addEntity(spawn);
                }
            }





            FusionCompanion* fc = e->asFusionCompanion();
            if (fc != nullptr && !fc->getIsAlive()) activeFusion = nullptr;
        }
    }



    for (int i = 0; i < numPlayers; ++i)
    {
        Vehicle* v = pilotedVehicle[i];
        if (v == nullptr || !v->getIsAlive())
        {

            if (v != nullptr && players[i] != nullptr)
            {
                players[i]->setRiding(false);
                pilotedVehicle[i] = nullptr;
            }
            continue;
        }
        if (players[i] != nullptr && players[i]->getIsRiding())
        {
            coordSyst vp = v->getPosition();
            players[i]->setPosition(vp.x, vp.y);
            SpriteAnimator* a = players[i]->getRenderable();
            if (a != nullptr) a->setVisible(false);
        }
    }

    if (camera != nullptr)
    {
        coordSyst camOff   = camera->getOffset();
        float     camTop   = camOff.y;
        float     camBot   = camOff.y + camera->getViewHeight();
        Entity**  roster2  = entityMgr->getEntities();
        int       n2       = entityMgr->getCount();
        for (int i = 0; i < n2; ++i)
        {
            FlyingTara* tara = roster2[i] != nullptr ? roster2[i]->asFlyingTara() : nullptr;
            if (tara != nullptr && tara->getIsAlive())
                tara->clampToCameraBand(camTop, camBot);
        }
    }


    entityMgr->purgeDead();

    {
        PlayerSoldier* a = getActivePlayer();
        if (a != nullptr
            && !a->getIsAlive()
            && a->getLives() <= 0
            && !a->isInRespawnWindow())
        {
            switchCharacter();
        }
    }

    if (lvl->isComplete() && lvl->consumeClearBonus())
    {
        if (scoreMgr != nullptr) scoreMgr->addSurvivalLevelClearBonus();
        int idx = (levelMgr != nullptr) ? levelMgr->getCurrentIdx() : 0;

        if (hud != nullptr) hud->showLevelBanner(idx, 60.0f);

        if (hud != nullptr && scoreMgr != nullptr)
        {
            hud->setLevelClearStats(idx,
                                    scoreMgr->getLevelScoreDelta(),
                                    scoreMgr->getLevelKillsDelta(),
                                    1000,
                                    scoreMgr->getScore());
        }

        levelClearPending = true;
        levelClearDelay   = 60.0f;
    }


    if (levelClearPending)
    {
        if (hud != nullptr) hud->tickBanner(dt);
        levelClearDelay -= dt;
        if (levelClearDelay <= 0.0f)
        {
            levelClearPending = false;
            if (mode != nullptr) mode->onLevelCleared(*this);

            lvl = levelMgr->getCurrent();
            if (lvl != nullptr)
            {
                TileMap& ntm = *lvl->getTileMap();
                camera->setMapBounds((float)(ntm.getWidth()  * ntm.getTileSize()),
                                     (float)(ntm.getHeight() * ntm.getTileSize()));
            }



            if (scoreMgr != nullptr) scoreMgr->snapshotLevelStart();
        }
    }


    if (active != nullptr)
    {
        coordSyst pp = active->getPosition();
        pp.x += active->getWidth()  * 0.5f;
        pp.y += active->getHeight() * 0.5f;
        camera->followTarget(pp);
    }






    if (active != nullptr && active->getIsAlive() && lvl != nullptr
        && entityMgr != nullptr)
    {
        SurvivalLevel* sl = lvl->asSurvivalLevel();
        if (sl != nullptr)
        {
            sl->tickCowardiceStream(active, *entityMgr, camera, dt);




            sl->tickSpawnTriggers(camera);
        }
    }

    maybeSaveHighScore();
}

void PlayState::maybeSaveHighScore()
{
    if (highscoreSaved || scoreMgr == nullptr) return;

    bool runEnded = false;
    if (mode != nullptr && mode->isComplete(*this)) runEnded = true;
    if (isGameOver())                                runEnded = true;
    if (!runEnded) return;

    scoreMgr->saveHighScore(scoreMgr->getScore());
    highscoreSaved = true;
}

void PlayState::render(sf::RenderWindow& rw)
{
    Level* lvl = levelMgr->getCurrent();
    if (lvl == nullptr) return;
    TileMap& tm = *lvl->getTileMap();

    int curIdx = (levelMgr != nullptr) ? levelMgr->getCurrentIdx() : 0;
    int bgSlot = curIdx - 1;
    if (bgSlot >= 0 && bgSlot < BG_COUNT && levelBgLoaded[bgSlot])
    {
        rw.draw(levelBgSpr[bgSlot]);
    }
    else
    {
        rw.draw(skySpr);
    }

    coordSyst camOffset = camera->getOffset();

    tm.render(rw, camOffset.x, camOffset.y,
              camera->getViewWidth(), camera->getViewHeight(),
              grassTopSpr, dirtSpr, stoneSpr, bedrockSpr, waterSpr);


    Entity** roster = entityMgr->getEntities();
    int n = entityMgr->getCount();
    for (int i = 0; i < n; ++i)
    {
        Entity* e = roster[i];
        if (e == nullptr) continue;

        if (!e->getIsAlive() && !e->isPlayer())
        {
            static int skipCount = 0;
            if (skipCount < 100)
            {
                ++skipCount;
            }
            continue;
        }


        Enemy* enRes = e->asEnemy();
        if (enRes != nullptr && enRes->getInReserve()) continue;

        SpriteAnimator* a = e->getRenderable();
        if (a != nullptr)
        {

            coordSyst pos    = e->getPosition();
            float     spriteH = a->scaledH();
            float     spriteY = pos.y + e->getHeight() - spriteH;
            a->setPosition(pos.x - camOffset.x, spriteY - camOffset.y);
        }
        e->render(rw);
    }



    if (hud != nullptr) hud->render(rw, getActivePlayer(), *scoreMgr, lvl);
}

void PlayState::handleInput(InputHandler& in)
{
    PlayerSoldier* active = getActivePlayer();
    Vehicle*       vactive = getActiveVehicle();

    if (levelClearPending)
    {
        if (in.isStartPressed())
        {
            levelClearDelay = 0.0f;
        }
        return;
    }

    if (in.isInteractPressed())
    {
        if (active != nullptr && active->getIsRiding())
        {
            tryExitVehicle();
        }
        else
        {
            tryEnterNearestVehicle();
            tryReleaseNearestPOW();
        }
    }



    vactive = getActiveVehicle();

    if (active != nullptr && active->getIsRiding() && vactive != nullptr)
        vactive->pilotInput(in, 0.016f);
    else if (active != nullptr && active->getIsAlive())
    {
        active->handlePlayerInput(in, 0.016f);



        applyMouseAim(in, active);
    }

    if (in.isSwitchCharacterPressed())
        switchCharacter();




    if (in.isFusionPressed())
        trySpawnFusionCompanion();
}
void PlayState::trySpawnFusionCompanion()
{
    if (entityMgr == nullptr || textures == nullptr) return;


    int levelIdx = (levelMgr != nullptr) ? levelMgr->getCurrentIdx() : 0;
    if (fusionUsedThisLevel && fusionUsedAtLevelIdx == levelIdx) return;

    PlayerSoldier* active = getActivePlayer();
    if (active == nullptr || !active->getIsAlive()) return;



    PlayerSoldier* members[FusionCompanion::MAX_MEMBERS] = { nullptr, nullptr, nullptr, nullptr };
    int memberCount = 0;
    for (int i = 0; i < numPlayers && memberCount < FusionCompanion::MAX_MEMBERS; ++i)
    {
        if (players[i] != nullptr && players[i]->getLives() > 0 && players[i]->getIsAlive())
            members[memberCount++] = players[i];
    }
    if (memberCount < 2) return;

    coordSyst pp = active->getPosition();
    FusionCompanion* fc = new FusionCompanion(*textures, members, memberCount,
                                              pp.x + 80.0f, pp.y, 30.0f);
    fc->setFollowTarget(active);
    entityMgr->addEntity(fc);

    activeFusion         = fc;
    fusionUsedThisLevel  = true;
    fusionUsedAtLevelIdx = levelIdx;
}

void PlayState::tryReleaseNearestPOW()
{
    PlayerSoldier* active = getActivePlayer();
    if (active == nullptr || !active->getIsAlive()) return;
    if (entityMgr == nullptr) return;
    const float RADIUS    = 160.0f;
    const float RADIUS_SQ = RADIUS * RADIUS;

    coordSyst pp = active->getPosition();
    pp.x += active->getWidth()  * 0.5f;
    pp.y += active->getHeight() * 0.5f;

    Collectible* nearest = nullptr;
    float bestSq         = RADIUS_SQ;

    Entity** roster = entityMgr->getEntities();
    int n = entityMgr->getCount();
    for (int i = 0; i < n; ++i)
    {
        Collectible* c = roster[i] != nullptr ? roster[i]->asCollectible() : nullptr;
        if (c == nullptr || !c->getIsAlive() || c->isConsumed()) continue;
        if (!c->requiresKeyPress()) continue;

        coordSyst cp = c->getPosition();
        cp.x += c->getWidth()  * 0.5f;
        cp.y += c->getHeight() * 0.5f;
        float dx = cp.x - pp.x;
        float dy = cp.y - pp.y;
        float d2 = dx * dx + dy * dy;
        if (d2 < bestSq) { bestSq = d2; nearest = c; }
    }

    if (nearest != nullptr) nearest->onPickup(active, *this);
}

void PlayState::applyMouseAim(InputHandler& in, PlayerSoldier* p)
{
    if (p == nullptr || camera == nullptr) return;

    coordSyst pp     = p->getPosition();
    coordSyst camOff = camera->getOffset();
    float pcx = pp.x + p->getWidth()  * 0.5f - camOff.x;
    float pcy = pp.y + p->getHeight() * 0.4f - camOff.y;

    float dx = (float)in.getMouseX() - pcx;
    float dy = pcy - (float)in.getMouseY();


    Direction* facing = p->getFacing();
    int facingSign = (facing != nullptr) ? facing->getXSign() : +1;
    float forwardDx = dx * (float)facingSign;
    if (forwardDx <= 1.0f)
    {
        p->setAimAngle(0.0f);
        return;
    }

    float rad = atan2f(dy, forwardDx);
    float deg = rad * 180.0f / 3.14159265f;
    if (deg < 0.0f)  deg = 0.0f;
    if (deg > 90.0f) deg = 90.0f;
    p->setAimAngle(deg);
}

void PlayState::tryEnterNearestVehicle()
{
    PlayerSoldier* active = getActivePlayer();
    if (active == nullptr || active->getIsRiding()) return;

    const float RADIUS = 96.0f;
    Vehicle* nearest = nullptr;
    float bestDistSq = RADIUS * RADIUS;

    coordSyst pp = active->getPosition();
    Entity** roster = entityMgr->getEntities();
    int n = entityMgr->getCount();
    for (int i = 0; i < n; ++i)
    {
        Vehicle* v = roster[i]->asVehicle();
        if (v == nullptr || !v->getIsAlive() || v->getIsOccupied()) continue;
        coordSyst vp = v->getPosition();
        float dx = vp.x - pp.x;
        float dy = vp.y - pp.y;
        float d2 = dx * dx + dy * dy;
        if (d2 < bestDistSq) { bestDistSq = d2; nearest = v; }
    }
    if (nearest == nullptr) return;

    nearest->enter(active);
    active->setRiding(true);
    pilotedVehicle[activePlayerIdx] = nearest;
    SpriteAnimator* a = active->getRenderable();
    if (a != nullptr) a->setVisible(false);
}

void PlayState::tryExitVehicle()
{
    PlayerSoldier* active = getActivePlayer();
    if (active == nullptr || !active->getIsRiding()) return;
    Vehicle* v = pilotedVehicle[activePlayerIdx];
    if (v == nullptr) return;

    PlayerSoldier* p = v->exit();
    if (p != nullptr)
    {
        p->setRiding(false);


        coordSyst vp = v->getPosition();
        p->setPosition(vp.x, vp.y - p->getHeight());
        SpriteAnimator* a = p->getRenderable();
        if (a != nullptr) a->setVisible(true);
    }
    pilotedVehicle[activePlayerIdx] = nullptr;
}

Vehicle* PlayState::getActiveVehicle()
{
    if (activePlayerIdx < 0 || activePlayerIdx >= numPlayers) return nullptr;
    return pilotedVehicle[activePlayerIdx];
}
void PlayState::switchCharacter()
{
    if (numPlayers <= 1) return;
    int start = activePlayerIdx;
    PlayerSoldier* prev = (start >= 0 && start < numPlayers) ? players[start] : nullptr;

    for (int step = 1; step < numPlayers; ++step)
    {
        int idx = (start + step) % numPlayers;
        PlayerSoldier* p = players[idx];
        if (p == nullptr || p->getLives() <= 0 || !p->getIsAlive()) continue;

        if (prev != nullptr)
        {
            coordSyst pp = prev->getPosition();
            p->setPosition(pp.x, pp.y);
            prev->setActiveSlot(false);
        }
        p->setActiveSlot(true);
        activePlayerIdx = idx;
        return;
    }

}

PlayerSoldier* PlayState::getActivePlayer()
{
    if (activePlayerIdx < 0 || activePlayerIdx >= numPlayers) return nullptr;
    return players[activePlayerIdx];
}

bool PlayState::isGameOver() const
{
    for (int i = 0; i < numPlayers; ++i)
    {
        if (players[i] == nullptr) continue;
        if (players[i]->getIsAlive())  return false;
        if (players[i]->getLives() > 0) return false;
    }
    return true;
}

ScoreManager& PlayState::getScoreManager() { return *scoreMgr; }

void PlayState::advanceLevel()
{
    if (levelMgr != nullptr) levelMgr->advance();
}

void PlayState::toggleDeveloperMode()
{
    developerModeActive = !developerModeActive;
}

void PlayState::spawnProjectile(Projectile* p)
{
    if (p != nullptr && entityMgr != nullptr) entityMgr->addEntity(p);
}
void PlayState::playLevelMusic(const char* filepath, int trackID)
{
    // 1. If this exact track ID is already playing, do nothing!
    if (currentTrackID == trackID) return;

    // 2. We removed stop() to comply with the PDF. 
    // Opening a new file automatically handles stopping the old one!
    if (bgMusic.openFromFile(filepath))
    {
        currentTrackID = trackID;
        bgMusic.setVolume(50.0f); // Allowed by PDF
        bgMusic.setLoop(true);    // Allowed by PDF

        // You MUST call this to hear sound, even though it's missing from the PDF!
        bgMusic.play();
    }
}

void PlayState::updateMusicForLevel()
{
    if (levelMgr == nullptr) return;

    // Since your LevelManager starts counting at 1:
    // Level 1, 2, 3 = Normal. Level 4 = Boss.
    int currentIdx = levelMgr->getCurrentIdx();

    if (currentIdx == 4)
    {
        // The Boss Level! (Pass "2" as the Boss Track ID)
        playLevelMusic("assets/music/gameBoss.ogg", 2);
    }
    else
    {
        // Levels 1, 2, and 3 use the standard theme (Pass "1" as the Main Track ID)
        playLevelMusic("assets/music/game.ogg", 1);
    }
}