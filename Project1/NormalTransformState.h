#pragma once
#include "TransformationState.h"

class NormalTransformState : public TransformationState
{
    public:
    NormalTransformState();
    void enter(Soldier* s) override;
    void exit(Soldier* s) override;
    void update(Soldier* s, float dt) override;

    const char* getAnimPrefix() const override { return ""; }
};