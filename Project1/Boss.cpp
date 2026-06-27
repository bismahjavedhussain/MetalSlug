#include "Boss.h"
#include "EntityManager.h"
#include "FiringStrategy.h"
#include "Entity.h"





Boss::~Boss()
{
    if (minionPrototype != nullptr)
    {
        delete minionPrototype;
        minionPrototype = nullptr;
    }
    currentStrategy = nullptr;
}
Entity* Boss::takePendingShot()
{
    if (!hasPendingShot || currentStrategy == nullptr) return nullptr;
    Entity* shot = currentStrategy->produce(this, pendingShotOrigin, pendingShotAim);
    hasPendingShot = false;
    return shot;
}
Entity* Boss::takePendingSpawn()
{
    if (Entity* shot = takePendingShot()) return shot;
    return Enemy::takePendingSpawn();
}

void Boss::spawnMinions(EntityManager* em)
{
    if (em == nullptr || minionPrototype == nullptr) return;

    int n = minionBatchSize;
    if (n < 2) n = 2;
    if (n > 4) n = 4;

    coordSyst origin = position;
    for (int i = 0; i < n; ++i)
    {
        Enemy* clone = minionPrototype->clone();
        if (clone == nullptr) continue;


        float sx = origin.x + (float)i * 80.0f - (float)(n - 1) * 40.0f;
        coordSyst protoPos = minionPrototype->getPosition();
        clone->setPosition(sx, protoPos.y > 0.0f ? protoPos.y : origin.y);

        em->addEntity(clone);
    }
}
