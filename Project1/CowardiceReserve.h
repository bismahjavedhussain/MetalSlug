#pragma once

class Enemy;
class CowardiceReserve
{
    static const int MAX_RESERVED = 64;

    Enemy* slots[MAX_RESERVED];
    int    head;
    int    count;
    float  spawnTimer;

public:
    static const float SPAWN_INTERVAL;
    static const float SKIP_MARGIN;
    static const float RESPAWN_MARGIN;

    CowardiceReserve();

    bool isEmpty() const { return count <= 0; }
    int  getCount() const { return count; }
    void enqueue(Enemy* e);
    Enemy* dequeue();
    bool tickSpawnReady(float dt);
};
