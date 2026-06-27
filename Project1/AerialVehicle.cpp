#include "AerialVehicle.h"



void AerialVehicle::ascend(float dt)
{
    velocity.y -= 600.0f * dt;
    if (velocity.y < -400.0f) velocity.y = -400.0f;
}
