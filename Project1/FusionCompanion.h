#pragma once
#include "Soldier.h"
#include "TextureManager.h"

class PlayerSoldier;
class TileMap;
class FusionCompanion : public Soldier
{
public:
    static const int MAX_MEMBERS = 4;

private:
    PlayerSoldier* members[MAX_MEMBERS];
    int  memberCount;
    float fireRateMultiplier;
    float speedMultiplier;
    float meleeDamageMultiplier;
    float ammoPickupMultiplier;
    float blastRadiusMultiplier;
    float lifetime;
    PlayerSoldier* followTarget;
    Entity* pendingShot;
    float   fireCooldown;
    int     facingDir;

    void averageStatsFromMembers();

public:
    FusionCompanion(TextureManager& tm,
                    PlayerSoldier* fusionMembers[MAX_MEMBERS],
                    int            count,
                    float          spawnX,
                    float          spawnY,
                    float          lifetimeSeconds = 30.0f);
    ~FusionCompanion() override;

    void update(TileMap& tm, float dt) override;
    void attack()                      override;


    void takeDamage(int , class DamageSource* ) override {}

    void setFollowTarget(PlayerSoldier* p) { followTarget = p; }



    Entity* takePendingShot();

    int   getMemberCount()           const { return memberCount; }
    float getLifetime()              const { return lifetime; }
    float getFireRateMultiplier()    const { return fireRateMultiplier; }
    float getSpeedMultiplier()       const { return speedMultiplier; }
    float getMeleeDamageMult()       const { return meleeDamageMultiplier; }
    float getAmmoPickupMult()        const { return ammoPickupMultiplier; }
    float getBlastRadiusMult()       const { return blastRadiusMultiplier; }
    void render( sf:: RenderWindow& rw);
    FusionCompanion* asFusionCompanion() override { return this; }
    Entity* takePendingSpawn() override { return takePendingShot(); }
};
