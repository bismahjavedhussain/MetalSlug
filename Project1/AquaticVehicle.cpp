#include "AquaticVehicle.h"

void AquaticVehicle::dive(float dt)
{
    velocity.y += 200.0f * dt;
    if (velocity.y > 220.0f) velocity.y = 220.0f;
}
