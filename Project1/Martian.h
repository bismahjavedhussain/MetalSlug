#pragma once
#include "Alien.h"
#include "TextureManager.h"

class Martian : public Alien
{
private:
    int   phase;
    bool  hasPod;
    float fireCooldown;
    int   facingDir;

public:
    Martian(TextureManager& tm, float spawnX, float spawnY);
    ~Martian() override = default;

    void  update(TileMap& tm, float dt)              override;
    void  attack()                                   override;
    void  onDeath()                                  override;
    void  transitionToPhase2();
    Enemy* clone()                                   override;
};
