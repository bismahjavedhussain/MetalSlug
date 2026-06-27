#pragma once
#include "TransformationState.h"
class Soldier;
class MummyTransformState : public TransformationState
{
    public:
    MummyTransformState();
    void enter(Soldier* s) override;
    void exit(Soldier* s) override;
    void update(Soldier* s, float dt) override;

    const char* getAnimPrefix() const override { return "mummy"; }
};