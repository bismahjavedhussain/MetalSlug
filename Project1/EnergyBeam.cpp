#include "EnergyBeam.h"
#include <cmath>

sf::Texture EnergyBeam::s_tex;
bool        EnergyBeam::s_loaded = false;

EnergyBeam::EnergyBeam(Entity* shooter, int dmg, coordSyst dir, float spd, float rng, float life, bool instantKill)
    : StraightProjectile(shooter, dmg, dir, spd, rng),
      range(rng), lifetime(life), isInstantKill(instantKill)
{
    ensureTexture();
    if (s_loaded)
    {
        m_anim.setScale(1.f, 1.f);
        m_anim.addClipExternal("idle", s_tex, 1, 0.10f, true);
        m_anim.play("idle");
    }
}
void EnergyBeam::ensureTexture()
{
    if (s_loaded) return;
    s_loaded = s_tex.loadFromFile("assets/projectiles/laser.png");
}

void EnergyBeam::update(TileMap& tm, float dt)
{
    StraightProjectile::update(tm, dt);
    lifetime -= dt;
    if (lifetime <= 0.0f) isAlive = false;
}
void EnergyBeam::onImpact() {}
void EnergyBeam::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}
