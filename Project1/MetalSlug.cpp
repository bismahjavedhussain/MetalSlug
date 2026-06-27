#include "MetalSlug.h"
#include "PlayerSoldier.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "TileMap.h"
#include "Tile.h"
#include "DamageState.h"
#include "EntityAnims.h"
#include "TextureManager.h"
#include <cmath>

MetalSlug::MetalSlug(TextureManager& tm, float spawnX, float spawnY)
    : GroundVehicle(12), aimAngle(0.0f)
{
    fireRate = 0.08f;
    setupMetalSlugAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 96.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 64.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void MetalSlug::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("explode");
        m_anim.update(dt);
        return;
    }

    if (!isOccupied)
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;

        int ts = tm.getTileSize();
        int gx = (int)((position.x + width * 0.5f) / ts);
        int feR = (int)((position.y + height) / ts);
        Tile* below = tm.getTile(gx, feR);
        if (below != nullptr && below->isSolid())
            position.y = (float)(feR * ts) - height;
        isOnGround = true;

        if (currentDamageState != nullptr)
            currentDamageState->update(this, dt);


        m_anim.play("idle");
        m_anim.setPosition(position.x, position.y);
        m_anim.update(dt);
        return;
    }

    const float GRAVITY = 1400.0f;
    velocity.y += GRAVITY * dt;
    if (velocity.y > 1500.0f) velocity.y = 1500.0f;

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
        traverseStep(tm);
    }
    else
    {
        isOnGround = false;
    }

    if (position.x < 0.0f) position.x = 0.0f;
    float maxX = (float)((tm.getWidth() - 1) * ts) - width;
    if (position.x > maxX) position.x = maxX;

    if (fireCooldown > 0.0f) fireCooldown -= dt;
    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);

    float vxAbs = (velocity.x < 0.0f) ? -velocity.x : velocity.x;

    if (!isOnGround)
        m_anim.play("jump");
    else if (aimAngle > 30.0f)
        m_anim.play("shoot_up");
    else if (vxAbs > 1.0f)
        m_anim.play("driving_pilot");
    else
        m_anim.play("idle");

    if (velocity.x < -0.1f)    
      m_anim.setFlipX(true);
    else if (velocity.x >  0.1f)
     m_anim.setFlipX(false);

    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

Entity* MetalSlug::fire(coordSyst aim)
{
    if (fireCooldown > 0.0f) return nullptr;
    fireCooldown = fireRate / pilotFireRateMult();
    return new Bullet(this, 3, aim, 700.0f, 1200.0f);
}

void MetalSlug::pilotInput(InputHandler& in, float )
{
    if (!isAlive) return;

    const float SPEED = treadSpeed;
    if (in.isLeftHeld())  velocity.x = -SPEED;
    else if (in.isRightHeld()) velocity.x = +SPEED;
    else velocity.x = 0.0f;

    if (in.isJumpPressed() && isOnGround)
    {
        velocity.y = -550.0f;
        isOnGround = false;
    }

    if (in.isAimUpHeld()) { aimAngle += 90.0f * 0.016f; if (aimAngle > 90.0f) aimAngle = 90.0f; }
    else                  { aimAngle -= 90.0f * 0.016f; if (aimAngle < 0.0f)  aimAngle = 0.0f;  }

    if (in.isFireHeld() && fireCooldown <= 0.0f)
    {
        float rad = aimAngle * 3.14159265f / 180.0f;
        int   sgn = (velocity.x < 0.0f) ? -1 : +1;
        coordSyst aim((float)sgn * std::cos(rad), -std::sin(rad));


        if (pilot != nullptr)
        {
            Entity* spawned = fire(aim);
            if (spawned != nullptr) pilot->queueProjectile(spawned);
        }
    }
}
