#pragma once
#include "Undead.h"
#include "TextureManager.h"

class MummyWarrior : public Undead
{
private:
    float crumbleTimer;
    bool  isCrumbled;
    float resurrectionDelay;
    float walkSpeed;
    int   facingDir;

public:
    MummyWarrior(TextureManager& tm, float spawnX, float spawnY);
    ~MummyWarrior() override = default;

    void update(TileMap& tm, float dt)              override;
    void attack()                                   override;
    void onPlayerContact(PlayerSoldier* p)          override;
    void takeDamage(int amount, DamageSource* src)  override;
    void resurrect();
    Enemy* clone()                                  override;
};
