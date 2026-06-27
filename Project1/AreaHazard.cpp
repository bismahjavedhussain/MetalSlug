#include "AreaHazard.h"

AreaHazard::AreaHazard(int dps, float dur)
    : Entity(), damagePerSecond(dps), duration(dur)
{
    isAlive = true;
}

void AreaHazard::render(sf::RenderWindow& ) {}
