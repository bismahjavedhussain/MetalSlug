#include "Grenadier.h"
#include "TileMap.h"
#include "Tile.h"
#include "EntityAnims.h"
#include "GrenadeProjectile.h"

Grenadier::Grenadier(TextureManager& tm, float spawnX, float spawnY, int batchId)
    : Infantry(100, 2, batchId),
      walkSpeed(35.0f),
      lobCooldown(2.5f),
      facingDir(-1)
{
    setupGrenadierAnims(m_anim, tm);
    m_tex = &tm;
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 24.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 32.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void Grenadier::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("die");
        m_anim.update(dt);
        return;
    }

    velocity.x = walkSpeed * (float)facingDir;

    const float GRAVITY = 1200.0f;
    velocity.y += GRAVITY * dt;
    if (velocity.y > 1200.0f) velocity.y = 1200.0f;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    int ts = tm.getTileSize();
    int gx = (int)((position.x + width * 0.5f) / ts);
    int feR = (int)((position.y + height) / ts);
    Tile* below = tm.getTile(gx, feR);
    if (below != nullptr && below->isSolid())
    {
        position.y = (float)(feR * ts) - height;
        velocity.y = 0.0f;
        isOnGround = true;
    }
    else
    {
        isOnGround = false;
    }

    if (position.x < 0.0f) { facingDir = +1; position.x = 0.0f; }
    float maxX = (float)((tm.getWidth() - 1) * ts) - width;
    if (position.x > maxX) { facingDir = -1; position.x = maxX; }

    lobCooldown -= dt;
    if (lobCooldown <= 0.0f)
    {
        attack();
        lobCooldown = 2.5f;
    }

    if (lobCooldown < 2.0f && lobCooldown > 1.7f) m_anim.play("fire");
    else                                          m_anim.play("walk");

    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

void Grenadier::attack()
{
    if (!getCanFire()) return;
    if (pendingProjectile != nullptr) return;

    coordSyst aim;
    aim.x = (float)facingDir * 0.7f;
    aim.y = -0.7f;
    coordSyst origin;
    origin.x = position.x + width  * 0.5f;
    origin.y = position.y + height * 0.30f;

    GrenadeProjectile* g = new GrenadeProjectile(this, 5, aim,
                                                 280.0f, 1100.0f, 96.0f);
    g->setPosition(origin.x, origin.y);
    pendingProjectile = g;
}

Enemy* Grenadier::clone() { return new Grenadier(*this); }
