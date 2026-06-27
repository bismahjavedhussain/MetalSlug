#pragma once

#include "Boss.h"
#include "FiringStrategy.h"
#include "TextureManager.h"

class TileMap;
class SeaSatan : public Boss
{
private:
    int   rocketCount;
    float cruiseSpeed;
    int   facingDir;
    float rocketCooldown;
    float hmgBurstTimer;
    float hmgRestTimer;
    float retreatTimer;
    int   explodeStage;
    float explodeTimer;

    RocketFiringStrategy rocketStrat;
    HMGFiringStrategy    hmgStrat;

public:
    SeaSatan(TextureManager& tm, float spawnX, float spawnY);
    ~SeaSatan() override = default;

    void update(TileMap& tm, float dt)  override;
    void attack()                       override;

    Enemy* clone()                      override { return new SeaSatan(*this); }
};
