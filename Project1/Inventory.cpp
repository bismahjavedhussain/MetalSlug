#include "Inventory.h"
#include "Pistol.h"
#include "Knife.h"
#include "Grenade.h"
#include "FatPistol.h"


Inventory::Inventory()
{
    defaultPistol = new Pistol();

    knife = new Knife();

    currentWeaponInHand = defaultPistol;


    grenadePrototype = nullptr;
    grenadeCount = 10;

    savedWeaponBeforeSwap = nullptr;
    inForcedSwap          = false;
}


Inventory::~Inventory()
{
    if (currentWeaponInHand != nullptr && currentWeaponInHand != defaultPistol)
    {
       delete currentWeaponInHand;
    }

    if (savedWeaponBeforeSwap != nullptr &&
        savedWeaponBeforeSwap != defaultPistol &&
        savedWeaponBeforeSwap != currentWeaponInHand)
    {
        delete savedWeaponBeforeSwap;
    }
    delete defaultPistol;
    delete knife;

    if (grenadePrototype != nullptr)
    {
        delete grenadePrototype;
    }
}

void Inventory::pickupWeapon(Weapon* w)
{

    if (inForcedSwap)
    {
        if (savedWeaponBeforeSwap != nullptr && savedWeaponBeforeSwap != defaultPistol)
            delete savedWeaponBeforeSwap;
        savedWeaponBeforeSwap = w;
        return;
    }

    if (currentWeaponInHand != defaultPistol)
    {
        delete currentWeaponInHand;
    }
    currentWeaponInHand = w;
}

Weapon* Inventory::getCurrentWeapon() const
{
    return currentWeaponInHand;
}

bool Inventory::hasWeapon() 
{
    return (currentWeaponInHand != defaultPistol);
}

void Inventory::revertToPistol()
{
    if (inForcedSwap)
    {
        if (savedWeaponBeforeSwap != nullptr && savedWeaponBeforeSwap != defaultPistol)
            delete savedWeaponBeforeSwap;
        savedWeaponBeforeSwap = defaultPistol;
        return;
    }
    if (currentWeaponInHand != defaultPistol)
    {
        delete currentWeaponInHand;
        currentWeaponInHand = defaultPistol;
    }
}

void Inventory::setGrenadePrototype(Grenade* g)
{
    if (grenadePrototype != nullptr) 
    {
        delete grenadePrototype;
    }
    grenadePrototype = g;
}

Grenade* Inventory::getGrenadePrototype() 
{
    return grenadePrototype;
}

int Inventory::getGrenadeCount()
{
    return grenadeCount;
}

void Inventory::addGrenades(int n)
{
    grenadeCount += n;
}

Grenade* Inventory::consumeGrenade()
{
    if (grenadeCount > 0 && grenadePrototype != nullptr)
    {
        grenadeCount--;
        return grenadePrototype->clone();
    }


    return nullptr;
}

void Inventory::forceKnifeOnly()
{
    if (inForcedSwap) return;
    savedWeaponBeforeSwap = currentWeaponInHand;
    currentWeaponInHand   = nullptr;
    inForcedSwap          = true;
}

void Inventory::restoreSavedWeapon()
{
    if (!inForcedSwap) return;
    if (currentWeaponInHand != nullptr && currentWeaponInHand != defaultPistol &&
        currentWeaponInHand != savedWeaponBeforeSwap)
    {
        delete currentWeaponInHand;
    }
    currentWeaponInHand   = savedWeaponBeforeSwap;
    savedWeaponBeforeSwap = nullptr;
    inForcedSwap          = false;
}
void Inventory::equipFatPistol()
{
    if (inForcedSwap) return;
    savedWeaponBeforeSwap = currentWeaponInHand;
    currentWeaponInHand   = new FatPistol();
    inForcedSwap          = true;
}

void Inventory::restoreFromFatPistol()
{

    restoreSavedWeapon();
}