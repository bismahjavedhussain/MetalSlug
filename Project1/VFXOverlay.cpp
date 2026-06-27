#include "VFXOverlay.h"

VFXOverlay::VFXOverlay() : m_loaded(false) {}

void VFXOverlay::loadAssets(TextureManager& tm)
{
    m_redInjured.setTexture(tm.load("Sprites/clean/overlay_red_25.png"));
    m_redCritical.setTexture(tm.load("Sprites/clean/overlay_red_75.png"));
    m_redDead.setTexture(tm.load("Sprites/clean/overlay_red_dead.png"));

    m_redInjured.setPosition(0.f, 0.f);
    m_redCritical.setPosition(0.f, 0.f);
    m_redDead.setPosition(0.f, 0.f);

    m_loaded = true;
}

void VFXOverlay::drawForDamageState(sf::RenderWindow& rw, int damageState)
{
    if (!m_loaded) return;

    if (damageState == 1) rw.draw(m_redInjured);
    else if (damageState == 2) rw.draw(m_redCritical);
    else if (damageState == 3) rw.draw(m_redDead);

}