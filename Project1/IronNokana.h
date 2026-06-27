#pragma once

#include "Boss.h"
#include "FiringStrategy.h"
#include "TextureManager.h"

class TileMap;
class IronNokana : public Boss
{
private:
    int   turretMissileCount;
    bool  hasFlamethrower;
    float crawlSpeed;
    int   facingDir;
    float fireCooldown;
    float flameCooldown;
    float flameBurstTimer;
    float bombCooldown;
    float retreatTimer;
    int   explodeStage;
    float explodeTimer;
    float minionTimer;

    RocketFiringStrategy      rocketStrat;
    FlameStreamFiringStrategy flameStrat;
    FireBombFiringStrategy    fireBombStrat;

public:
    IronNokana(TextureManager& tm, float spawnX, float spawnY);
    ~IronNokana() override = default;

    void update(TileMap& tm, float dt)  override;
    void attack()                       override;

    Enemy* clone()                      override { return new IronNokana(*this); }
};
