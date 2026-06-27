#pragma once
#include "Level.h"

class EntityManager;
class TextureManager;
class IronNokana;
class HairBusterRiberts;
class SeaSatan;
class UltimateBoss;
class Boss;
class BossPhase;
class BossPhase1Ground;
class BossPhase2Aerial;
class BossPhase3Aquatic;
class BossPhase4Fused;
class BossPhaseDone;


class BossLevel : public Level
{
    friend class BossPhase1Ground;
    friend class BossPhase2Aerial;
    friend class BossPhase3Aquatic;
    friend class BossPhase4Fused;
    friend class BossPhaseDone;

private:

    IronNokana*         groundBoss;
    HairBusterRiberts*  aerialBoss;
    SeaSatan*           aquaticBoss;
    UltimateBoss*       ultimateBoss;
    Boss*       activeBoss;
    BossPhase*  currentPhase;

    int    activeBatchAlive;
    int    activeBatchOriginalSize;

    EntityManager*  entityMgr;
    TextureManager* textures;
    bool            complete;
    bool            clearBonusAwarded;

    void  enterPhase1();
    void  enterPhase2();
    void  enterPhase3();
    void  enterPhase4();
    void  drainBossActions(Boss* b, float dt);
    void  spawnSupplyCrateAt(float x, float y);
    bool  bossDead(Boss* b) const;

public:
    BossLevel(EntityManager* em, TextureManager* tm);
    ~BossLevel() override;

    void update(float dt)                  override;
    void render(sf::RenderWindow& rw)      override;
    void generateTerrain()                 override;
    void spawnEnemies()                    override;
    void spawnPlayerVehicles()             override;
    bool isComplete()                      override;
    bool consumeClearBonus()               override;

    int   getPhase() const;
    Boss* getActiveBoss() { return activeBoss; }
    BossLevel* asBossLevel() override { return this; }
};
