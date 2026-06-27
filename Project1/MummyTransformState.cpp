#include "MummyTransformState.h"
#include "NormalTransformState.h"
#include "Soldier.h"
#include "PlayerSoldier.h"
#include "Inventory.h"

MummyTransformState::MummyTransformState() : TransformationState(10.0f) {}

void MummyTransformState::enter(Soldier* s)
{
    owner = s;
    if (s == nullptr) return;



    Inventory* inv = s->getInventoryPtr();
    if (inv != nullptr) inv->forceKnifeOnly();
}

void MummyTransformState::exit(Soldier* s)
{
    if (s == nullptr) return;
    Inventory* inv = s->getInventoryPtr();
    if (inv != nullptr) inv->restoreSavedWeapon();
}

void MummyTransformState::update(Soldier* s, float dt)
{
    duration -= dt;
    if (duration <= 0.0f)
    {
        s->changeState(new NormalTransformState());
    }
}