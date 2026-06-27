#pragma once

#include <SFML/Graphics.hpp>
#include "coordSyst.h"
#include "Box.h"

class TileMap;
class SpriteAnimator;




class DamagableEntity;
class Projectile;
class Enemy;
class AreaHazard;
class Collectible;
class Vehicle;
class Paratrooper;
class FireBombProjectile;
class FlyingTara;
class M15ABradley;
class EnemySub;
class FusionCompanion;
class Boss;
class PlayerSoldier;



class Entity
{
protected:
    coordSyst position;
    coordSyst velocity;
    float width;
    float height;
    bool isAlive;
    bool isOnGround;
    bool touchesWall;

public:
    Entity();
    virtual ~Entity() = default;

    virtual void update(TileMap& tm, float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    bool checkCollision(Entity& other);
    Box  getHitbox();

    coordSyst getPosition() const { return position; }
    coordSyst getVelocity() const { return velocity; }
    float     getWidth()    const { return width; }
    float     getHeight()   const { return height; }
    bool      getIsAlive()  const { return isAlive; }
    bool      getIsOnGround() const { return isOnGround; }

    void      setPosition(float x, float y) { position.x = x; position.y = y; }
    void      setVelocity(float vx, float vy) { velocity.x = vx; velocity.y = vy; }
    void      kill() { isAlive = false; }

    virtual SpriteAnimator* getRenderable() { return nullptr; }
    virtual Entity* clone();
    virtual Entity* takePendingSpawn() { return nullptr; }
    virtual bool isPlayer() const { return false; }


    virtual DamagableEntity*    asDamagableEntity()    { return nullptr; }
    virtual Projectile*         asProjectile()         { return nullptr; }
    virtual Enemy*              asEnemy()              { return nullptr; }
    virtual AreaHazard*         asAreaHazard()         { return nullptr; }
    virtual Collectible*        asCollectible()        { return nullptr; }
    virtual Vehicle*            asVehicle()            { return nullptr; }
    virtual Paratrooper*        asParatrooper()        { return nullptr; }
    virtual FireBombProjectile* asFireBombProjectile() { return nullptr; }
    virtual FlyingTara*         asFlyingTara()         { return nullptr; }
    virtual M15ABradley*        asM15ABradley()        { return nullptr; }
    virtual EnemySub*           asEnemySub()           { return nullptr; }
    virtual FusionCompanion*    asFusionCompanion()    { return nullptr; }
    virtual Boss*               asBoss()               { return nullptr; }
    virtual PlayerSoldier*      asPlayerSoldier()      { return nullptr; }
};
