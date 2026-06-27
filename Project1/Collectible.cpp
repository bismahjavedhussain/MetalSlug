#include "Collectible.h"

Collectible::Collectible() : Entity(), consumed(false)
{
    width  = 24.0f;
    height = 24.0f;
}
void Collectible::update(TileMap& , float dt)
{
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

void Collectible::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}
