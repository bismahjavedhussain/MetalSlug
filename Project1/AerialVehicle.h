#pragma once
#include "Vehicle.h"


class AerialVehicle : public Vehicle
{
protected:
    float hoverHeight;

public:
    AerialVehicle(int hp) : Vehicle(hp), hoverHeight(0.0f) {}
    virtual ~AerialVehicle() = default;

    virtual void ascend(float dt);
};
