#include "Soldier.h"
#include "TransformationState.h"
#include "Direction.h"

Soldier::Soldier(int hp)
    : DamagableEntity(hp), currentTransformState(nullptr),
      facing(new RightDirection()), baseSpeed(280.0f), baseFireRate(4.0f),
      attackDamage(3), aimAngle(0.0f),



      equippedWeapon(nullptr) {}
Soldier::Soldier(const Soldier& other)
    : DamagableEntity(other),
      currentTransformState(nullptr),
      facing(other.facing != nullptr ? other.facing->clone() : new RightDirection()),
      baseSpeed(other.baseSpeed),
      baseFireRate(other.baseFireRate),
      attackDamage(other.attackDamage),
      aimAngle(other.aimAngle),
      equippedWeapon(other.equippedWeapon) {}

Soldier& Soldier::operator=(const Soldier& other)
{
    if (this == &other) return *this;
    DamagableEntity::operator=(other);

    if (currentTransformState != nullptr) { delete currentTransformState; currentTransformState = nullptr; }
    if (facing                != nullptr) { delete facing;                facing                = nullptr; }

    facing = (other.facing != nullptr) ? other.facing->clone() : new RightDirection();
    baseSpeed       = other.baseSpeed;
    baseFireRate    = other.baseFireRate;
    attackDamage    = other.attackDamage;
    aimAngle        = other.aimAngle;
    equippedWeapon  = other.equippedWeapon;
    return *this;
}

Soldier::~Soldier()
{
    if (currentTransformState != nullptr)
    {
        delete currentTransformState;
        currentTransformState = nullptr;
    }
    if (facing != nullptr)
    {
        delete facing;
        facing = nullptr;
    }
}

void Soldier::changeState(TransformationState* s)
{
    if (currentTransformState != nullptr)
    {
        currentTransformState->exit(this);
        delete currentTransformState;
    }
    currentTransformState = s;
    if (currentTransformState != nullptr)
        currentTransformState->enter(this);
}

void Soldier::setFacing(Direction* d)
{
    if (facing != nullptr) delete facing;
    facing = d;
}

void Soldier::move(float )        {  }
void Soldier::attack()                  {  }
void Soldier::jump()
{
    if (isOnGround)
    {
        velocity.y = -680.0f;
        isOnGround = false;
    }
}
void Soldier::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}
