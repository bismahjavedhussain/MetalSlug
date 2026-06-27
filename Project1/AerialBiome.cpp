#include "AerialBiome.h"

class Enemy;
class Vehicle;

char* AerialBiome::biomeName()
{
    static char nm[] = "Aerial";
    return nm;                   
}

bool AerialBiome::canHostEnemy(Enemy* ) { return true; }  
bool AerialBiome::canHostVehicle(Vehicle* ) { return true; }
int  AerialBiome::ambientSoundId()  { return 0; }
