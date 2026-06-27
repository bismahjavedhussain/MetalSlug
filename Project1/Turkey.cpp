#include "Turkey.h"
#include "PlayerSoldier.h"
#include "EntityAnims.h"

Turkey::Turkey(TextureManager& tm, float spawnX, float spawnY)
    : Collectible(), saturationRestore(3)
{
    setupTurkeyAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 24.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 24.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void Turkey::onPickup(PlayerSoldier* p, PlayState& )
{
    if (p == nullptr || consumed) return;
    p->addSaturation(saturationRestore);
    consumed = true;
    isAlive  = false;
}
