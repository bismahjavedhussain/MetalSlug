#include "RebelSoldier.h"
#include "EntityAnims.h"
#include "TileMap.h"
#include "Tile.h"
#include "Bullet.h"



RebelSoldier::RebelSoldier(TextureManager& tm, float spawnX, float spawnY, int batchId)
    : Infantry(50, 2, batchId),
      m_walkSpeed(40.0f),
      m_shootCooldown(2.0f),
      m_shootDuration(0.0f),
      m_facingDir(-1)
{
    setupRebelAnims(m_anim, tm);
    m_tex = &tm;

    width  = 36.0f;
    height = 90.0f;

    position.x = spawnX;
    position.y = spawnY;
    velocity.x = m_walkSpeed * (float)m_facingDir;
}

void RebelSoldier::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("die");
        m_anim.update(dt);
        return;
    }

    if (m_shootDuration > 0.0f)
    {
        m_shootDuration -= dt;
        velocity.x = 0.0f;
    }
    else
    {
        velocity.x = m_walkSpeed * (float)m_facingDir;
    }

    m_shootCooldown -= dt;
    if (m_shootCooldown <= 0.0f)
    {
        m_shootDuration = 0.4f;
        m_shootCooldown = 2.5f;
        attack();
    }


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


    if (position.x < 0.0f)              { m_facingDir = +1; position.x = 0.0f; }
    float maxX = (float)((tm.getWidth() - 1) * ts) - width;
    if (position.x > maxX)              { m_facingDir = -1; position.x = maxX; }


    if (m_shootDuration > 0.0f)         m_anim.play("shoot");
    else if (velocity.x != 0.0f)        m_anim.play("walk");
    else                                m_anim.play("idle");

    m_anim.setFlipX(m_facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}


void RebelSoldier::attack()
{
    if (!getCanFire()) return;
    if (pendingProjectile != nullptr) return;

    coordSyst aim;
    aim.x = (float)m_facingDir;
    aim.y = 0.0f;
    coordSyst origin;
    origin.x = position.x + width  * 0.5f;
    origin.y = position.y + height * 0.35f;

    Bullet* b = new Bullet(this, 3, aim, 520.0f, 900.0f);
    b->setPosition(origin.x, origin.y);
    pendingProjectile = b;
}

void RebelSoldier::onPlayerContact(PlayerSoldier* )
{
}

Enemy* RebelSoldier::clone()
{
    return new RebelSoldier(*this);
}
