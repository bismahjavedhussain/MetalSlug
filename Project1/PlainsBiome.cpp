#include "PlainsBiome.h"

class Enemy;
class Vehicle;

char* PlainsBiome::biomeName()
{
    static char nm[] = "Plains";
    return nm;
}

bool PlainsBiome::canHostEnemy(Enemy* )     { return true; }
bool PlainsBiome::canHostVehicle(Vehicle* ) { return true; }
int  PlainsBiome::ambientSoundId() { return 1; }
