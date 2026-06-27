
#include "FlyingTara.h"
#include "TileMap.h"
#include "DamageState.h"
#include "EntityAnims.h"
#include "GrenadeProjectile.h"

FlyingTara::FlyingTara(TextureManager& tm, float spawnX, float spawnY)
    : EnemyVehicle(3, true, 100),
      hoverY(spawnY),
      horizSpeed(60.0f),
      facingDir(-1),
      dropCooldown(0.0f),
      hasPendingDrop(false)
{
    setupFlyingTaraAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 64.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 32.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void FlyingTara::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("explode");
        m_anim.update(dt);
        return;
    }
    velocity.x = horizSpeed * (float)facingDir;
    position.x += velocity.x * dt;
    position.y = hoverY;


    if (position.x < 0.0f) { facingDir = +1; position.x = 0.0f; }
    float maxX = (float)((tm.getWidth() - 1) * tm.getTileSize()) - width;
    if (position.x > maxX) { facingDir = -1; position.x = maxX; }

    dropCooldown -= dt;
    if (dropCooldown <= 0.0f)
    {
        attack();
        dropCooldown = 3.5f;
    }

    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);

    m_anim.play("idle");
    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

void FlyingTara::attack()
{
    if (!getCanFire()) return;
    pendingDropOrigin.x = position.x + width  * 0.5f;
    pendingDropOrigin.y = position.y + height;
    hasPendingDrop = true;
}

bool FlyingTara::takePendingDrop(coordSyst& outOrigin)
{
    if (!hasPendingDrop) return false;
    outOrigin = pendingDropOrigin;
    hasPendingDrop = false;
    return true;
}

Entity* FlyingTara::takePendingSpawn()
{
    if (!hasPendingDrop) return nullptr;
    hasPendingDrop = false;
    coordSyst aimDown(0.0f, 1.0f);
    GrenadeProjectile* g = new GrenadeProjectile(this, 5, aimDown,
                                                 120.0f, 1200.0f,
                                                 96.0f);
    g->setPosition(pendingDropOrigin.x, pendingDropOrigin.y);
    return g;
}

void FlyingTara::onDestroy()
{
    EnemyVehicle::onDestroy();
}

Entity* FlyingTara::clone()
{
    return new FlyingTara(*this);
}


void FlyingTara::clampToCameraBand(float cameraTopY, float cameraBottomY)
{
    float viewH = cameraBottomY - cameraTopY;
    if (viewH <= 0.0f) return;


    float spriteH = m_anim.scaledH();
    if (spriteH < 16.0f) spriteH = (float)height;
    if (spriteH < 16.0f) spriteH = 64.0f;

    float minPos = cameraTopY    + 16.0f + spriteH - (float)height;
    float maxPos = cameraBottomY - 16.0f - (float)height;
    if (maxPos < minPos) maxPos = minPos;

    float preferred = cameraTopY + viewH * 0.25f;
    if (preferred < minPos) preferred = minPos;
    if (preferred > maxPos) preferred = maxPos;

    hoverY     = preferred;
    position.y = preferred;
}
