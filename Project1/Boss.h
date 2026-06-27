#pragma once

#include "Enemy.h"
#include "coordSyst.h"

class EntityManager;
class FiringStrategy;


class Boss : public Enemy
{
protected:
    float retreatThreshold;
    bool  hasRetreated;
    int   minionBatchSize;

    Enemy* minionPrototype;

    FiringStrategy* currentStrategy;
    coordSyst       pendingShotOrigin;
    coordSyst       pendingShotAim;
    bool            hasPendingShot;

    bool wantsMinionBatch;
    bool wantsCrateDrop;
    float chaseTargetX;
    bool  hasChaseTarget;

public:
    Boss(int   scoreVal,
         int   hp,
         float threshold   = 0.5f,
         int   minionBatch = 3)
        : Enemy(scoreVal, hp, false),
          retreatThreshold(threshold),
          hasRetreated(false),
          minionBatchSize(minionBatch),
          minionPrototype(nullptr),
          currentStrategy(nullptr),
          hasPendingShot(false),
          wantsMinionBatch(false),
          wantsCrateDrop(false),
          chaseTargetX(0.0f),
          hasChaseTarget(false) {}


    virtual ~Boss();
    virtual bool checkRetreat()
    {
        if (hasRetreated) return true;
        if (maxHealthPoints > 0)
        {
            float hpFrac = (float)healthPoints / (float)maxHealthPoints;
            if (hpFrac <= retreatThreshold)
            {
                hasRetreated = true;
                return true;
            }
        }
        return false;
    }

    virtual void spawnMinions(EntityManager* em);

    bool getHasRetreated()    const { return hasRetreated; }
    int  getMinionBatchSize() const { return minionBatchSize; }
    virtual void setChaseTarget(float x)
    {
        chaseTargetX   = x;
        hasChaseTarget = true;
    }
    virtual class Entity* takePendingShot();
    Entity* takePendingSpawn() override;
    virtual bool consumeMinionRequest()
    {
        bool b = wantsMinionBatch; wantsMinionBatch = false; return b;
    }
    virtual bool consumeCrateRequest()
    {
        bool b = wantsCrateDrop; wantsCrateDrop = false; return b;
    }
    virtual void requestCrateDrop() { wantsCrateDrop = true; }

    Boss* asBoss() override { return this; }
};
