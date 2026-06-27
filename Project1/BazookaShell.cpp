#include "BazookaShell.h"

sf::Texture BazookaShell::s_tex;
bool BazookaShell::s_loaded = false;

BazookaShell::BazookaShell(Entity* shooter, int dmg, coordSyst dir, float spd, float grav, float bRadius)
    : BallisticProjectile(shooter, dmg, dir, spd, grav), blastRadius(bRadius)
{
    this->velocity.y = -300.0f;

    ensureTexture();
    if (s_loaded)
    {
        m_anim.setScale(1.f, 1.f);
        m_anim.addClipExternal("idle", s_tex, 1, 0.10f, true);
        m_anim.play("idle");
    }
}

void BazookaShell::ensureTexture()
{
    if (s_loaded) return;
    s_loaded = s_tex.loadFromFile("assets/projectiles/shell.png");
}

void BazookaShell::onImpact()
{
    isAlive = false;
}

void BazookaShell::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}
