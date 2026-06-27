#pragma once
#include "Vehicle.h"



class AquaticVehicle : public Vehicle
{
protected:
    float depth;

public:
    AquaticVehicle(int hp) : Vehicle(hp), depth(0.0f) {}
    virtual ~AquaticVehicle() = default;
    virtual void dive(float dt);
};
