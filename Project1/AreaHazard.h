#pragma once
#include "Entity.h"

class TileMap;
class AreaHazard : public Entity
{
protected:
    int   damagePerSecond;
    float duration;

public:
    AreaHazard(int dps, float dur);
    virtual ~AreaHazard() = default;

    virtual void update(TileMap& tm, float dt) override = 0;
    virtual void render(sf::RenderWindow& rw)  override;
    virtual bool isExpired() = 0;

    int   getDamagePerSecond() const { return damagePerSecond; }
    float getRemaining()       const { return duration; }

    AreaHazard* asAreaHazard() override { return this; }
};
