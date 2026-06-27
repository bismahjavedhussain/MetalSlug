#include "DamageSource.h"

DamageSource::DamageSource(Entity* c) : cause(c) {}

bool DamageSource::canKillMummy() 
{ 
	return false; 
}
bool DamageSource::isExplosive() 
{ 
	return false; 
}