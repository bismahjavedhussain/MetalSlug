#include "FiringStrategy.h"

#include "Rocket.h"
#include "Bullet.h"
#include "FireBombProjectile.h"
#include "FireStream.h"
#include "Direction.h"

Entity* RocketFiringStrategy::produce(Entity* shooter, coordSyst , coordSyst aim)
{
    const int   DMG    = 5;
    const float SPEED  = 520.0f;
    const float RANGE  = 1500.0f;
    const float BLAST  = 192.0f;
    return new Rocket(shooter, DMG, aim, SPEED, RANGE, BLAST);
}

Entity* HMGFiringStrategy::produce(Entity* shooter, coordSyst , coordSyst aim)
{
    const int   DMG   = 3;
    const float SPEED = 700.0f;
    const float RANGE = 1200.0f;
    return new Bullet(shooter, DMG, aim, SPEED, RANGE);
}


Entity* FireBombFiringStrategy::produce(Entity* shooter, coordSyst , coordSyst aim)
{
    const int   DMG          = 5;
    const float SPEED        = 420.0f;
    const float GRAVITY      = 600.0f;
    const float BLAST        = 192.0f;
    const float POOL_RADIUS  = 192.0f;
    const float POOL_DUR     = 10.0f;
    return new FireBombProjectile(shooter, DMG, aim, SPEED, GRAVITY, BLAST,
                                  POOL_RADIUS, POOL_DUR);
}
Entity* FlameStreamFiringStrategy::produce(Entity* , coordSyst origin, coordSyst aim)
{
    const float LENGTH = 320.0f;
    Direction* dir = (aim.x < 0.0f) ? (Direction*)new LeftDirection()
                                    : (Direction*)new RightDirection();
    return new FireStream(origin, dir, LENGTH);
}
