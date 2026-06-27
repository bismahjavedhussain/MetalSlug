#pragma once
#include "EnemyVehicle.h"
#include "TextureManager.h"

class TileMap;
class BazookaShell;
class M15ABradley : public EnemyVehicle
{
private:
    bool          isStationary;
    float         crawlSpeed;
    int           facingDir;
    float         fireCooldown;
    coordSyst     pendingShellOrigin;
    coordSyst     pendingShellAim;
    bool          hasPendingShell;

public:
    M15ABradley(TextureManager& tm, float spawnX, float spawnY);
    ~M15ABradley() override = default;

    void update(TileMap& tm, float dt) override;
    void attack();
    bool takePendingShell(coordSyst& outOrigin, coordSyst& outAim);
    void onDestroy()                   override;


    M15ABradley* asM15ABradley() override { return this; }
    Entity* takePendingSpawn() override;


    Entity* clone() override;
};
