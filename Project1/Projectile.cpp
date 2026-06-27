#include "Projectile.h"

Projectile::Projectile(Entity* shooter, int dmg, coordSyst dir, float spd)
    : Entity(), owner(shooter), damage(dmg), direction(dir), speed(spd),
      aoePending(false)
{
    width  = 24.0f;
    height = 16.0f;
    isAlive = true;

    ownerIsHostile = false;
    if (shooter != nullptr)
    {
        if      (shooter->asEnemy()       != nullptr) ownerIsHostile = true;
        else if (shooter->asM15ABradley() != nullptr) ownerIsHostile = true;
        else if (shooter->asEnemySub()    != nullptr) ownerIsHostile = true;
        else if (shooter->asFlyingTara()  != nullptr) ownerIsHostile = true;
    }
}

void Projectile::onImpact()
{
    isAlive = false;
}

void Projectile::render(sf::RenderWindow& ) {}
