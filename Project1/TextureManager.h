#pragma once
#include <SFML/Graphics.hpp>
#include "TSlot.h"










static const int TM_MAX = 256;

class TextureManager
{
private:
    TSlot m_slots[TM_MAX];
    int   m_count;

    int  find(const char* path) const;
    bool pathEquals(const char* a, const char* b) const;
    void copyPath(char* dst, const char* src) const;

public:
    TextureManager();


    sf::Texture& load(const char* path);


    void unloadAll();

    int getCount() const;
};
