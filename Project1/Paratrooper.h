#pragma once
#include "Infantry.h"
#include "TextureManager.h"

class ParatrooperKind;
class Paratrooper : public Infantry
{
private:
    bool             hasLanded;
    bool             isParachuting;
    ParatrooperKind* kind;
    float            descendSpeed;
    int              facingDir;
    Infantry*        landedSpawn;
    TextureManager*  tex;

public:
    Paratrooper(TextureManager& tm, float spawnX, float spawnTopY,
                ParatrooperKind* k, int batchId = 0);
    ~Paratrooper() override;

    void  update(TileMap& tm, float dt)              override;
    void  attack()                                   override;
    void  onDeath()                                  override;
    void  onLand();
    Enemy* clone()                                   override;

    Infantry* takeLandedSpawn();
    bool      hasParachuted() const { return hasLanded; }
    bool      isAerial() const override { return isParachuting && !hasLanded; }
    Paratrooper* asParatrooper() override { return this; }
    Entity* takePendingSpawn() override;
};
