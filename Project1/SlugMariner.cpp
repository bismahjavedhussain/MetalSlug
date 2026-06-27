#include "SlugMariner.h"
#include "PlayerSoldier.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "ReverseArcMissile.h"
#include "TileMap.h"
#include "DamageState.h"
#include "EntityAnims.h"
#include "TextureManager.h"
#include <cmath>

SlugMariner::SlugMariner(TextureManager& tm, float spawnX, float spawnY)
    : AquaticVehicle(10),
      horizontalMissiles(3), verticalMissiles(3), reverseArcMissiles(3),
      aimAngle(0.0f)
{
    fireRate = 0.30f;
    setupSlugMarinerAnims(m_anim, tm);
    width  = m_anim.scaledW(); if (width  < 1.0f) width  = 96.0f;
    height = m_anim.scaledH(); if (height < 1.0f) height = 56.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void SlugMariner::update(TileMap& , float dt)
{
    if (!isAlive) return;


    velocity.y += 150.0f * dt;
    if (velocity.y > 200.0f) velocity.y = 200.0f;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if (fireCooldown > 0.0f) fireCooldown -= dt;
    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);

    if (!isAlive)                                  m_anim.play("explode");
    else if (std::fabs(velocity.x) > 1.0f)         m_anim.play("move");
    else                                           m_anim.play("idle");
    m_anim.setFlipX(velocity.x < 0.0f);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}





Entity* SlugMariner::fire(coordSyst aim)
{
    if (fireCooldown > 0.0f) return nullptr;
    fireCooldown = fireRate / pilotFireRateMult();

    if (aim.y < -0.6f && verticalMissiles > 0)
    {
        verticalMissiles--;
        coordSyst up(0.0f, -1.0f);
        return new Bullet(this, 4, up, 650.0f, 900.0f);
    }
    if (aim.y > 0.6f && reverseArcMissiles > 0)
    {
        reverseArcMissiles--;


        coordSyst rev(aim.x * 0.5f, -1.0f);
        return new ReverseArcMissile(this, 4, rev, 450.0f,
                                     -600.0f, 96.0f);
    }
    if (horizontalMissiles > 0)
    {
        horizontalMissiles--;
        coordSyst horiz(aim.x >= 0.0f ? 1.0f : -1.0f, 0.0f);
        return new Bullet(this, 4, horiz, 650.0f, 1100.0f);
    }

    fireCooldown = 0.0f;
    return nullptr;
}

void SlugMariner::pilotInput(InputHandler& in, float )
{
    if (!isAlive) return;

    const float SPEED = 200.0f;
    if (in.isLeftHeld())       velocity.x = -SPEED;
    else if (in.isRightHeld()) velocity.x = +SPEED;
    else                       velocity.x *= 0.85f;


    if (in.isJumpPressed()) velocity.y = -260.0f;

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
