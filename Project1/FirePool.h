#pragma once
#include "AreaHazard.h"
#include "SpriteAnimator.h"




class FirePool : public AreaHazard
{
private:
    float radius;
    float damageAccum;

    static sf::Texture s_tex;
    static bool        s_loaded;
    SpriteAnimator     m_anim;
    void ensureTexture();

public:
    FirePool(coordSyst centre, float radius, float duration);

    void update(TileMap& tm, float dt) override;
    void render(sf::RenderWindow& rw)  override;
    bool isExpired()                   override;

    float getRadius() const { return radius; }

    SpriteAnimator* getRenderable() override { return &m_anim; }
};
