#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"


class VFXOverlay
{
private:
    sf::Sprite   m_redInjured;
    sf::Sprite   m_redCritical;
    sf::Sprite   m_redDead;
    bool         m_loaded;

public:
    VFXOverlay();
    void loadAssets(TextureManager& tm);






    void drawForDamageState(sf::RenderWindow& rw, int damageState);
};