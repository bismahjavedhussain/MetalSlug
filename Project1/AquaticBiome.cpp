#include "AquaticBiome.h"

class Enemy;
class Vehicle;

char* AquaticBiome::biomeName()
{
    static char nm[] = "Aquatic";
    return nm;
}

bool AquaticBiome::canHostEnemy(Enemy* ) { return true; }
bool AquaticBiome::canHostVehicle(Vehicle* ) { return true; }
int  AquaticBiome::ambientSoundId(){ return 2; }
