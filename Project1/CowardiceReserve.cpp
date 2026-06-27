#include "CowardiceReserve.h"
#include "Enemy.h"


const float CowardiceReserve::SPAWN_INTERVAL = 7.0f;
const float CowardiceReserve::SKIP_MARGIN    = 800.0f;
const float CowardiceReserve::RESPAWN_MARGIN = 96.0f;

CowardiceReserve::CowardiceReserve()
    : head(0), count(0), spawnTimer(SPAWN_INTERVAL)
{
    for (int i = 0; i < MAX_RESERVED; ++i) 
    slots[i] = nullptr;
}

void CowardiceReserve::enqueue(Enemy* e)
{
    if (e == nullptr)
     return;
    if (count >= MAX_RESERVED)
     return;
    int tail = (head + count) % MAX_RESERVED;
    slots[tail] = e;
    ++count;
}

Enemy* CowardiceReserve::dequeue()
{
    if (count <= 0)
     return nullptr;
    Enemy* e = slots[head];
    slots[head] = nullptr;
    head = (head + 1) % MAX_RESERVED;
    --count;
    return e;
}

bool CowardiceReserve::tickSpawnReady(float dt)
{
    if (count <= 0)
    {
        spawnTimer = SPAWN_INTERVAL;
        return false;
    }

    spawnTimer -= dt;
    if (spawnTimer <= 0.0f)
    {
        spawnTimer = SPAWN_INTERVAL;
        return true;
    }
    return false;
}
