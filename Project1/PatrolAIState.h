#pragma once
#include "EnemyAIState.h"


class PatrolAIState : public EnemyAIState
{
    float patrolSpeed;
    int   facingSign;

public:
    PatrolAIState();
    void enter(Enemy* e)                              override;
    void exit(Enemy* e)                               override;
    void update(Enemy* e, TileMap& tm, float dt)      override;
};
