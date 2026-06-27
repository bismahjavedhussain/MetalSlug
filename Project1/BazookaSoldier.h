#pragma once
#include "Infantry.h"
#include "TextureManager.h"




class BazookaSoldier : public Infantry
{
private:
    float walkSpeed;
    float fireCooldown;
    int   facingDir;

public:
    BazookaSoldier(TextureManager& tm, float spawnX, float spawnY, int batchId = 0);
    ~BazookaSoldier() override = default;
    void  update(TileMap& tm, float dt) override;
    void  attack() override;
    Enemy* clone() override;
};
