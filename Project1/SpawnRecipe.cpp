#include "SpawnRecipe.h"
#include "Entity.h"
#include "EntityManager.h"
#include "SurvivalLevel.h"


static const float ROW_SPACING_PX = 80.0f;

SpawnRecipe::SpawnRecipe(float tx, int biome, int n, Entity* proto, bool aerial)
    : triggerX(tx), biomeIdx(biome), count(n),
      spawned(false), prototype(proto), isAerial(aerial)
{
    if (count < 1) count = 1;
}

SpawnRecipe::~SpawnRecipe()
{
    if (prototype != nullptr) { delete prototype; prototype = nullptr; }
}

void SpawnRecipe::fire(EntityManager& em, SurvivalLevel& lvl)
{
    if (spawned) return;
    if (prototype == nullptr) { spawned = true; return; }

    for (int i = 0; i < count; ++i)
    {
        Entity* clone = prototype->clone();
        if (clone == nullptr) continue;

        float spawnX = triggerX + ROW_SPACING_PX * (float)i;


        clone->setPosition(spawnX, clone->getPosition().y);

        if (!isAerial) lvl.placeOnGround(clone, biomeIdx);

        em.addEntity(clone);
    }
    spawned = true;
}
