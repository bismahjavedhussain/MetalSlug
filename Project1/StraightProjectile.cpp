#include "StraightProjectile.h"
#include "TileMap.h"
#include "Tile.h"

StraightProjectile::StraightProjectile(Entity* shooter, int dmg, coordSyst dir, float spd, float range)
    : Projectile(shooter, dmg, dir, spd), maxRange(range), distCovered(0.0f)
{

    if (direction.x >= -1.0f && direction.x <= 1.0f &&
        direction.y >= -1.0f && direction.y <= 1.0f)
    {
        velocity.x = direction.x * speed;
        velocity.y = direction.y * speed;
    }
}

void StraightProjectile::update(TileMap& tm, float dt)
{
    if (!isAlive) return;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    float stepSize = speed * dt;
    distCovered += stepSize;
    if (distCovered >= maxRange)
    {
        isAlive = false;
        return;
    }

    int ts = tm.getTileSize();
    int gx = (int)(position.x / ts);
    int gy = (int)(position.y / ts);
    Tile* hit = tm.getTile(gx, gy);
    if (hit != nullptr && hit->isSolid())
    {
        if (isExplosiveImpact()) aoePending = true;
        onImpact();
    }
}
