#pragma once
class Soldier; 

class TransformationState
{
    protected:
    Soldier* owner;
    float duration;
    public:
    TransformationState(float dur = 0.0f);
    virtual ~TransformationState() = default;

    virtual void enter(Soldier* s) = 0;
    virtual void exit(Soldier* s) = 0;
    virtual void update(Soldier* s, float dt) = 0;





    virtual const char* getAnimPrefix() const { return ""; }
};
