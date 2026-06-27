#pragma once
#include "TransformationState.h"
class Soldier;
class UndeadTransformState : public TransformationState
{
    public:
    UndeadTransformState();
    void enter(Soldier* s) override;
    void exit(Soldier* s) override;
    void update(Soldier* s, float dt) override;

    const char* getAnimPrefix() const override { return "undead"; }
};