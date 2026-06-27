#include "DamagableEntity.h"
#include "DamageState.h"
#include "DamageSource.h"
#include "NormalDamageState.h"
#include <iostream>


DamagableEntity::DamagableEntity(int startHealthPoint)
    : Entity(),
      healthPoints(startHealthPoint), maxHealthPoints(startHealthPoint),
      isInvelnerable(false), currentDamageState(nullptr),
      m_canFire(true) {}

DamagableEntity::DamagableEntity(const DamagableEntity& other)
    : Entity(other),
      healthPoints(other.healthPoints),
      maxHealthPoints(other.maxHealthPoints),
      isInvelnerable(other.isInvelnerable),
      currentDamageState(new NormalDamageState()),
      m_canFire(other.m_canFire)
{
    if (currentDamageState != nullptr)
        currentDamageState->enter(this);
}
DamagableEntity& DamagableEntity::operator=(const DamagableEntity& other)
{
    if (this == &other) return *this;
    Entity::operator=(other);
    healthPoints    = other.healthPoints;
    maxHealthPoints = other.maxHealthPoints;
    isInvelnerable  = other.isInvelnerable;
    m_canFire       = other.m_canFire;
    if (currentDamageState != nullptr)
    {
        delete currentDamageState;
        currentDamageState = nullptr;
    }
    currentDamageState = new NormalDamageState();
    currentDamageState->enter(this);
    return *this;
}

void DamagableEntity::takeDamage(int amount, DamageSource* src)
{
    if (isInvelnerable || !isAlive) return;

    healthPoints -= amount;
    advanceDamageState();


    if (healthPoints <= 0)
    {
        healthPoints = 0;
        die();
    }
}

void DamagableEntity::die()
{
    isAlive = false;
}

int DamagableEntity::getHealth() const
{
    return healthPoints;
}

void DamagableEntity::setHealth(int hp)
{
    healthPoints = hp;
    if (healthPoints > maxHealthPoints)
        healthPoints = maxHealthPoints;
}

void DamagableEntity::setMaxHealth(int newMax)
{
    if (newMax < 1) newMax = 1;
    maxHealthPoints = newMax;
    healthPoints    = newMax;
}

DamageState* DamagableEntity::getDamageState()
{
    return currentDamageState;
}

void DamagableEntity::advanceDamageState()
{
    if (currentDamageState == nullptr) return;

    DamageState* nxt = currentDamageState->next();
    if (nxt == nullptr || nxt == currentDamageState) return;

    currentDamageState->exit(this);
    delete currentDamageState;
    currentDamageState = nxt;
    currentDamageState->enter(this);
}

DamagableEntity::~DamagableEntity()
{
    if (currentDamageState != nullptr)
    {
        delete currentDamageState;
        currentDamageState = nullptr;
    }
}
