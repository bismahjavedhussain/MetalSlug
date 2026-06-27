#include "BallisticProjectile.h"
#include "TileMap.h"
#include "Tile.h"

BallisticProjectile::BallisticProjectile(Entity* shooter, int dmg, coordSyst dir, float spd, float grav)
    : Projectile(shooter, dmg, dir, spd), initialSpeed(spd), gravity(grav)
{
    if (direction.x >= -1.0f && direction.x <= 1.0f &&
        direction.y >= -1.0f && direction.y <= 1.0f)
    {
        velocity.x = direction.x * speed;
        velocity.y = direction.y * speed;
    }
}

void BallisticProjectile::update(TileMap& tm, float dt)
{
    if (!isAlive) return;
    
    velocity.y += gravity * dt;
    if (velocity.y > 800.0f) velocity.y = 800.0f;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

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
