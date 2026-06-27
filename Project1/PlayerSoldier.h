#pragma once
#include "Soldier.h"
#include "Inventory.h"
#include "SpriteAnimator.h"

class Weapon;
class Grenade;
class DamageSource;
class FusionCompanion;
class Projectile;
class TextureManager;
class InputHandler;



class PlayerSoldier : public Soldier
{
    const char* buildClipName(const char* suffix) const;

protected:
    int lives;
    int       saturationStat;
    bool      canMelee;
    float     fireRateMultiplier;
    float     speedMultiplier;
    float     meleeDamageMultiplier;
    float     ammoPickupMultiplier;
    float     blastRadiusMultiplier;
    float     powerUpTimer;
    bool      powerUpActive;
    float     fusionCooldownTimer;
    bool      fusionUsedInLevel;

    Inventory inventory;
    float     fireCooldown;
    float     invulnTimer;
    bool      inWaterCached;
    bool      m_isActiveSlot;
    float     respawnTimer;
    static const float RESPAWN_HUE_DURATION;

    SpriteAnimator  m_normal;
    SpriteAnimator  m_mummy;
    SpriteAnimator  m_undead;
    SpriteAnimator  m_fat;
    SpriteAnimator* m_active;



    float m_shootAnimTimer;
    float m_lastFireCooldown;
    float m_grenTimer;

    float saturationDrainTimer;
    static const float kSatDrainPeriod;

public:
    PlayerSoldier(int hp);
    virtual ~PlayerSoldier();
    virtual void specialPowerUp() = 0;
    virtual void onPowerUpExpire() {}

    virtual bool  dualFireWhilePoweredUp() const { return false; }
    virtual float superchargedFireRate()  const { return 1.0f;   }

    virtual float getVehicleFireRateMult()   const { return 1.0f; }
    virtual float getVehicleDurabilityMult() const { return 1.0f; }

    void respawn();
    virtual void throwGrenade();
    virtual void meleeAttack();
    virtual void pickupWeapon(Weapon* w);
    virtual void takeDamage(int amt, DamageSource* src) override;
    virtual bool onVehicleDestroyed();
    void checkSaturationTransition();
    Grenade* getGrenadePrototype();

    void attack() override;
    virtual void update(TileMap& tm, float dt) override;
    void handlePlayerInput(InputHandler& in, float dt);

    void render(sf::RenderWindow& rw) override;
    SpriteAnimator* getRenderable() override { return m_active; }

    bool isPlayer() const override { return true; }
    Inventory* getInventoryPtr() override { return &inventory; }

    float getSpeedMult() const override { return speedMultiplier; }
    void  setSpeedMult(float m) override { speedMultiplier = m; }

    void setActiveSlot(bool active);
    bool getIsActiveSlot() const { return m_isActiveSlot; }


    bool  isInRespawnWindow() const { return respawnTimer > 0.0f; }
    float getRespawnTimer()   const { return respawnTimer; }

    bool isRiding;
    int  getLives() const { return lives; }
    int  getSaturation() const { return saturationStat; }
    bool getPowerUpActive() const { return powerUpActive; }
    bool getIsRiding() const { return isRiding; }
    void setRiding(bool r) { isRiding = r; }
    Inventory& getInventory() { return inventory; }
    void addSaturation(int n);
    void addLives(int n);
    float getAmmoPickupMult() const { return ammoPickupMultiplier; }
    float getMeleeDamageMult() const { return meleeDamageMultiplier; }
    float getBlastRadiusMult() const { return blastRadiusMultiplier; }

    static const int PENDING_CAP = 4;
    Entity*     pendingProjectile;
    Entity*     pendingExtras[PENDING_CAP];
    int         pendingExtraCount;

    Entity*     takePendingProjectile();
    void        queueProjectile(Entity* p);
    Entity*     takeQueuedProjectile();
    PlayerSoldier* asPlayerSoldier() override { return this; }
};
