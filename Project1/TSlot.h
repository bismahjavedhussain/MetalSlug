#pragma once
#include <SFML/Graphics.hpp>

struct TSlot
{
    char path[256];
    sf::Texture tex;
    bool used;

    TSlot();
};