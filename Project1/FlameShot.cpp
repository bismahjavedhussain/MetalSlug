#include "FlameShot.h"
#include "FireStream.h"
#include "Direction.h"
#include "Soldier.h"


FlameShot::FlameShot()
    : ProjectileWeapon(2, 200, 0.1f, 200, coordSyst(15.0f, -5.0f)),
      streamLength(320.0f),
      activeStream(nullptr) {}

FlameShot::~FlameShot()
{
    activeStream = nullptr;
}

Entity* FlameShot::fire(Soldier* owner, coordSyst aim)
{
    if (!hasAmmo() || owner == nullptr) return nullptr;
    consumeAmmo();

    Direction* dir = (aim.x < 0.0f) ? (Direction*)new LeftDirection()
                                    : (Direction*)new RightDirection();
    coordSyst origin = owner->getPosition();
    if (aim.x < 0.0f)
        origin.x -= (8.0f + streamLength);
    else
        origin.x += owner->getWidth() + 8.0f;
    origin.y += owner->getHeight() * 0.5f;

    FireStream* fs = new FireStream(origin, dir, streamLength);
    activeStream   = fs;
    return fs;
}

Projectile* FlameShot::spawnProjectile(Soldier* , coordSyst )
{
    return nullptr;
}

Weapon* FlameShot::clone()
{

    FlameShot* c = new FlameShot(*this);
    c->activeStream = nullptr;
    return c;
}

void FlameShot::stopFire()
{
    if (activeStream != nullptr)
    {
        activeStream->deactivate();
        activeStream = nullptr;
    }
}
