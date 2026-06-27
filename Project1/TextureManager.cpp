#include "TextureManager.h"
#include <iostream>


TextureManager::TextureManager() : m_count(0) {}

bool TextureManager::pathEquals(const char* a, const char* b) const
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        return false;
        ++i;
    }
    return a[i] == '\0' && b[i] == '\0';
}

void TextureManager::copyPath(char* dst, const char* src) const
{
    int i = 0;
    while (i < 255 && src[i] != '\0')
    {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
}

int TextureManager::find(const char* path) const
{
    for (int i = 0; i < TM_MAX; ++i)
        if (m_slots[i].used && pathEquals(m_slots[i].path, path))
            return i;
    return -1;
}

sf::Texture& TextureManager::load(const char* path)
{
    int idx = find(path);
    if (idx != -1) return m_slots[idx].tex;

    for (int i = 0; i < TM_MAX; ++i)
    {
        if (!m_slots[i].used)
        {
            m_slots[i].used = true;
            copyPath(m_slots[i].path, path);
            if (!m_slots[i].tex.loadFromFile(path))
            {
                std::cout << "[TM] FAILED to load: " << path
                          << "  -- file missing OR exceeds GPU max texture size ("
                          << sf::Texture::getMaximumSize() << " px). "
                          << "Split the sheet into smaller PNGs." << std::endl;
            }











            ++m_count;
            return m_slots[i].tex;
        }
    }

    std::cout << "[TM] pool full" << std::endl;
    return m_slots[0].tex;
}

void TextureManager::unloadAll()
{
    for (int i = 0; i < TM_MAX; ++i)
    {
        if (m_slots[i].used)
        {
            m_slots[i].tex = sf::Texture();
            m_slots[i].used = false;
            m_slots[i].path[0] = '\0';
        }
    }
    m_count = 0;
}

int TextureManager::getCount() const { return m_count; }
