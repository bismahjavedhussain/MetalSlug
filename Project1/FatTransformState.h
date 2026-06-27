#pragma once
#include "TransformationState.h"
class FatTransformState : public TransformationState {
private:
    float fannumRadius;
    bool isBulletMagnet;
    public:
    FatTransformState();
    void enter(Soldier* s) override;
    void exit(Soldier* s) override;
    void update(Soldier* s, float dt) override;
    void getMagnetism(float& out_radius, bool& out_active);

    const char* getAnimPrefix() const override { return "fat"; }
};