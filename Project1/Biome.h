#pragma once

class Enemy;
class Vehicle;


class Biome
{
protected:
    int minAltitude;
    int maxAltitude;

public:
    Biome(int minA = 0, int maxA = 0) : minAltitude(minA), maxAltitude(maxA) {}
    virtual ~Biome() = default;
    virtual char* biomeName() = 0;
    virtual bool  canHostEnemy(Enemy* e) = 0;
    virtual bool  canHostVehicle(Vehicle* v) = 0;
    virtual int ambientSoundId() = 0;

    int getMinAltitude() const { return minAltitude; }
    int getMaxAltitude() const { return maxAltitude; }
    bool containsRow(int gridY) const { return gridY >= minAltitude && gridY <= maxAltitude; }  
};
