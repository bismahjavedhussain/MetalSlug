#include "EnemyVehicle.h"

void EnemyVehicle::onDestroy()
{
    isAlive = false;
}

void EnemyVehicle::die()
{
    if (!isAlive) return;
    onDestroy();
}
