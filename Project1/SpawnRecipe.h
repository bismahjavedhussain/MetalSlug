#pragma once

class Entity;
class EntityManager;
class SurvivalLevel;


class SpawnRecipe
{
    float   triggerX;
    int     biomeIdx;
    int     count;
    bool    spawned;
    Entity* prototype;
    bool    isAerial;

public:
    SpawnRecipe(float tx, int biome, int n, Entity* proto, bool aerial = false);
    ~SpawnRecipe();

    bool  isSpawned()   const { return spawned; }
    float getTriggerX() const { return triggerX; }
    int   getBiomeIdx() const { return biomeIdx; }
    int   getCount()    const { return count;    }
    void  fire(EntityManager& em, SurvivalLevel& lvl);
};
