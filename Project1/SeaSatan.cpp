#include "SeaSatan.h"
#include "TileMap.h"
#include "DamageState.h"
#include "Zombie.h"
#include "EntityAnims.h"

SeaSatan::SeaSatan(TextureManager& tm, float spawnX, float spawnY)
    : Boss(500, 30),
      rocketCount(0),
      cruiseSpeed(60.0f),
      facingDir(-1),
      rocketCooldown(3.0f),
      hmgBurstTimer(1.2f),
      hmgRestTimer(0.0f),
      retreatTimer(0.0f),
      explodeStage(0),
      explodeTimer(0.0f)
{
    setupSeaSatanAnims(m_anim, tm);
    m_tex = &tm;
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 192.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 96.0f;
    position.x = spawnX;
    position.y = spawnY + 96.0f - height;
    minionPrototype = new Zombie(tm, spawnX, spawnY);
}

void SeaSatan::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        explodeTimer -= dt;
        if (explodeStage == 0 && explodeTimer <= 0.0f)
        {
            explodeStage = 1;
            explodeTimer = 0.65f;
            m_anim.play("damaged", true);
        }
        m_anim.update(dt);
        return;
    }

    if (hasRetreated)
    {
        retreatTimer -= dt;
        velocity.x = cruiseSpeed * 1.6f * (float)facingDir;
        velocity.y = +60.0f;
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        m_anim.play("retreat");
        m_anim.setFlipX(facingDir < 0);
        m_anim.setPosition(position.x, position.y);
        m_anim.update(dt);
        if (retreatTimer <= 0.0f) isAlive = false;
        return;
    }
    if (hasChaseTarget)
    {
        float playerCenterX = chaseTargetX;
        float bossCenterX   = position.x + width * 0.5f;
        facingDir = (playerCenterX > bossCenterX) ? +1 : -1;
    }


    velocity.x = cruiseSpeed * (float)facingDir;
    position.x += velocity.x * dt;


    if (position.x < 0.0f) { facingDir = +1; position.x = 0.0f; }
    float maxX = (float)((tm.getWidth() - 1) * tm.getTileSize()) - width;
    if (position.x > maxX) { facingDir = -1; position.x = maxX; }


    if (hmgBurstTimer > 0.0f)
    {
        hmgBurstTimer -= dt;

        currentStrategy     = &hmgStrat;
        pendingShotOrigin.x = position.x + (facingDir > 0 ? width : 0.0f);
        pendingShotOrigin.y = position.y + height * 0.5f;
        pendingShotAim.x    = (float)facingDir;
        pendingShotAim.y    = 0.0f;
        hasPendingShot      = true;
        if (hmgBurstTimer <= 0.0f) hmgRestTimer = 0.8f;
    }
    else
    {
        hmgRestTimer -= dt;
        if (hmgRestTimer <= 0.0f) hmgBurstTimer = 1.2f;
    }


    rocketCooldown -= dt;
    if (rocketCooldown <= 0.0f)
    {
        attack();
        rocketCooldown = 3.0f;
        ++rocketCount;
    }

    if (checkRetreat())
    {
        retreatTimer = 4.0f;
        return;
    }

    static float minionTimer = 12.0f;
    minionTimer -= dt;
    if (minionTimer <= 0.0f)
    {
        wantsMinionBatch = true;
        minionTimer      = 12.0f;
    }

    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);



    m_anim.play("idle");

    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

void SeaSatan::attack()
{
    currentStrategy     = &rocketStrat;
    pendingShotOrigin.x = position.x + width * 0.5f;
    pendingShotOrigin.y = position.y;
    pendingShotAim.x    = (float)facingDir * 0.4f;
    pendingShotAim.y    = -0.85f;
    hasPendingShot      = true;
}



