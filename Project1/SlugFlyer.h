#pragma once
#include "AerialVehicle.h"

class TextureManager;
class InputHandler;




class SlugFlyer : public AerialVehicle
{
private:
    int   missilesRemaining;
    float aimAngle;

public:
    SlugFlyer(TextureManager& tm, float spawnX, float spawnY);
    ~SlugFlyer() override = default;

    void   update(TileMap& tm, float dt)            override;
    Entity* fire(coordSyst aim)                     override;
    void   pilotInput(InputHandler& in, float dt)   override;
};
