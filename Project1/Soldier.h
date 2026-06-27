#pragma once
#include "DamagableEntity.h"
#include "SpriteAnimator.h"

class Direction;
class TransformationState;
class Weapon;
class TileMap;
class Inventory;




class Soldier : public DamagableEntity
{
protected:
    TransformationState* currentTransformState;
    Direction* facing;
    float baseSpeed;
    float baseFireRate;
    int attackDamage;
    float aimAngle;
    SpriteAnimator m_anim;
    Weapon*  equippedWeapon;

public:
    Soldier(int hp);
    Soldier(const Soldier& other);
    Soldier& operator=(const Soldier& other);
    virtual ~Soldier();

    void changeState(TransformationState* s);

    virtual void move(float dt);
    virtual void attack();
    virtual void jump();

    void  setAimAngle(float deg) { aimAngle = deg; }
    float getAimAngle() const    { return aimAngle; }
    Direction* getFacing()       { return facing; }
    void  setFacing(Direction* d);
    SpriteAnimator& getAnimator() { return m_anim; }



    float getBaseSpeed() const   { return baseSpeed; }
    void  scaleBaseSpeed(float k) { baseSpeed *= k; }
    virtual Inventory* getInventoryPtr() { return nullptr; }
    virtual float getSpeedMult() const { return 1.0f; }
    virtual void  setSpeedMult(float m) { (void)m; }
    virtual bool meleePiercesShield() const { return false; }

    Weapon* getEquippedWeapon() const  { return equippedWeapon; }
    void    setEquippedWeapon(Weapon* w) { equippedWeapon = w; }

    void render(sf::RenderWindow& rw) override;
    SpriteAnimator* getRenderable() override { return &m_anim; }
};
