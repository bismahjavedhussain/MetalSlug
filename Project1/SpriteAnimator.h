#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "ClipEntry.h"

class SpriteAnimator
{
private:
    sf::Sprite   m_sprite;
    ClipEntry    m_clips[SA_MAX_CLIPS];
    int          m_count;
    int          m_cur;
    int          m_frame;
    float        m_timer;
    bool         m_done;
    float        m_sx;
    float        m_sy;
    bool         m_flipX;
    bool         m_visible;

    void applyRect();
    int  findClip(const char* name) const;
    bool nameEquals(const char* a, const char* b) const;
    void copyName(char* dst, const char* src) const;

public:
    SpriteAnimator();


    void setScale(float sx, float sy);


    void addClip(const char* name,
        const char* sheetPath,
        const AnimClip& clip,
        TextureManager& tm);

    void addClipAuto(const char* name,
        const char* stripPath,
        int frameCount,
        float interval,
        bool looping,
        TextureManager& tm);
    void addClipExternal(const char* name,
        sf::Texture& tex,
        int frameCount,
        float interval,
        bool looping);


    void play(const char* name, bool force = false);
    void restart();


    void update(float dt);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& rw) const;

    void setFlipX(bool flip);

    void setVisible(bool v);
    bool isVisible() const;

    bool  isFinished()  const;
    int   getFrame()    const;
    float scaledW()     const;
    float scaledH()     const;
};