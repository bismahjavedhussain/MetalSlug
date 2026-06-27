#include "FirePool.h"

sf::Texture FirePool::s_tex;
bool        FirePool::s_loaded = false;
FirePool::FirePool(coordSyst centre, float r, float dur)
    : AreaHazard(2, dur), radius(r), damageAccum(0.0f)
{
    width      = r * 2.0f;
    height     = 64.0f;
    position.x = centre.x - width  * 0.5f;
    position.y = centre.y - height;

    ensureTexture();
    if (s_loaded)
    {
        m_anim.setScale(1.f, 1.f);
        m_anim.addClipExternal("idle", s_tex, 4, 0.10f, true);
        m_anim.play("idle");
    }
}

void FirePool::ensureTexture()
{
    if (s_loaded) return;
    s_loaded = s_tex.loadFromFile("assets/projectiles/firepool.png");
}

void FirePool::update(TileMap& , float dt)
{
    if (!isAlive) return;
    duration -= dt;
    if (duration <= 0.0f) isAlive = false;
    m_anim.update(dt);
}

void FirePool::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}

bool FirePool::isExpired()
{
    return duration <= 0.0f;
}
