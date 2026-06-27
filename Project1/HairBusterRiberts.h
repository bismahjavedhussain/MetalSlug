#pragma once

#include "Boss.h"
#include "FiringStrategy.h"
#include "TextureManager.h"

class TileMap;
class HairBusterRiberts : public Boss
{
private:
    int   rocketCount;
    int   fireBombCount;
    float hoverY;
    float driftSpeed;
    int   facingDir;
    float driftTimer;
    float rocketCooldown;
    float bombCooldown;
    float diveCooldown;
    bool  isDiving;
    float diveTimer;
    float retreatTimer;
    int   explodeStage;
    float explodeTimer;
    RocketFiringStrategy   rocketStrat;
    FireBombFiringStrategy fireBombStrat;

public:
    HairBusterRiberts(TextureManager& tm, float spawnX, float spawnY);
    ~HairBusterRiberts() override = default;

    void update(TileMap& tm, float dt)  override;
    void attack()  override;

    Enemy* clone() override { return new HairBusterRiberts(*this); }
    bool isAerial() const override { return true; }
};
