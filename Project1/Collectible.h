#pragma once
#include "Entity.h"
#include "SpriteAnimator.h"

class PlayerSoldier;
class PlayState;
class Collectible : public Entity
{
protected:
    bool consumed;
    SpriteAnimator m_anim;

public:
    Collectible();
    virtual ~Collectible() = default;
    virtual void onPickup(PlayerSoldier* p, PlayState& ps) = 0;
    virtual bool requiresKeyPress() const { return false; }

    virtual void update(TileMap& tm, float dt) override;
    virtual void render(sf::RenderWindow& rw)  override;
    SpriteAnimator* getRenderable() override { return &m_anim; }
    bool isConsumed() const { return consumed; }
    Collectible* asCollectible() override { return this; }
};
