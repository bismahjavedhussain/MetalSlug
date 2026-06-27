#include "Rocket.h"

sf::Texture Rocket::s_tex;
bool        Rocket::s_loaded = false;

Rocket::Rocket(Entity* shooter, int dmg, coordSyst dir, float spd, float range, float bRadius)
    : StraightProjectile(shooter, dmg, dir, spd, range), blastRadius(bRadius)
{
    ensureTexture();
    if (s_loaded)
    {
        m_anim.setScale(1.f, 1.f);
        m_anim.addClipExternal("idle", s_tex, 1, 0.10f, true);
        m_anim.play("idle");
    }
}

void Rocket::ensureTexture()
{
    if (s_loaded) return;
    s_loaded = s_tex.loadFromFile("assets/projectiles/rocket.png");
}

void Rocket::update(TileMap& tm, float dt)
{
    StraightProjectile::update(tm, dt);
}

void Rocket::onImpact()
{
    isAlive = false;
}

void Rocket::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}
