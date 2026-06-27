#pragma once
#include "Entity.h"

class DamageState;
class DamageSource;
class DamagableEntity : public Entity
{
	protected:
	int healthPoints;
	int maxHealthPoints;
	bool isInvelnerable;
	DamageState* currentDamageState;


	bool m_canFire;

	public:
	DamagableEntity(int startHealthPoint);

	DamagableEntity(const DamagableEntity& other);
	DamagableEntity& operator=(const DamagableEntity& other);

	virtual void takeDamage (int amount, DamageSource* src);
	void virtual die ();

	int getHealth() const;
	void setHealth(int healthPoints);



	int getMaxHealth() const { return maxHealthPoints; }



	void setMaxHealth(int newMax);
	DamageState* getDamageState ();
	void advanceDamageState();
	virtual ~DamagableEntity();


	DamagableEntity* asDamagableEntity() override { return this; }


	bool getCanFire() const { return m_canFire; }
	void setCanFire(bool b) { m_canFire = b; }
};