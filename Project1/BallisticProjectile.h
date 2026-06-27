#pragma once
#include "Projectile.h"

class TileMap;
class BallisticProjectile : public Projectile
{
protected:
    float initialSpeed;
    float gravity;

public:
    BallisticProjectile(Entity* shooter, int dmg, coordSyst dir, float spd, float grav);
    virtual ~BallisticProjectile() = default;

    virtual void update(TileMap& tm, float dt) override;
};
