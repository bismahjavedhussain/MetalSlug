#include "BulletDamage.h"

BulletDamage::BulletDamage(Entity* c) : DamageSource(c) {}
int BulletDamage::amount()
{ 
	return 3; 
}