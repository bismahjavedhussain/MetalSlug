#pragma once

#include "coordSyst.h"

class Entity;

class FiringStrategy
{
public:
    virtual ~FiringStrategy() = default;




    virtual Entity* produce(Entity* shooter, coordSyst origin, coordSyst aim) = 0;
};

class RocketFiringStrategy : public FiringStrategy
{
public:
    Entity* produce(Entity* shooter, coordSyst origin, coordSyst aim) override;
};

class HMGFiringStrategy : public FiringStrategy
{
public:
    Entity* produce(Entity* shooter, coordSyst origin, coordSyst aim) override;
};

class FireBombFiringStrategy : public FiringStrategy
{
public:
    Entity* produce(Entity* shooter, coordSyst origin, coordSyst aim) override;
};

class FlameStreamFiringStrategy : public FiringStrategy
{
public:
    Entity* produce(Entity* shooter, coordSyst origin, coordSyst aim) override;
};
