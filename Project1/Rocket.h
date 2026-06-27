#pragma once
#include "StraightProjectile.h"
#include "SpriteAnimator.h"

class TileMap;

class Rocket : public StraightProjectile
{
    private:
    float blastRadius;

    static sf::Texture s_tex;
    static bool        s_loaded;
    SpriteAnimator     m_anim;
    void ensureTexture();

    public:
    Rocket(Entity* shooter, int dmg, coordSyst dir, float spd, float range, float bRadius);
    virtual void update(TileMap& tm, float dt) override;
    virtual void onImpact() override;
    bool isExplosiveImpact() const override { return true; }

    SpriteAnimator* getRenderable() override { return &m_anim; }
    void render(sf::RenderWindow& rw) override;
};
