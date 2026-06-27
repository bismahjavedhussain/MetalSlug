#pragma once


class DamagableEntity;
class DamageState 
{
	protected:
	DamagableEntity* owner;
	float remainingTime;

	public:
	DamageState();
	virtual ~DamageState() = default;
	virtual void enter(DamagableEntity* entity);
	virtual void exit(DamagableEntity* entity);
	virtual void update(DamagableEntity* entity, float deltaTime);
	virtual float hueAlpha() = 0;
	virtual DamageState* next() = 0;
};