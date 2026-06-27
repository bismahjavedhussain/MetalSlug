#pragma once
#include "Entity.h"

class TileMap;






class Projectile : public Entity
{
protected:
    Entity*   owner;
    int       damage;
    coordSyst direction;
    float     speed;

public:
    Projectile(Entity* shooter, int dmg, coordSyst dir, float spd);
    virtual ~Projectile() = default;
    virtual void update(TileMap& tm, float deltaTime) override = 0;
    virtual void render(sf::RenderWindow& rw)                  override;

    virtual void onImpact();
    virtual bool isExplosiveImpact() const { return false; }

    virtual bool isMeleeImpact()     const { return false; }
    virtual bool isPiercingShield()  const { return false; }


    bool isOwnerHostile()    const { return ownerIsHostile; }

    int getDamage()    const { return damage;    }
    Entity* getOwner() const { return owner;     }

    bool getAoePending() const  { return aoePending; }
    void setAoePending(bool b)  { aoePending = b;    }


    Projectile* asProjectile() override { return this; }

protected:
    bool aoePending;
    bool ownerIsHostile = false;
};
