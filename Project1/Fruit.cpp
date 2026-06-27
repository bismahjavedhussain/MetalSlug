#include "Fruit.h"
#include "PlayerSoldier.h"
#include "EntityAnims.h"

Fruit::Fruit(TextureManager& tm, float spawnX, float spawnY)
    : Collectible(), saturationRestore(2)
{
    setupFruitAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 24.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 24.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void Fruit::onPickup(PlayerSoldier* p, PlayState& )
{
    if (p == nullptr || consumed) return;
    p->addSaturation(saturationRestore);
    consumed = true;
    isAlive  = false;
}
