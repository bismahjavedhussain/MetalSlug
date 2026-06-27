#pragma once
#include "Entity.h"

class PlayerSoldier;
class InteractableObject : public Entity
{
public:
    virtual ~InteractableObject() = default;
    virtual void onInteract(PlayerSoldier* player) = 0;
};
