#pragma once



class Weapon;
class Pistol;
class Knife;
class Grenade;
class FatPistol;

class Inventory
{
    private:
    Weapon* currentWeaponInHand;
    Pistol* defaultPistol;
    Knife* knife;
    Grenade* grenadePrototype;
    int grenadeCount;
    Weapon* savedWeaponBeforeSwap;
    bool    inForcedSwap;

    public:
    Inventory();
    ~Inventory();

    void pickupWeapon(Weapon* w);
    Weapon* getCurrentWeapon() const;
    Knife*  getKnife() { return knife; }


    bool hasWeapon();
    void revertToPistol();

    void forceKnifeOnly();
    void restoreSavedWeapon();
    void equipFatPistol();
    void restoreFromFatPistol();

    void setGrenadePrototype(Grenade* g);
    Grenade* getGrenadePrototype();
    int getGrenadeCount();
    void addGrenades(int n);

    Grenade* consumeGrenade();
};