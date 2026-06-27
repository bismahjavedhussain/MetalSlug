#include "FireStream.h"
#include "Direction.h"

sf::Texture FireStream::s_tex;
bool        FireStream::s_loaded = false;

FireStream::FireStream(coordSyst origin, Direction* dir, float length)
    : AreaHazard(2, 0.15f),
      streamLength(length),
      direction(dir)
{
    position = origin;
    width    = length;
    height   = 32.0f;

    ensureTexture();
    if (s_loaded)
    {
        m_anim.setScale(1.f, 1.f);
        m_anim.addClipExternal("idle", s_tex, 4, 0.06f, true);
        m_anim.play("idle");
    }
}

void FireStream::ensureTexture()
{
    if (s_loaded) return;
    s_loaded = s_tex.loadFromFile("assets/projectiles/firestream.png");
}

FireStream::~FireStream()
{
    if (direction != nullptr) { delete direction; direction = nullptr; }
}

void FireStream::update(TileMap& , float dt)
{
    if (!isAlive) return;
    duration -= dt;
    if (duration <= 0.0f) isAlive = false;
    m_anim.setFlipX(facingSign() < 0);
    m_anim.update(dt);
}

void FireStream::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}

bool FireStream::isExpired()
{
    return duration <= 0.0f || !isAlive;
}

void FireStream::deactivate()
{
    duration = 0.0f;
    isAlive  = false;
}

int FireStream::facingSign() const
{
    return (direction != nullptr) ? direction->getXSign() : +1;
}
