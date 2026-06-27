#include "Paratrooper.h"
#include "ParatrooperKind.h"
#include "TileMap.h"
#include "Tile.h"
#include "EntityAnims.h"

Paratrooper::Paratrooper(TextureManager& tm, float spawnX, float spawnTopY,
                         ParatrooperKind* k, int batchId)
    : Infantry((k != nullptr ? k->scoreBase() : 50) + 25, 2, batchId),
      hasLanded(false), isParachuting(true),
      kind(k), descendSpeed(60.0f), facingDir(-1),
      landedSpawn(nullptr), tex(&tm)
{
    setupParatrooperAnims(m_anim, tm);
    m_tex = &tm;
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 24.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 32.0f;
    position.x = spawnX;
    position.y = spawnTopY;
}

Paratrooper::~Paratrooper()
{
    if (landedSpawn != nullptr) { delete landedSpawn; landedSpawn = nullptr; }
    if (kind        != nullptr) { delete kind;        kind        = nullptr; }
}

void Paratrooper::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("die");
        m_anim.update(dt);
        return;
    }

    if (isParachuting)
    {

        position.y += descendSpeed * dt;

        int ts = tm.getTileSize();
        int gx = (int)((position.x + width * 0.5f) / ts);
        int feR = (int)((position.y + height) / ts);
        Tile* below = tm.getTile(gx, feR);
        if (below != nullptr && below->isSolid())
        {
            position.y = (float)(feR * ts) - height;
            onLand();
        }
    }

    m_anim.play("walk");
    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

void Paratrooper::attack() {  }

void Paratrooper::onDeath()
{
    Enemy::onDeath();
    isParachuting = false;
}

void Paratrooper::onLand()
{
    if (hasLanded) return;
    hasLanded = true;
    isParachuting = false;

    if (tex == nullptr || kind == nullptr)
    {
        isAlive = false;
        return;
    }

    landedSpawn = kind->spawnLanded(*tex, position.x, position.y, batchId);
    isAlive = false;
}

Infantry* Paratrooper::takeLandedSpawn()
{
    Infantry* s = landedSpawn;
    landedSpawn = nullptr;
    return s;
}

Entity* Paratrooper::takePendingSpawn()
{
    if (hasLanded && landedSpawn != nullptr)
    {
        Infantry* s = landedSpawn;
        landedSpawn = nullptr;
        return s;
    }
    return Enemy::takePendingSpawn();
}

Enemy* Paratrooper::clone()
{
    ParatrooperKind* kClone = (kind != nullptr ? kind->clone() : nullptr);
    Paratrooper* p = new Paratrooper(*tex, position.x, position.y, kClone, batchId);
    return p;
}
