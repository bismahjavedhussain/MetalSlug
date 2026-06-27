#include "FireDamage.h"

FireDamage::FireDamage(Entity* c) : DamageSource(c) {}
int FireDamage::amount()
{ 
	return 2;
}
bool FireDamage::canKillMummy() 
{ 
	return true;
}