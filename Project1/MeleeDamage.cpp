#include "MeleeDamage.h"

MeleeDamage::MeleeDamage(Entity* c) : DamageSource(c) {}
int MeleeDamage::amount() 
{ 
	return 2;
}