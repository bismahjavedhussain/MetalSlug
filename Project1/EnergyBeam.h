#pragma once
#include "StraightProjectile.h"
#include "SpriteAnimator.h"

class TileMap;

class EnergyBeam : public StraightProjectile
{
    private:
    float range;
    float lifetime;
    bool  isInstantKill;
    static sf::Texture s_tex;
    static bool        s_loaded;
    SpriteAnimator     m_anim;
    void ensureTexture();
    public:
    EnergyBeam(Entity* shooter, int dmg, coordSyst dir, float spd, float rng, float life, bool instantKill);
    virtual void update(TileMap& tm, float dt) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual void onImpact() override;

    SpriteAnimator* getRenderable() override { return &m_anim; }
};
