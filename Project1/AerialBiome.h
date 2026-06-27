#pragma once
#include "Biome.h"

class AerialBiome : public Biome
{
public:
    AerialBiome(int minA = 0, int maxA = 0) : Biome(minA, maxA) {}
    char* biomeName() override;
    bool  canHostEnemy(Enemy* e) override;
    bool  canHostVehicle(Vehicle* v) override;
    int   ambientSoundId()  override;
};
