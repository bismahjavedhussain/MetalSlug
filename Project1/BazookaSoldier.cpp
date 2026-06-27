#include "BazookaSoldier.h"
#include "TileMap.h"
#include "Tile.h"
#include "EntityAnims.h"
#include "BazookaShell.h"

BazookaSoldier::BazookaSoldier(TextureManager& tm, float spawnX, float spawnY, int batchId)
    : Infantry(100, 2, batchId),
      walkSpeed(20.0f),
      fireCooldown(3.5f),
      facingDir(-1)
{
    setupBazookaAnims(m_anim, tm);
    m_tex = &tm;
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 24.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 32.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void BazookaSoldier::update(TileMap& tm, float dt)
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

    fireCooldown -= dt;
    if (fireCooldown <= 0.0f)
    {
        attack();
        fireCooldown = 3.5f;
    }

    if (fireCooldown < 3.0f && fireCooldown > 2.6f) m_anim.play("fire");
    else                                            m_anim.play("walk");

    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}





void BazookaSoldier::attack()
{
    if (!getCanFire()) return;
    if (pendingProjectile != nullptr) return;

    coordSyst aim;
    aim.x = (float)facingDir * 0.6f;
    aim.y = -0.8f;
    coordSyst origin;
    origin.x = position.x + width  * 0.5f;
    origin.y = position.y + height * 0.30f;

    BazookaShell* sh = new BazookaShell(this, 5, aim,
                                        360.0f, 1100.0f, 96.0f);
    sh->setPosition(origin.x, origin.y);
    pendingProjectile = sh;
}

Enemy* BazookaSoldier::clone() { return new BazookaSoldier(*this); }
