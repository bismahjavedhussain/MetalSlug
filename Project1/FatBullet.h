#pragma once
#include "Bullet.h"


class FatBullet : public Bullet
{
public:
    FatBullet(Entity* shooter, int dmg, coordSyst dir, float spd, float range);
};
