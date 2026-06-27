#pragma once
#include "Vehicle.h"

class GroundVehicle : public Vehicle
{
protected:
    float treadSpeed;

public:
    GroundVehicle(int hp) : Vehicle(hp), treadSpeed(220.0f) {}
    virtual ~GroundVehicle() = default;

    virtual void traverseStep(TileMap& tm);
};
