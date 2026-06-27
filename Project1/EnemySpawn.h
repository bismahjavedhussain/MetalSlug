#pragma once
#include "coordSyst.h"

class Enemy;
class Biome;

struct EnemySpawn
{
    Enemy*    masterCopy;
    coordSyst spawnPosition;
    int       batchSize;
    Biome*    biome;
    EnemySpawn() : masterCopy(nullptr), spawnPosition(), batchSize(0), biome(nullptr) {}
};
