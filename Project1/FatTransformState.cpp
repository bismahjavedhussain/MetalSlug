#include "FatTransformState.h"
#include "Soldier.h"
#include "Inventory.h"

FatTransformState::FatTransformState() : TransformationState(0.0f)
{
    fannumRadius = 300.0f;
    isBulletMagnet = true;

}

void FatTransformState::enter(Soldier* s)
{
    owner = s;
    if (s == nullptr) return;

    Inventory* inv = s->getInventoryPtr();
    if (inv != nullptr) inv->equipFatPistol();

    s->setSpeedMult(s->getSpeedMult() * 0.7f);
}

void FatTransformState::exit(Soldier* s)
{
    isBulletMagnet = false;
    if (s == nullptr) return;

    Inventory* inv = s->getInventoryPtr();
    if (inv != nullptr) inv->restoreFromFatPistol();

    s->setSpeedMult(s->getSpeedMult() / 0.7f);
}
void FatTransformState::update(Soldier* s, float dt) {  }

void FatTransformState::getMagnetism(float& out_radius, bool& out_active)
{
    out_radius = fannumRadius;
    out_active = isBulletMagnet;
}