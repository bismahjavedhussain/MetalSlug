#include "AmphibiousSlug.h"
#include "VehicleModeStrategy.h"
#include "PlayerSoldier.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "Rocket.h"
#include "ReverseArcMissile.h"
#include "TileMap.h"
#include "Tile.h"
#include "DamageState.h"
#include "EntityAnims.h"
#include "TextureManager.h"
#include <cmath>

AmphibiousSlug::AmphibiousSlug(TextureManager& tm, float spawnX, float spawnY)
    : Vehicle(14),
      currentMode(new NormalSlugMode()),
      aimAngle(0.0f)
{
    fireRate = 0.10f;
    setupAmphibiousSlugAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 96.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 64.0f;
    position.x = spawnX;
    position.y = spawnY;

    if (currentMode != nullptr) currentMode->setOwner(this);
}

AmphibiousSlug::~AmphibiousSlug()
{
    if (currentMode != nullptr) { delete currentMode; currentMode = nullptr; }
}

void AmphibiousSlug::switchMode(TileMap& tm)
{
    if (currentMode == nullptr) return;
    VehicleModeStrategy* next = currentMode->canSwitchTo(tm);
    if (next != nullptr)
    {
        delete currentMode;
        currentMode = next;
        currentMode->setOwner(this);
    }
}

void AmphibiousSlug::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("explode");
        m_anim.update(dt);
        return;
    }


    switchMode(tm);
    if (currentMode != nullptr) currentMode->update(tm, dt);
    int ts = tm.getTileSize();
    int gx = (int)((position.x + width * 0.5f) / ts);
    int gy = (int)((position.y + height) / ts);
    Tile* below = tm.getTile(gx, gy);
    bool inWater = (below != nullptr && below->isWater());

    velocity.y += (inWater ? 200.0f : 1400.0f) * dt;
    if (velocity.y > 1500.0f) velocity.y = 1500.0f;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if (below != nullptr && below->isSolid())
    {
        position.y = (float)(gy * ts) - height;
        velocity.y = 0.0f;
        isOnGround = true;
    }
    else
    {
        isOnGround = false;
    }

    if (fireCooldown > 0.0f) fireCooldown -= dt;
    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);



    if (!isAlive)             m_anim.play("explode");
    else if (inWater)
        m_anim.play(std::fabs(velocity.x) > 1.0f ? "mariner_move" : "mariner_idle");
    else if (!isOnGround)
        m_anim.play(velocity.y < -1.0f ? "flyer_fly_up"
                                       : (velocity.y > 1.0f ? "flyer_fly_dn" : "flyer_idle"));
    else
        m_anim.play(std::fabs(velocity.x) > 1.0f ? "slug_move" : "slug_idle");

    m_anim.setFlipX(velocity.x < 0.0f);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

Entity* AmphibiousSlug::fire(coordSyst aim)
{


    if (currentMode != nullptr) currentMode->fire(aim);
    return nullptr;
}

void AmphibiousSlug::pilotInput(InputHandler& in, float )
{
    if (!isAlive) return;

    const float SPEED = 220.0f;
    if (in.isLeftHeld())       velocity.x = -SPEED;
    else if (in.isRightHeld()) velocity.x = +SPEED;
    else                       velocity.x *= 0.85f;

    if (in.isJumpPressed())
    {


        velocity.y = -550.0f;
    }

    if (in.isAimUpHeld()) { aimAngle += 90.0f * 0.016f; if (aimAngle > 90.0f) aimAngle = 90.0f; }
    else                  { aimAngle -= 90.0f * 0.016f; if (aimAngle < 0.0f)  aimAngle = 0.0f;  }

    if (in.isFireHeld() && fireCooldown <= 0.0f)
    {
        fireCooldown = fireRate / pilotFireRateMult();
        float rad = aimAngle * 3.14159265f / 180.0f;
        int   sgn = (velocity.x < 0.0f) ? -1 : +1;
        coordSyst aim((float)sgn * std::cos(rad), -std::sin(rad));
        fire(aim);
    }
}


void AmphibiousSlug::fireAsSlug(coordSyst aim)
{
    if (pilot != nullptr) pilot->queueProjectile(new Bullet(this, 3, aim, 700.0f, 1200.0f));
}
void AmphibiousSlug::fireAsFlyerMissile(coordSyst aim)
{
    if (pilot != nullptr) pilot->queueProjectile(new Rocket(this, 5, aim, 600.0f, 1500.0f, 96.0f));
}
void AmphibiousSlug::fireAsFlyerBullet(coordSyst aim)
{
    if (pilot != nullptr) pilot->queueProjectile(new Bullet(this, 3, aim, 350.0f, 1000.0f));
}
void AmphibiousSlug::fireAsMarinerHorizontal(coordSyst aim)
{
    coordSyst horiz(aim.x >= 0.0f ? 1.0f : -1.0f, 0.0f);
    if (pilot != nullptr) pilot->queueProjectile(new Bullet(this, 4, horiz, 650.0f, 1100.0f));
}
void AmphibiousSlug::fireAsMarinerVertical(coordSyst aim)
{
    coordSyst up(0.0f, -1.0f);
    if (pilot != nullptr) pilot->queueProjectile(new Bullet(this, 4, up, 650.0f, 900.0f));
}
void AmphibiousSlug::fireAsMarinerReverse(coordSyst aim)
{
    coordSyst rev(aim.x * 0.5f, -1.0f);
    if (pilot != nullptr)
        pilot->queueProjectile(new ReverseArcMissile(this, 4, rev, 450.0f, -600.0f, 96.0f));
}
