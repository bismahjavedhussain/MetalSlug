#include "Knife.h"
#include "Bullet.h"
#include "Soldier.h"


Knife::Knife() : Weapon(2, -1, 0.5f, -1), meleeRange(32.0f), meleeCooldown(0.5f) {}
Entity* Knife::fire(Soldier* owner, coordSyst aim)
{
    Bullet* b = new Bullet(owner, damage, aim, 1200.0f, meleeRange);
    b->setMelee(true);
    if (owner != nullptr)
    {
        if (owner->meleePiercesShield()) b->setPiercesShield(true);

        coordSyst op = owner->getPosition();
        float ox = (aim.x < 0.0f) ? op.x - 4.0f
                                  : op.x + owner->getWidth() + 4.0f;
        float oy = op.y + owner->getHeight() * 0.40f;
        b->setPosition(ox, oy);
    }
    return b;
}

Weapon* Knife::clone()
{
    return new Knife(*this);
}
