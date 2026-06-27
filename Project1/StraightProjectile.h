#pragma once
#include "Projectile.h"

class TileMap;
class StraightProjectile : public Projectile
{
protected:
    float maxRange;
    float distCovered;

public:
    StraightProjectile(Entity* shooter, int dmg, coordSyst dir, float spd, float range);
    virtual ~StraightProjectile() = default;
    virtual void update(TileMap& tm, float dt) override;
};
