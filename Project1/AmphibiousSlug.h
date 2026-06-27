#pragma once
#include "Vehicle.h"

class TextureManager;
class InputHandler;
class VehicleModeStrategy;

class AmphibiousSlug : public Vehicle
{
private:
    VehicleModeStrategy* currentMode;
    float aimAngle;

public:
    AmphibiousSlug(TextureManager& tm, float spawnX, float spawnY);
    ~AmphibiousSlug() override;

    void   update(TileMap& tm, float dt) override;
    Entity* fire(coordSyst aim)override;
    void   pilotInput(InputHandler& in, float dt) override;
    void   switchMode(TileMap& tm);
    void fireAsSlug              (coordSyst aim);
    void fireAsFlyerMissile      (coordSyst aim);
    void fireAsFlyerBullet       (coordSyst aim);
    void fireAsMarinerHorizontal (coordSyst aim);
    void fireAsMarinerVertical   (coordSyst aim);
    void fireAsMarinerReverse    (coordSyst aim);
};
