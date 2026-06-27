#pragma once
#include "Biome.h"

class AquaticBiome : public Biome
{
    int seaLevel;
public:
    AquaticBiome(int minA = 0, int maxA = 0, int sea = 0): Biome(minA, maxA), seaLevel(sea) {}
    char* biomeName()  override;
    bool  canHostEnemy(Enemy* e) override;
    bool  canHostVehicle(Vehicle* v) override;
    int   ambientSoundId() override;

    int getSeaLevel() const { return seaLevel; }
};
