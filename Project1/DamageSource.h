#pragma once


class Entity;
class DamageSource
{
    protected:
    Entity* cause;
    public:
    DamageSource(Entity* c = nullptr);
    virtual ~DamageSource() = default;

    virtual int amount() = 0;
    virtual bool canKillMummy();
    virtual bool isExplosive();
};