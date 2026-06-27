#pragma once
#include "Enemy.h"



class Alien : public Enemy
{
public:
    Alien(int scoreVal, int hp) : Enemy(scoreVal, hp, false) {}
    virtual ~Alien() = default;
    void attack() override = 0;
};
