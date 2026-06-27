#pragma once
#include "ProjectileWeapon.h"

class FireStream;
class FlameShot : public ProjectileWeapon
{
private:
    float streamLength;
    FireStream* activeStream;

public:
    FlameShot();
    ~FlameShot() override;
    Entity*    fire(Soldier* owner, coordSyst aim) override;
    Projectile* spawnProjectile(Soldier* owner, coordSyst aim) override;
    Weapon*    clone() override;
    const char* getAnimPrefix() const override { return "flame"; }

    void       stopFire();
};
