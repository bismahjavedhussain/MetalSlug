#pragma once
#include "DamagableEntity.h"
#include "SpriteAnimator.h"

class PlayerSoldier;
class TileMap;
class DamageSource;
class Vehicle : public DamagableEntity
{
protected:
    PlayerSoldier* pilot;
    bool           isOccupied;
    float          fireRate;
    float          fireCooldown;
    SpriteAnimator m_anim;

public:
    Vehicle(int hp);
    virtual ~Vehicle() = default;

    void           enter(PlayerSoldier* p);
    PlayerSoldier* exit();
    bool           getIsOccupied() const  { return isOccupied; }
    PlayerSoldier* getPilot()             { return pilot;      }

    virtual void   onDestroy();
    virtual Entity* fire(coordSyst aim) = 0;
    virtual void   takeDamage(int amt, DamageSource* src) override;
    virtual void   render(sf::RenderWindow& rw) override;

    SpriteAnimator* getRenderable() override { return &m_anim; }

    virtual void pilotInput(class InputHandler& in, float dt);


    float pilotFireRateMult() const;


    Vehicle* asVehicle() override { return this; }
};
