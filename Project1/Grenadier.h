#pragma once
#include "Infantry.h"
#include "TextureManager.h"

class Grenadier : public Infantry
{
private:
    float walkSpeed;
    float lobCooldown;
    int   facingDir;

public:
    Grenadier(TextureManager& tm, float spawnX, float spawnY, int batchId = 0);
    ~Grenadier() override = default;

    void  update(TileMap& tm, float dt)               override;
    void  attack()                                    override;
    Enemy* clone()                                    override;
};
