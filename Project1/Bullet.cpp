#include "Bullet.h"
#include <cmath>

sf::Texture Bullet::s_tex;
bool        Bullet::s_loaded = false;

Bullet::Bullet(Entity* shooter, int dmg, coordSyst dir, float spd, float range)
    : StraightProjectile(shooter, dmg, dir, spd, range),
      isBentByFannum(false), meleeFlag(false), pierceShieldFlag(false)
{ ensureTexture();
    if (s_loaded)
    {
        m_anim.setScale(1.f, 1.f);
        m_anim.addClipExternal("idle", s_tex, 1, 0.10f, true);
        m_anim.play("idle");
    }
}

void Bullet::ensureTexture()
{
    if (s_loaded) return;
    s_loaded = s_tex.loadFromFile("assets/projectiles/bullet.png");
}

void Bullet::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}

void Bullet::update(TileMap& tm, float dt)
{
    StraightProjectile::update(tm, dt);
}

void Bullet::bendTowardTarget(coordSyst target, float radius, float dt)
{
    float dx = target.x - position.x;
    float dy = target.y - position.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance < 1.0f) distance = 1.0f;

    float gravPull = 150000.0f;
    float vLimit = std::sqrt((2.0f * gravPull * radius) / (distance * (distance + radius)));
    float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    if (currentSpeed > vLimit)
    {
        velocity.x *= 0.95f;
        velocity.y *= 0.95f;
    }

    float directx = dx / distance;
    float directy = dy / distance;
    float pullForce = gravPull / (distance * distance);
    if (pullForce > 1000.0f) pullForce = 1000.0f;

    velocity.x += directx * pullForce * dt;
    velocity.y += directy * pullForce * dt;
    isBentByFannum = true;
}
void Bullet::onImpact()
{
    isAlive = false;
}
