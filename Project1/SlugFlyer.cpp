#include "SlugFlyer.h"
#include "PlayerSoldier.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "Rocket.h"
#include "TileMap.h"
#include "DamageState.h"
#include "EntityAnims.h"
#include "TextureManager.h"
#include <cmath>



SlugFlyer::SlugFlyer(TextureManager& tm, float spawnX, float spawnY)
    : AerialVehicle(10), missilesRemaining(4), aimAngle(0.0f)
{
    fireRate = 0.10f;
    setupSlugFlyerAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 96.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 64.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void SlugFlyer::update(TileMap& , float dt)
{
    if (!isAlive)
    {
        m_anim.play("explode");
        m_anim.update(dt);
        return;
    }


    velocity.y += 200.0f * dt;
    if (velocity.y > 250.0f) velocity.y = 250.0f;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if (fireCooldown > 0.0f) fireCooldown -= dt;
    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);

    m_anim.play(velocity.y < -10.0f ? "fly_up" : (velocity.y > 10.0f ? "fly_down" : "idle"));
    m_anim.setFlipX(velocity.x < 0.0f);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}



Entity* SlugFlyer::fire(coordSyst aim)
{
    if (fireCooldown > 0.0f) return nullptr;
    fireCooldown = fireRate / pilotFireRateMult();

    if (missilesRemaining > 0)
    {
        missilesRemaining--;
        return new Rocket(this, 5, aim, 600.0f, 1500.0f, 96.0f);
    }
    return new Bullet(this, 3, aim, 350.0f, 1000.0f);
}

void SlugFlyer::pilotInput(InputHandler& in, float dt)
{
    if (!isAlive) return;

    const float SPEED = 220.0f;
    if (in.isLeftHeld())       velocity.x = -SPEED;
    else if (in.isRightHeld()) velocity.x = +SPEED;
    else                       velocity.x *= 0.85f;


    if (in.isJumpPressed())  ascend(dt * 6.0f);

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
