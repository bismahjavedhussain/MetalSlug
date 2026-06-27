#include "ContactDamage.h"

ContactDamage::ContactDamage(Entity* c) : DamageSource(c) {}

int ContactDamage::amount() 
{
    return 1;
}