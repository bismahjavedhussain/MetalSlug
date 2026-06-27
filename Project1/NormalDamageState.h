#pragma once
#include "DamageState.h"

class InjuryState;
class NormalDamageState : public DamageState
{
	public:
	NormalDamageState();
	virtual ~NormalDamageState() = default;
	virtual void enter(DamagableEntity* entity) override;
	virtual float hueAlpha() override;
	virtual DamageState* next() override;
};