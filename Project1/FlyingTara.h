#pragma once
#include "EnemyVehicle.h"
#include "TextureManager.h"

class TileMap;
class FlyingTara : public EnemyVehicle
{
private:
    float  hoverY;
    float   horizSpeed;
    int   facingDir;
    float  dropCooldown;
    coordSyst pendingDropOrigin;
    bool  hasPendingDrop;

public:
    FlyingTara(TextureManager& tm, float spawnX, float spawnY);
    ~FlyingTara() override = default;

    void update(TileMap& tm, float dt) override;
    void attack();
    bool takePendingDrop(coordSyst& outOrigin);
    void onDestroy() override;
    Entity* takePendingSpawn() override;
    void clampToCameraBand(float cameraTopY, float cameraBottomY);


    FlyingTara* asFlyingTara() override { return this; }
    Entity* clone() override;
};
