#include "Martian.h"
#include "TileMap.h"
#include "Tile.h"
#include "EntityAnims.h"
#include "EnergyBeam.h"
#include "Bullet.h"

Martian::Martian(TextureManager& tm, float spawnX, float spawnY)
    : Alien(200, 3),
      phase(1), hasPod(true),
      fireCooldown(2.0f), facingDir(-1)
{
    setupMartianAnims(m_anim, tm);
    m_tex = &tm;
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 32.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 32.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void Martian::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("explode");
        m_anim.update(dt);
        return;
    }

    if (phase == 1)
    {

        velocity.x = 30.0f * (float)facingDir;
        position.x += velocity.x * dt;

        if (position.x < 0.0f) { facingDir = +1; position.x = 0.0f; }
        float maxX = (float)((tm.getWidth() - 1) * tm.getTileSize()) - width;
        if (position.x > maxX) { facingDir = -1; position.x = maxX; }

        fireCooldown -= dt;
        if (fireCooldown <= 0.0f)
        {
            attack();
            fireCooldown = 2.0f;
        }

        m_anim.play("idle");
    }
    else
    {

        velocity.x = 25.0f * (float)facingDir;

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

        m_anim.play("loop");
    }

    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}


void Martian::attack()
{
    if (!getCanFire()) return;
    if (pendingProjectile != nullptr) return;

    coordSyst origin;
    origin.x = position.x + width  * 0.5f;
    origin.y = position.y + height * 0.50f;

    if (phase == 1)
    {
        coordSyst aim;
        aim.x = 0.0f;
        aim.y = 1.0f;
        EnergyBeam* beam = new EnergyBeam(this, 4, aim,
                                          700.0f, 900.0f,
                                          1.5f, false);
        beam->setPosition(origin.x, origin.y);
        pendingProjectile = beam;
    }
    else
    {
        coordSyst aim;
        aim.x = (float)facingDir;
        aim.y = 0.0f;
        Bullet* b = new Bullet(this, 3, aim, 500.0f, 900.0f);
        b->setPosition(origin.x, origin.y);
        pendingProjectile = b;
    }
}

void Martian::onDeath()
{
    if (phase == 1)
    {

        transitionToPhase2();
    }
    else
    {
        Enemy::onDeath();
    }
}

void Martian::transitionToPhase2()
{
    phase  = 2;
    hasPod = false;
    healthPoints = maxHealthPoints;
    isAlive = true;
}

Enemy* Martian::clone() { return new Martian(*this); }
