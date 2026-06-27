#pragma once

class Enemy;
class TileMap;
class EnemyAIState
{
protected:
    Enemy* owner;

public:
    EnemyAIState() : owner(nullptr) {}
    virtual ~EnemyAIState() = default;
    virtual void enter(Enemy* e)                              = 0;
    virtual void exit(Enemy* e)                               = 0;
    virtual void update(Enemy* e, TileMap& tm, float dt)      = 0;
};
