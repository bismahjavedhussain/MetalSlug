#pragma once
#include "Enemy.h"




class Undead : public Enemy
{
public:
    Undead(int scoreVal, int hp) : Enemy(scoreVal, hp, false) {}
    virtual ~Undead() = default;
    void onPlayerContact(PlayerSoldier* p) override = 0;     
};
