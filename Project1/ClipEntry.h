#pragma once
#include <SFML/Graphics.hpp>
#include "AnimClip.h"

static const int SA_MAX_CLIPS = 48;
struct ClipEntry
{
    char  name[32];
    AnimClip  clip;
    sf::Texture* tex;
    bool valid;

    ClipEntry();
};