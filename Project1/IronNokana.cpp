#include "IronNokana.h"
#include "TileMap.h"
#include "Tile.h"
#include "DamageState.h"
#include "RebelSoldier.h"
#include "EntityAnims.h"


IronNokana::IronNokana(TextureManager& tm, float spawnX, float spawnY)
    : Boss(500, 30),
      turretMissileCount(0),
      hasFlamethrower(true),
      crawlSpeed(35.0f),
      facingDir(-1),
      fireCooldown(2.0f),
      flameCooldown(4.0f),
      flameBurstTimer(0.0f),
      bombCooldown(5.0f),
      retreatTimer(0.0f),
      explodeStage(0),
      explodeTimer(0.0f),
      minionTimer(12.0f)
{
    setupIronNokanaAnims(m_anim, tm);
    m_tex = &tm;
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 144.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 96.0f;
    position.x = spawnX;

    position.y = spawnY + 96.0f - height;
    minionPrototype = new RebelSoldier(tm, spawnX, spawnY);
}

void IronNokana::update(TileMap& tm, float dt)
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
        velocity.x = crawlSpeed * 1.8f * (float)facingDir;
        position.x += velocity.x * dt;
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

    velocity.x = crawlSpeed * (float)facingDir;
    position.x += velocity.x * dt;


    int ts = tm.getTileSize();
    int gx = (int)((position.x + width * 0.5f) / ts);
    int feR = (int)((position.y + height) / ts);
    Tile* below = tm.getTile(gx, feR);
    if (below != nullptr && below->isSolid())
        position.y = (float)(feR * ts) - height;


    fireCooldown -= dt;
    if (fireCooldown <= 0.0f)
    {
        attack();
        fireCooldown = 2.0f;
        ++turretMissileCount;
    }

    if (flameBurstTimer > 0.0f)
    {
        flameBurstTimer -= dt;
        currentStrategy   = &flameStrat;
        pendingShotOrigin.x = position.x + (facingDir > 0 ? width : 0.0f);
        pendingShotOrigin.y = position.y + height * 0.65f;
        pendingShotAim.x  = (float)facingDir;
        pendingShotAim.y  = 0.0f;
        hasPendingShot    = true;
    }
    else
    {
        flameCooldown -= dt;
        if (flameCooldown <= 0.0f)
        {
            flameBurstTimer = 6.0f;
            flameCooldown   = 10.0f;
        }
    }
    bombCooldown -= dt;
    if (bombCooldown <= 0.0f)
    {
        bombCooldown        = 5.0f;
        currentStrategy     = &fireBombStrat;
        pendingShotOrigin.x = position.x + width * 0.5f;
        pendingShotOrigin.y = position.y;
        pendingShotAim.x    = (float)facingDir * 0.7f;
        pendingShotAim.y    = -0.7f;
        hasPendingShot      = true;
    }
    if (checkRetreat())
    {
        retreatTimer = 4.0f;
        m_anim.play("damaged", true);
        return;
    }


    minionTimer -= dt;
    if (minionTimer <= 0.0f)
    {
        wantsMinionBatch = true;
        minionTimer      = 12.0f;
    }

    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);

    bool attacking = (flameBurstTimer > 0.0f)
                  || (bombCooldown > 4.7f && bombCooldown < 4.9f)
                  || (fireCooldown  > 1.7f && fireCooldown  < 1.95f);
    if (attacking) m_anim.play("hatch_open");
    else           m_anim.play("idle");

    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

void IronNokana::attack()
{
    currentStrategy     = &rocketStrat;
    pendingShotOrigin.x = position.x + (facingDir > 0 ? width : 0.0f);
    pendingShotOrigin.y = position.y + height * 0.25f;
    pendingShotAim.x    = (float)facingDir;
    pendingShotAim.y    = -0.15f;
    hasPendingShot      = true;
}
