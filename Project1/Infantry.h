#pragma once
#include "Enemy.h"


class Infantry : public Enemy
{
protected:
    int batchId;

public:
    Infantry(int scoreVal, int hp, int batch)
        : Enemy(scoreVal, hp, false), batchId(batch) {}
    virtual ~Infantry() = default;

    int getBatchId() const { return batchId; }
};
