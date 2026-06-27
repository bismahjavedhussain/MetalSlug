#pragma once
#include "BallisticProjectile.h"
class ReverseArcMissile : public BallisticProjectile
{
    private:
    float blastRadius;
    public:
    ReverseArcMissile(Entity* shooter, int dmg, coordSyst dir, float spd, float grav, float bRadius);
    virtual void onImpact() override;
};


