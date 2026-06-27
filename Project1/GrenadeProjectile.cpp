#include "GrenadeProjectile.h"

sf::Texture GrenadeProjectile::s_tex;
bool        GrenadeProjectile::s_loaded = false;

GrenadeProjectile::GrenadeProjectile(Entity* shooter, int dmg, coordSyst dir, float spd, float grav, float bRadius)
    : BallisticProjectile(shooter, dmg, dir, spd, grav), blastRadius(bRadius), bounces(3)
{
    ensureTexture();
    if (s_loaded)
    {
        m_anim.setScale(1.f, 1.f);
        m_anim.addClipExternal("idle", s_tex, 1, 0.10f, true);
        m_anim.play("idle");
    }
}

void GrenadeProjectile::ensureTexture()
{
    if (s_loaded) return;
    s_loaded = s_tex.loadFromFile("assets/projectiles/grenade.png");
}

void GrenadeProjectile::update(TileMap& tm, float dt)
{
    BallisticProjectile::update(tm, dt);
}

void GrenadeProjectile::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}

void GrenadeProjectile::bounceOnFloor()
{
    if (bounces < 3)
    {
        velocity.y = -(velocity.y) * 0.7f;
        velocity.x =  (velocity.x) * 0.8f;
        bounces++;
    }
    else
    {
        onImpact();
    }
}

void GrenadeProjectile::onImpact() { isAlive = false; }

int GrenadeProjectile::getBounces() const { return bounces; }
