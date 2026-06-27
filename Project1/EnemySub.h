#pragma once
#include "EnemyVehicle.h"
#include "TextureManager.h"

class TileMap;
class Rocket;
class EnemySub : public EnemyVehicle
{
private:
    float horizSpeed;
    int  facingDir;
    float fireCooldown;
    coordSyst  pendingRocketOrigin;
    coordSyst  pendingRocketAim;
    bool hasPendingRocket;

public:
    EnemySub(TextureManager& tm, float spawnX, float spawnY);
    ~EnemySub() override = default;

    void update(TileMap& tm, float dt) override;
    void attack();
    bool takePendingRocket(coordSyst& outOrigin, coordSyst& outAim);
    void onDestroy() override;

    EnemySub* asEnemySub() override { return this; }
    Entity* takePendingSpawn() override;
    Entity* clone() override;
};
