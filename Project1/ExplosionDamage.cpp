#include "ExplosionDamage.h"
ExplosionDamage::ExplosionDamage(Entity* c, float r) : DamageSource(c), radius(r) {}
int ExplosionDamage::amount() 
{ 
	return 5;
}
bool ExplosionDamage::canKillMummy()
{ 
	return true;
}
bool ExplosionDamage::isExplosive() 
{ 
	return true;
}