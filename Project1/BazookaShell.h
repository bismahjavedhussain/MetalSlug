#pragma once
#include "BallisticProjectile.h"
#include "SpriteAnimator.h"

class BazookaShell : public BallisticProjectile
{
private:
    float blastRadius;
    static sf::Texture s_tex;
    static bool        s_loaded;
    SpriteAnimator     m_anim;
    void ensureTexture();

public:
    BazookaShell(Entity* shooter, int dmg, coordSyst dir, float spd, float grav, float bRadius);
    virtual void onImpact() override;
    bool isExplosiveImpact() const override { return true; }

    SpriteAnimator* getRenderable() override { return &m_anim; }
    void render(sf::RenderWindow& rw) override;
};
