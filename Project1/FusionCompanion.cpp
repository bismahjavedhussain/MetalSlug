#include "FusionCompanion.h"
#include "PlayerSoldier.h"
#include "TileMap.h"
#include "Tile.h"
#include "Bullet.h"
#include "EntityAnims.h"
#include <cmath>


FusionCompanion::FusionCompanion(TextureManager& tm,
                                 PlayerSoldier* fusionMembers[MAX_MEMBERS],
                                 int            count,
                                 float          spawnX,
                                 float          spawnY,
                                 float          lifetimeSeconds)
    : Soldier(30), memberCount(0),fireRateMultiplier(1.0f),speedMultiplier(1.0f),
      meleeDamageMultiplier(1.0f),ammoPickupMultiplier(1.0f),
      blastRadiusMultiplier(1.0f),
      lifetime(lifetimeSeconds),followTarget(nullptr),pendingShot(nullptr),
      fireCooldown(0.6f), facingDir(+1)
{

    if (count < 2) count = 2;
    if (count > MAX_MEMBERS) count = MAX_MEMBERS;
    memberCount = count;
    for (int i = 0; i < MAX_MEMBERS; ++i) members[i] = nullptr;
    if (fusionMembers != nullptr)
        for (int i = 0; i < memberCount; ++i) members[i] = fusionMembers[i];

    averageStatsFromMembers();



    setupFusionCompanionAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 32.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 48.0f;
    position.x = spawnX;
    position.y = spawnY;


    isInvelnerable = true;
}
void FusionCompanion::averageStatsFromMembers()
{
    if (memberCount <= 0) return;

    int   hpSum     = 0;
    float speedSum  = 0.0f;
    float fireMult  = 0.0f;

    float meleeSum  = 0.0f;
    float ammoSum   = 0.0f;
    float blastSum  = 0.0f;
    int   live      = 0;

    for (int i = 0; i < memberCount; ++i)
    {
        PlayerSoldier* m = members[i];
        if (m == nullptr) continue;
        ++live;
        hpSum    += m->getHealth();
        speedSum += m->getBaseSpeed();
        meleeSum += m->getMeleeDamageMult();
        ammoSum  += m->getAmmoPickupMult();
        blastSum += m->getBlastRadiusMult();


        fireMult += 1.0f;
    }

    if (live <= 0) return;
    float invN = 1.0f / (float)live;

    healthPoints          = (int)((float)hpSum * invN);
    maxHealthPoints       = healthPoints;
    baseSpeed             = speedSum * invN;
    fireRateMultiplier    = fireMult * invN;
    meleeDamageMultiplier = meleeSum * invN;
    ammoPickupMultiplier  = ammoSum  * invN;
    blastRadiusMultiplier = blastSum * invN;
    speedMultiplier       = 1.0f;
}

void FusionCompanion::update(TileMap& tm, float dt)
{
    lifetime -= dt;
    if (lifetime <= 0.0f)
    {
        isAlive = false;
        m_anim.play("despawn");
        m_anim.update(dt);
        return;
    }


    const float GRAVITY = 1200.0f;
    velocity.y += GRAVITY * dt;
    if (velocity.y > 1200.0f) velocity.y = 1200.0f;


    if (followTarget != nullptr && followTarget->getIsAlive())
    {
        coordSyst tgt = followTarget->getPosition();
        float dx = tgt.x - position.x;
        float dist = std::fabs(dx);
        if (dist > 96.0f)
        {
            velocity.x = (dx > 0.0f ? +1.0f : -1.0f) * baseSpeed;
            facingDir  = (dx > 0.0f ? +1 : -1);
        }
        else
        {
            velocity.x = 0.0f;
        }
    }
    else
    {
        velocity.x = 0.0f;
    }

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    int ts = tm.getTileSize();
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



    if (fireCooldown > 0.0f) fireCooldown -= dt;
    if (fireCooldown <= 0.0f && pendingShot == nullptr)
    {
        attack();
        fireCooldown = 0.6f;
    }

    if      (lifetime <= 1.0f)             
    m_anim.play("despawn");
    else if (fireCooldown>0.4f)           
    m_anim.play("shoot");
    else if ( !isOnGround)
        m_anim.play("jump");
        else
    m_anim.play("walk");

    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}


void FusionCompanion::attack()
{
    m_anim.play("fire", true);
    if (pendingShot != nullptr) return;

    coordSyst aim;
    aim.x = (float)facingDir;
    aim.y = 0.0f;
    coordSyst origin;
    origin.x = position.x + width  * 0.5f;
    origin.y = position.y + height * 0.40f;

    Bullet* b = new Bullet(this, 3, aim, 520.0f, 900.0f);
    b->setPosition(origin.x, origin.y);
    pendingShot = b;
}

Entity* FusionCompanion::takePendingShot()
{
    Entity* p = pendingShot;
    pendingShot = nullptr;
    return p;
}

FusionCompanion::~FusionCompanion()
{
    if (pendingShot != nullptr)
    {
        delete pendingShot;
        pendingShot = nullptr;
    }

}
void FusionCompanion::render(sf::RenderWindow&rw) {
m_anim.draw(rw);

}