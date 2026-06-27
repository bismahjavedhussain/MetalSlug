#pragma once
#include "Infantry.h"
#include "TextureManager.h"






class ShieldedSoldier : public Infantry
{
private:
    float walkSpeed;
    float shootCooldown;
    int   facingDir;

public:
    ShieldedSoldier(TextureManager& tm, float spawnX, float spawnY, int batchId = 0);
    ~ShieldedSoldier() override = default;

    void  update(TileMap& tm, float dt)               override;
    void  attack()                                    override;
    void  takeDamage(int amt, DamageSource* src)      override;



    bool  blockAttack(coordSyst bulletDirection);



    bool  blocksProjectile(coordSyst incomingDir, bool isExplosive) override;

    Enemy* clone()                                    override;
};
