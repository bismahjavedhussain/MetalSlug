#include "SpriteAnimator.h"
#include <iostream>

SpriteAnimator::SpriteAnimator()
    : m_count(0), m_cur(-1), m_frame(0),
    m_timer(0.f), m_done(false),
    m_sx(1.f), m_sy(1.f),
    m_flipX(false), m_visible(true)
{
}


bool SpriteAnimator::nameEquals(const char* a, const char* b) const
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i]) return false;
        ++i;
    }
    return a[i] == '\0' && b[i] == '\0';
}


void SpriteAnimator::copyName(char* dst, const char* src) const
{
    int i = 0;
    while (i < 31 && src[i] != '\0')
    {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
}

int SpriteAnimator::findClip(const char* name) const
{
    for (int i = 0; i < m_count; ++i)
        if (m_clips[i].valid && nameEquals(m_clips[i].name, name))
            return i;
    return -1;
}


void SpriteAnimator::applyRect()
{
    if (m_cur < 0) return;
    const AnimClip& c = m_clips[m_cur].clip; 

    int left = m_frame * c.frameW;  
    int w = c.frameW; 

    if (m_flipX)
    {

        left = left + c.frameW;  
        w = -c.frameW;
    }

    m_sprite.setTextureRect(sf::IntRect(left, c.srcY, w, c.srcH));
}


void SpriteAnimator::setScale(float sx, float sy)
{
    m_sx = sx; m_sy = sy;
    m_sprite.setScale(sx, sy);
}

void SpriteAnimator::addClip(const char* name,
    const char* sheetPath,
    const AnimClip& clip,
    TextureManager& tm)
{
    if (m_count >= SA_MAX_CLIPS)
    {
        std::cout << "[SA] clip table full" << std::endl;
        return;
    }

    ClipEntry& e = m_clips[m_count];
    e.tex = &tm.load(sheetPath);

    sf::Vector2u sz = e.tex->getSize();

    int needX = clip.frameW * clip.frameCount;
    int needY = clip.srcY + clip.srcH;
    if (sz.x == 0 || sz.y == 0)
    {
        std::cout << "[SA] clip '" << name << "' on " << sheetPath
                  << " -- texture is empty (load failed)." << std::endl;
    }
    else if ((unsigned)needX > sz.x || (unsigned)needY > sz.y || clip.frameW <= 0 || clip.srcH <= 0)
    {
        std::cout << "[SA] clip '" << name << "' OUT OF BOUNDS on " << sheetPath
                  << " sheet=" << sz.x << "x" << sz.y
                  << " needs " << needX << "x" << needY
                  << " (srcY=" << clip.srcY << " srcH=" << clip.srcH
                  << " frameW=" << clip.frameW << " frames=" << clip.frameCount << ")" << std::endl;
    }

    e.clip = clip;
    e.valid = true;
    copyName(e.name, name);
    ++m_count;

    if (m_count == 1) 
    play(name);
}

void SpriteAnimator::addClipAuto(const char* name,
    const char* stripPath,
    int frameCount,
    float interval,
    bool looping,
    TextureManager& tm)
{
    sf::Texture& t = tm.load(stripPath);
    sf::Vector2u sz = t.getSize();
    if (sz.x == 0 || sz.y == 0 || frameCount <= 0)
    {
        return;
    }
    int fw = (int)(sz.x / (unsigned)frameCount);
    addClip(name, stripPath, AnimClip(0, (int)sz.y, fw, frameCount, interval, looping), tm);
}

void SpriteAnimator::addClipExternal(const char* name,
    sf::Texture& tex,
    int frameCount,
    float interval,
    bool looping)
{
    if (m_count >= SA_MAX_CLIPS) return;

    sf::Vector2u sz = tex.getSize();
    if (sz.x == 0 || sz.y == 0 || frameCount <= 0) return;

    int fw = (int)(sz.x / (unsigned)frameCount);

    ClipEntry& e = m_clips[m_count];
    e.tex   = &tex;
    e.clip  = AnimClip(0, (int)sz.y, fw, frameCount, interval, looping);
    e.valid = true;
    copyName(e.name, name);
    ++m_count;

    if (m_count == 1) play(name);
}


void SpriteAnimator::play(const char* name, bool force)
{
    int idx = findClip(name);
    if (idx == -1)
    {
        return;
    }
    if (idx == m_cur && !force)    
    return;

    m_cur = idx;
    m_frame = 0;
    m_timer = 0.f;
    m_done = false;

    if (m_clips[m_cur].tex)
        m_sprite.setTexture(*m_clips[m_cur].tex);

    applyRect();
}

void SpriteAnimator::restart()   
{
    if (m_cur < 0) return;
    m_frame = 0;
    m_timer = 0.f;
    m_done = false;
    applyRect();
}


void SpriteAnimator::update(float dt)
{
    if (m_cur < 0 || m_done) return;
    const AnimClip& c = m_clips[m_cur].clip;

    m_timer += dt;
    if (m_timer >= c.interval)
    {
        m_timer -= c.interval;
        ++m_frame;
        if (m_frame >= c.frameCount)
        {
            if (c.looping) m_frame = 0;
            else { m_frame = c.frameCount - 1; m_done = true; }
        }
        applyRect();  
    }
}

void SpriteAnimator::setPosition(float x, float y)   
{
    m_sprite.setPosition(x, y);
}

void SpriteAnimator::draw(sf::RenderWindow& rw) const
{
    if (!m_visible) return;
    if (m_cur >= 0 && m_clips[m_cur].tex)
        rw.draw(m_sprite);
}


void SpriteAnimator::setFlipX(bool flip)
{
    if (m_flipX == flip) return;
    m_flipX = flip;
    applyRect();
}


void SpriteAnimator::setVisible(bool v) { m_visible = v; }
bool SpriteAnimator::isVisible() const { return m_visible; }


bool  SpriteAnimator::isFinished() const { return m_done; }
int   SpriteAnimator::getFrame()   const { return m_frame; }
float SpriteAnimator::scaledW()    const
{
    if (m_cur < 0) return 0.f;
    return (float)m_clips[m_cur].clip.frameW * m_sx;
}
float SpriteAnimator::scaledH()    const
{
    if (m_cur < 0) return 0.f;
    return (float)m_clips[m_cur].clip.srcH * m_sy;
}
