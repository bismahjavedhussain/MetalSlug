#include "ReverseArcMissile.h"
ReverseArcMissile::ReverseArcMissile(Entity* shooter, int dmg, coordSyst dir, float spd, float grav, float bRadius) : BallisticProjectile(shooter, dmg, dir, spd, grav), blastRadius(bRadius) {}

void ReverseArcMissile::onImpact()
{
    isAlive = false;
}
