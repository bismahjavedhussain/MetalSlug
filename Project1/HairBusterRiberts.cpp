#include "HairBusterRiberts.h"
#include "TileMap.h"
#include "DamageState.h"
#include "Paratrooper.h"
#include "ParatrooperKind.h"
#include "EntityAnims.h"


HairBusterRiberts::HairBusterRiberts(TextureManager& tm, float spawnX, float spawnY)
    : Boss(500, 30),
      rocketCount(0),
      fireBombCount(0),
      hoverY(spawnY),
      driftSpeed(70.0f),
      facingDir(-1),
      driftTimer(3.5f),
      rocketCooldown(1.8f),
      bombCooldown(4.0f),
      diveCooldown(10.0f),
      isDiving(false),
      diveTimer(0.0f),
      retreatTimer(0.0f),
      explodeStage(0),
      explodeTimer(0.0f)
{
    setupHairBusterRibertsAnims(m_anim, tm);
    m_tex = &tm;
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 144.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 96.0f;
    position.x = spawnX;
    position.y = spawnY;

    float minionY = spawnY - 128.0f;
    if (minionY < 0.0f) minionY = 0.0f;
    minionPrototype = new Paratrooper(tm, spawnX, minionY,
                                      new RebelParatrooperKind());
}

void HairBusterRiberts::update(TileMap& , float dt)
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
        velocity.x = driftSpeed * 1.6f * (float)facingDir;
        velocity.y = -120.0f;
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        m_anim.play("retreat");
        m_anim.setFlipX(facingDir < 0);
        m_anim.setPosition(position.x, position.y);
        m_anim.update(dt);
        if (retreatTimer <= 0.0f) isAlive = false;
        return;
    }

    if (isDiving)
    {
        diveTimer -= dt;
        if (diveTimer > 0.6f)
        {
            velocity.y = +260.0f;
            m_anim.play("idle");
        }
        else if (diveTimer > 0.3f)
        {

            currentStrategy     = &rocketStrat;
            pendingShotOrigin.x = position.x + width * 0.5f;
            pendingShotOrigin.y = position.y + height;
            pendingShotAim.x    = (float)facingDir * 0.5f;
            pendingShotAim.y    = +0.85f;
            hasPendingShot      = true;
        }
        else
        {
            velocity.y = -300.0f;
            m_anim.play("idle");
        }
        position.y += velocity.y * dt;
        if (diveTimer <= 0.0f)
        {
            isDiving      = false;
            position.y    = hoverY;
            diveCooldown  = 10.0f;
        }
    }
    else
    {
        if (hasChaseTarget)
        {
            float playerCenterX = chaseTargetX;
            float bossCenterX   = position.x + width * 0.5f;
            facingDir = (playerCenterX > bossCenterX) ? +1 : -1;
        }


        velocity.x = driftSpeed * (float)facingDir;
        position.x += velocity.x * dt;
        position.y = hoverY;

        driftTimer -= dt;
        if (driftTimer <= 0.0f)
        {
            facingDir = -facingDir;
            driftTimer = 3.5f;
        }


        rocketCooldown -= dt;
        if (rocketCooldown <= 0.0f)
        {
            attack();
            rocketCooldown = 1.8f;
            ++rocketCount;
        }

        bombCooldown -= dt;
        if (bombCooldown <= 0.0f)
        {
            bombCooldown        = 4.0f;
            currentStrategy     = &fireBombStrat;
            pendingShotOrigin.x = position.x + width * 0.5f;
            pendingShotOrigin.y = position.y + height;
            pendingShotAim.x    = (float)facingDir * 0.4f;
            pendingShotAim.y    = +0.5f;
            hasPendingShot      = true;
            ++fireBombCount;
        }
        diveCooldown -= dt;
        if (diveCooldown <= 0.0f)
        {
            isDiving  = true;
            diveTimer = 1.0f;
        }
    }

    if (checkRetreat())
    {
        retreatTimer = 4.0f;
        m_anim.play("damaged", true);
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

    if (!isDiving) m_anim.play("idle");

    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}
void HairBusterRiberts::attack()
{
    currentStrategy     = &rocketStrat;
    pendingShotOrigin.x = position.x + width * 0.5f;
    pendingShotOrigin.y = position.y + height * 0.6f;
    pendingShotAim.x    = (float)facingDir * 0.6f;
    pendingShotAim.y    = +0.6f;
    hasPendingShot      = true;
}



