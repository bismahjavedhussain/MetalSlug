#include "POWPrisoner.h"
#include "SupplyCrate.h"
#include "PlayState.h"
#include "EntityManager.h"
#include "EntityAnims.h"

POWPrisoner::POWPrisoner(TextureManager& tm, float spawnX, float spawnY, unsigned seed)
    : Collectible(), crateSeed(seed), texMgr(&tm)
{
    setupPOWPrisonerAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 28.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 56.0f;
    position.x = spawnX;
    position.y = spawnY;
}


void POWPrisoner::onPickup(PlayerSoldier* , PlayState& ps)
{
    if (consumed) return;

    EntityManager* em = ps.getEntityManager();
    if (em != nullptr && texMgr != nullptr)
    {
        em->addEntity(new SupplyCrate(*texMgr,
                                      position.x,
                                      position.y + height - 32.0f,
                                      crateSeed));
    }

    consumed = true;
    isAlive  = false;
}


Entity* POWPrisoner::clone()
{
    return new POWPrisoner(*this);
}
