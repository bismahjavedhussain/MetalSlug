#include "Vehicle.h"
#include "PlayerSoldier.h"
#include "DamageState.h"
#include "NormalDamageState.h"
#include "DamageSource.h"
#include "SpriteAnimator.h"

Vehicle::Vehicle(int hp)
    : DamagableEntity(hp),
      pilot(nullptr), isOccupied(false),
      fireRate(0.25f), fireCooldown(0.0f)
{
    width  = 96.0f;
    height = 64.0f;
    currentDamageState = new NormalDamageState();
    currentDamageState->enter(this);
}

void Vehicle::enter(PlayerSoldier* p)
{
    if (p == nullptr || isOccupied) return;
    pilot = p;
    isOccupied = true;
}

PlayerSoldier* Vehicle::exit()
{
    PlayerSoldier* p = pilot;
    pilot = nullptr;
    isOccupied = false;
    return p;
}

void Vehicle::onDestroy()
{
    if (pilot != nullptr && isOccupied)
    {
        bool survives = pilot->onVehicleDestroyed();
        if (!survives)
        {
            int big = 99999;
            pilot->takeDamage(big, nullptr);
        }


        pilot->setPosition(position.x, position.y - 8.0f);
        pilot->setRiding(false);
        SpriteAnimator* a = pilot->getRenderable();
        if (a != nullptr) a->setVisible(true);
        pilot = nullptr;
        isOccupied = false;
    }
    isAlive = false;
}

void Vehicle::takeDamage(int amt, DamageSource* src)
{
    if (isInvelnerable || !isAlive) return;

    if (pilot != nullptr && isOccupied)
    {
        float dmult = pilot->getVehicleDurabilityMult();
        if (dmult > 1.0f)
        {
            float scaled = (float)amt / dmult;
            amt = (int)scaled;
            if (amt < 1 && scaled > 0.0f) amt = 1;
        }
    }

    DamagableEntity::takeDamage(amt, src);
    if (!isAlive) onDestroy();
}

void Vehicle::render(sf::RenderWindow& rw)
{
    m_anim.draw(rw);
}


void Vehicle::pilotInput(class InputHandler& , float ) {}
float Vehicle::pilotFireRateMult() const
{
    if (pilot != nullptr && isOccupied)
    {
        float m = pilot->getVehicleFireRateMult();
        if (m > 0.0f) return m;
    }
    return 1.0f;
}
