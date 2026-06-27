#include "MummyWarrior.h"
#include "TileMap.h"
#include "Tile.h"
#include "PlayerSoldier.h"
#include "Soldier.h"
#include "MummyTransformState.h"
#include "DamageSource.h"
#include "EntityAnims.h"

MummyWarrior::MummyWarrior(TextureManager& tm, float spawnX, float spawnY)
    : Undead(150, 5),
      crumbleTimer(0.0f), isCrumbled(false),
      resurrectionDelay(3.0f),
      walkSpeed(20.0f),
      facingDir(-1)
{
    setupMummyAnims(m_anim, tm);
    m_tex = &tm;
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 24.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 32.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void MummyWarrior::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("die");
        m_anim.update(dt);
        return;
    }

    if (isCrumbled)
    {
        crumbleTimer -= dt;
        m_anim.play("crumble");
        m_anim.update(dt);
        m_anim.setPosition(position.x, position.y);
        if (crumbleTimer <= 0.0f) resurrect();
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



    if (position.x < 0.0f) position.x = 0.0f;
    float maxX = (float)((tm.getWidth() - 1) * ts) - width;
    if (position.x > maxX) position.x = maxX;

    m_anim.play("walk");
    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

void MummyWarrior::attack() {  }


void MummyWarrior::onPlayerContact(PlayerSoldier* p)
{
    if (p == nullptr || isCrumbled) return;
    p->changeState(new MummyTransformState());
}


void MummyWarrior::takeDamage(int amount, DamageSource* src)
{
    if (!isAlive || isCrumbled) return;

    if (src != nullptr && src->canKillMummy())
    {

        Enemy::takeDamage(amount, src);
        return;
    }


    isCrumbled       = true;
    crumbleTimer     = resurrectionDelay;
    velocity.x       = 0.0f;
    velocity.y       = 0.0f;
}

void MummyWarrior::resurrect()
{
    isCrumbled   = false;
    healthPoints = maxHealthPoints;
    crumbleTimer = 0.0f;
    m_anim.play("resurrect", true);
}

Enemy* MummyWarrior::clone()
{
    return new MummyWarrior(*this);
}
