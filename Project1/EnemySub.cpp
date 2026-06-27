#include "EnemySub.h"
#include "TileMap.h"
#include "Tile.h"
#include "DamageState.h"
#include "EntityAnims.h"
#include "Rocket.h"

EnemySub::EnemySub(TextureManager& tm, float spawnX, float spawnY)
    : EnemyVehicle(7, true, 250),
      horizSpeed(70.0f),
      facingDir(-1),
      fireCooldown(2.5f),
      hasPendingRocket(false)
{
    setupSubAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 96.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 32.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void EnemySub::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("explode");
        m_anim.update(dt);
        return;
    }


    velocity.x = horizSpeed * (float)facingDir;
    position.x += velocity.x * dt;

    if (position.x < 0.0f) { facingDir = +1; position.x = 0.0f; }
    float maxX = (float)((tm.getWidth() - 1) * tm.getTileSize()) - width;
    if (position.x > maxX) { facingDir = -1; position.x = maxX; }

    fireCooldown -= dt;
    if (fireCooldown <= 0.0f)
    {
        attack();
        fireCooldown = 2.5f;
    }

    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);

    m_anim.play("move");
    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}


void EnemySub::attack()
{
    if (!getCanFire()) return;
    pendingRocketOrigin.x = position.x + width * 0.5f;
    pendingRocketOrigin.y = position.y;
    pendingRocketAim.x    = (float)facingDir * 0.5f;
    pendingRocketAim.y    = -0.85f;
    hasPendingRocket = true;
}

bool EnemySub::takePendingRocket(coordSyst& outOrigin, coordSyst& outAim)
{
    if (!hasPendingRocket) return false;
    outOrigin = pendingRocketOrigin;
    outAim    = pendingRocketAim;
    hasPendingRocket = false;
    return true;
}

Entity* EnemySub::takePendingSpawn()
{
    if (!hasPendingRocket) return nullptr;
    hasPendingRocket = false;
    Rocket* r = new Rocket(this, 5, pendingRocketAim,
                           420.0f, 1500.0f, 96.0f);
    r->setPosition(pendingRocketOrigin.x, pendingRocketOrigin.y);
    return r;
}

void EnemySub::onDestroy()
{
    EnemyVehicle::onDestroy();
}

Entity* EnemySub::clone()
{
    return new EnemySub(*this);
}
