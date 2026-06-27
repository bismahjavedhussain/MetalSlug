#include "ShieldedSoldier.h"
#include "TileMap.h"
#include "Tile.h"
#include "DamageSource.h"
#include "EntityAnims.h"
#include "Bullet.h"
#include <iostream>

ShieldedSoldier::ShieldedSoldier(TextureManager& tm, float spawnX, float spawnY, int batchId)
    : Infantry(75, 5, batchId),
      walkSpeed(35.0f),
      shootCooldown(2.5f),
      facingDir(-1)
{
    setupShieldedAnims(m_anim, tm);
    m_tex = &tm;
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 24.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 32.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void ShieldedSoldier::update(TileMap& tm, float dt)
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

    int ts  = tm.getTileSize();
    int gx  = (int)((position.x + width * 0.5f) / ts);
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

    shootCooldown -= dt;
    if (shootCooldown <= 0.0f)
    {
        attack();
        shootCooldown = 2.5f;
    }

    if (shootCooldown < 2.0f && shootCooldown > 1.7f) m_anim.play("shoot");
    else                                              m_anim.play("walk");

    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}




void ShieldedSoldier::attack()
{
    if (!getCanFire()) return;
    if (pendingProjectile != nullptr) return;

    coordSyst aim;
    aim.x = (float)facingDir;
    aim.y = 0.0f;
    coordSyst origin;
    origin.x = position.x + width  * 0.5f;
    origin.y = position.y + height * 0.40f;

    Bullet* b = new Bullet(this, 3, aim, 520.0f, 900.0f);
    b->setPosition(origin.x, origin.y);
    pendingProjectile = b;
}





bool ShieldedSoldier::blockAttack(coordSyst bulletDir)
{
    if (facingDir == 0) return false;

    bool fromFront = (bulletDir.x > 0.0f && facingDir < 0) ||
                     (bulletDir.x < 0.0f && facingDir > 0);
    return fromFront;
}




void ShieldedSoldier::takeDamage(int amt, DamageSource* src)
{
    if (!isAlive) return;
    Enemy::takeDamage(amt, src);
}












bool ShieldedSoldier::blocksProjectile(coordSyst incomingDir, bool isExplosive)
{
    bool blocked = false;
    const char* reason = "FRONT-block";
    if (isExplosive)
    {
        reason = "explosive-pass";
        blocked = false;
    }
    else if (incomingDir.y > 0.5f)
    {
        reason = "above-pass";
        blocked = false;
    }
    else
    {
        bool fromFront = (incomingDir.x > 0.0f && facingDir < 0) ||
                         (incomingDir.x < 0.0f && facingDir > 0);
        blocked = fromFront;
        if (!fromFront) reason = "behind-pass";
    }















    return blocked;
}

Enemy* ShieldedSoldier::clone() { return new ShieldedSoldier(*this); }
