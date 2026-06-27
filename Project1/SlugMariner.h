#pragma once
#include "AquaticVehicle.h"

class TextureManager;
class InputHandler;







class SlugMariner : public AquaticVehicle
{
private:
    int   horizontalMissiles;
    int   verticalMissiles;
    int   reverseArcMissiles;
    float aimAngle;

public:
    SlugMariner(TextureManager& tm, float spawnX, float spawnY);
    ~SlugMariner() override = default;

    void   update(TileMap& tm, float dt)            override;
    Entity* fire(coordSyst aim)                     override;
    void   pilotInput(InputHandler& in, float dt)   override;
};
