#pragma once
#include "coordSyst.h"

class AmphibiousSlug;
class TileMap;




class VehicleModeStrategy
{
protected:
    AmphibiousSlug* owner;

public:
    VehicleModeStrategy() : owner(nullptr) {}
    virtual ~VehicleModeStrategy() = default;

    void setOwner(AmphibiousSlug* o) { owner = o; }

    virtual void               fire(coordSyst aim)                 = 0;
    virtual void               update(TileMap& tm, float dt)       = 0;



    virtual VehicleModeStrategy* canSwitchTo(TileMap& tm)          = 0;
};

class NormalSlugMode : public VehicleModeStrategy
{
public:
    void                fire(coordSyst aim)            override;
    void                update(TileMap& tm, float dt)  override;
    VehicleModeStrategy* canSwitchTo(TileMap& tm)      override;
};

class FlyerMode : public VehicleModeStrategy
{
    int missilesRemaining;
public:
    FlyerMode() : missilesRemaining(4) {}
    void                fire(coordSyst aim)            override;
    void                update(TileMap& tm, float dt)  override;
    VehicleModeStrategy* canSwitchTo(TileMap& tm)      override;
};

class MarinerMode : public VehicleModeStrategy
{
    int horizontalMissiles;
    int verticalMissiles;
    int reverseArcMissiles;
public:
    MarinerMode()
        : horizontalMissiles(3), verticalMissiles(3), reverseArcMissiles(3) {}
    void                fire(coordSyst aim)            override;
    void                update(TileMap& tm, float dt)  override;
    VehicleModeStrategy* canSwitchTo(TileMap& tm)      override;
};
