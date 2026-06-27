#include "Enemy.h"
#include "EnemyAIState.h"
#include "TileMap.h"
#include "Tile.h"
#include "DamageState.h"
#include "PlayerSoldier.h"
#include "ContactDamage.h"
#include "Turkey.h"
#include "Fruit.h"
#include "Collectible.h"
#include "Weapon.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(int scoreVal, int hp, bool grudgeful)
    : DamagableEntity(hp), scoreValue(scoreVal), isGrudgeful(grudgeful),
      currentAIState(nullptr), m_inReserve(false), m_tex(nullptr),
      weapon(nullptr), pendingDrop(nullptr), pendingProjectile(nullptr)
{
    width  = 24.0f;
    height = 32.0f;
}
Enemy::Enemy(const Enemy& other)
    : DamagableEntity(other),
      scoreValue(other.scoreValue),
      isGrudgeful(other.isGrudgeful),
      currentAIState(nullptr),
      m_inReserve(other.m_inReserve),
      m_tex(other.m_tex),
      weapon(nullptr),
      pendingDrop(nullptr),
      pendingProjectile(nullptr)
{
}
Enemy& Enemy::operator=(const Enemy& other)
{
    if (this == &other) return *this;
    DamagableEntity::operator=(other);
    scoreValue  = other.scoreValue;
    isGrudgeful = other.isGrudgeful;
    if (currentAIState    != nullptr) { 
        delete currentAIState;   
         currentAIState    = nullptr;
         }
    if (weapon            != nullptr) { 
        delete weapon;       
             weapon            = nullptr;
             }
    if (pendingDrop       != nullptr) {
         delete pendingDrop;     
           pendingDrop       = nullptr; 
        }
    if (pendingProjectile != nullptr) { 
        delete pendingProjectile; 
        pendingProjectile = nullptr;
     }
    m_inReserve = other.m_inReserve;
    m_tex = other.m_tex;
    return *this;
}

Enemy::~Enemy()
{
    if (currentAIState != nullptr)
    {
        delete currentAIState;
        currentAIState = nullptr;
    }
    if (pendingDrop != nullptr)
    {
        delete pendingDrop;
        pendingDrop = nullptr;
    }
    if (pendingProjectile != nullptr)
    {
        delete pendingProjectile;
        pendingProjectile = nullptr;
    }
    if (weapon != nullptr)
    {
        delete weapon;
        weapon = nullptr;
    }
}
void Enemy::update(TileMap& tm, float dt)
{
    if (!isAlive) return;

    if (currentAIState != nullptr)
        currentAIState->update(this, tm, dt);


    const float GRAVITY = 800.0f;
    if (!isOnGround)
        velocity.y += GRAVITY * dt;
    if (velocity.y > 1200.0f) velocity.y = 1200.0f;


    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    int ts = tm.getTileSize();
    int gx = (int)((position.x + width * 0.5f) / ts);
    int footRow = (int)((position.y + height) / ts);
    Tile* below = tm.getTile(gx, footRow);
    if (below != nullptr && below->isSolid())
    {
        position.y = (float)(footRow * ts) - height;
        velocity.y = 0.0f;
        isOnGround = true;
    }
    else
    {
        isOnGround = false;
    }


    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);


    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

void Enemy::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}
void Enemy::die()
{
    if (!isAlive) return;
    onDeath();
}

void Enemy::onDeath()
{
    isAlive = false;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    rollDeathDrop();
}

void Enemy::rollDeathDrop()
{
    static unsigned seed = 0xA17EFEED;
    seed = seed * 1664525u + 1013904223u;
    unsigned r = seed % 100u;
    if (r >= 25) return;
    if (m_tex == nullptr) return;

    coordSyst at = position;


    if (r < 13) pendingDrop = new Turkey(*m_tex, at.x, at.y);
    else        pendingDrop = new Fruit (*m_tex, at.x, at.y);
}

Collectible* Enemy::takePendingDrop()
{
    Collectible* c = pendingDrop;
    pendingDrop = nullptr;
    return c;
}

Entity* Enemy::takePendingProjectile()
{
    Entity* p = pendingProjectile;
    pendingProjectile = nullptr;
    return p;
}
Entity* Enemy::takePendingSpawn()
{
    if (pendingProjectile != nullptr)
    {
        Entity* p = pendingProjectile;
        pendingProjectile = nullptr;
        return p;
    }
    if (pendingDrop != nullptr)
    {
        Collectible* d = pendingDrop;
        pendingDrop = nullptr;
        return d;
    }
    return nullptr;
}

void Enemy::pathToPlayer(TileMap& , coordSyst target)
{
    const float SPEED = 80.0f;
    float dx = target.x - (position.x + width * 0.5f);
    float dy = target.y - (position.y + height * 0.5f);
    float dist = std::sqrt(dx * dx + dy * dy);
    if (dist > 0.5f)
    {
        velocity.x = (dx / dist) * SPEED;
        if (dy < -48.0f && isOnGround)
            velocity.y = -400.0f;
    }
    else
    {
        velocity.x = 0.0f;
    }
}
void Enemy::onPlayerContact(PlayerSoldier* p)
{
    if (p == nullptr) return;
    ContactDamage cd(this);
    p->takeDamage(cd.amount(), &cd);
}

void Enemy::changeAIState(EnemyAIState* newState)
{
    if (currentAIState != nullptr)
    {
        currentAIState->exit(this);
        delete currentAIState;
    }
    currentAIState = newState;
    if (currentAIState != nullptr)
        currentAIState->enter(this);
}
