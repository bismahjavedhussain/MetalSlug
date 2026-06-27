#pragma once
#include "AreaHazard.h"
#include "SpriteAnimator.h"

class Direction;
class FireStream : public AreaHazard
{
private:
    float streamLength;
    Direction*  direction;

    static sf::Texture s_tex;
    static bool        s_loaded;
    SpriteAnimator     m_anim;
    void ensureTexture();

public:
    FireStream(coordSyst origin, Direction* dir, float length);
    ~FireStream() override;

    void update(TileMap& tm, float dt) override;
    void render(sf::RenderWindow& rw)  override;
    bool isExpired()                   override;
    void deactivate();

    float getLength() const { return streamLength; }
    int   facingSign() const;

    SpriteAnimator* getRenderable() override { return &m_anim; }
};
