#pragma once
#include "StraightProjectile.h"
#include "SpriteAnimator.h"

class TileMap;
class Bullet : public StraightProjectile
{
    private:
    bool isBentByFannum;
    bool meleeFlag;
    bool pierceShieldFlag;
    static sf::Texture s_tex;
    static bool        s_loaded;
    SpriteAnimator     m_anim;

    void ensureTexture();

    public:
    Bullet(Entity* shooter, int dmg, coordSyst dir, float spd, float range);
    virtual void update(TileMap& tm, float dt) override;
    void bendTowardTarget(coordSyst target, float radius, float dt);
    virtual void onImpact() override;
    SpriteAnimator* getRenderable() override { return &m_anim; }
    void render(sf::RenderWindow& rw) override;
    void setMelee(bool m) { meleeFlag = m; }
    bool isMeleeImpact() const override { return meleeFlag; }

    void setPiercesShield(bool b) { pierceShieldFlag = b; }
    bool isPiercingShield() const override { return pierceShieldFlag; }
};