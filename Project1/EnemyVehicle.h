#pragma once
#include "Vehicle.h"


class EnemyVehicle : public Vehicle
{
protected:
    bool movesHorizontally;
    int  scoreValue;

public:
    EnemyVehicle(int hp, bool horizMover, int scoreVal = 100)
        : Vehicle(hp), movesHorizontally(horizMover), scoreValue(scoreVal) {}
    virtual ~EnemyVehicle() = default;
    Entity* fire(coordSyst ) override { return nullptr; }
    void onDestroy() override;
    void die() override;
    int  getScoreValue() const { return scoreValue; }
    bool movesHoriz()    const { return movesHorizontally; }
};
