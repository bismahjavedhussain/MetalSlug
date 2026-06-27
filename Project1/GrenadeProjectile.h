#pragma once
#include "BallisticProjectile.h"
#include "SpriteAnimator.h"

class TileMap;

class GrenadeProjectile : public BallisticProjectile
{
protected:
    float blastRadius;
    int   bounces;

    static sf::Texture s_tex;
    static bool        s_loaded;
    SpriteAnimator     m_anim;
    void ensureTexture();

public:
    GrenadeProjectile(Entity* shooter, int dmg, coordSyst dir, float spd, float grav, float radius);
    virtual void update(TileMap& tm, float dt) override;
    virtual void onImpact() override;
    void bounceOnFloor();
    int  getBounces() const;
    bool isExplosiveImpact() const override { return true; }

    SpriteAnimator* getRenderable() override { return &m_anim; }
    void render(sf::RenderWindow& rw) override;
};
