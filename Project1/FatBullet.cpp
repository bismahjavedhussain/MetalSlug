#include "FatBullet.h"

FatBullet::FatBullet(Entity* shooter, int dmg, coordSyst dir, float spd, float range)
    : Bullet(shooter, dmg, dir, spd, range)
{
    width  = 24.0f;
    height = 24.0f;
}
