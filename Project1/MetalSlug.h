#pragma once
#include "GroundVehicle.h"

class TextureManager;
class InputHandler;
class Bullet;
class MetalSlug : public GroundVehicle
{
private:
    float aimAngle;

public:
    MetalSlug(TextureManager& tm, float spawnX, float spawnY);
    ~MetalSlug() override = default;

    void   update(TileMap& tm, float dt)            override;
    Entity* fire(coordSyst aim)                     override;
    void   pilotInput(InputHandler& in, float dt)   override;
};
