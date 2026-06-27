#include "PlayerSoldier.h"
#include "Weapon.h"
#include "Knife.h"
#include "Grenade.h"
#include "TileMap.h"
#include "Tile.h"
#include "DamageSource.h"
#include "DamageState.h"
#include "NormalDamageState.h"
#include "TransformationState.h"
#include "NormalTransformState.h"
#include "FatTransformState.h"
#include "InputHandler.h"
#include "Projectile.h"
#include "Direction.h"
#include "HandGrenadePrototype.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>


const float PlayerSoldier::RESPAWN_HUE_DURATION = 3.0f;
const float PlayerSoldier::kSatDrainPeriod = 4.0f;

PlayerSoldier::PlayerSoldier(int hp)
    : Soldier(hp),
      lives(2),
      saturationStat(0),
      canMelee(true),
      fireRateMultiplier(1.0f),
      speedMultiplier(1.0f),
      meleeDamageMultiplier(1.0f),
      ammoPickupMultiplier(1.0f),
      blastRadiusMultiplier(1.0f),
      powerUpTimer(0.0f),
      powerUpActive(false),
      fusionCooldownTimer(0.0f),
      fusionUsedInLevel(false),
      fireCooldown(0.0f),
      invulnTimer(1.5f),
      pendingProjectile(nullptr),
      pendingExtraCount(0),
      isRiding(false),
      inWaterCached(false),
      m_isActiveSlot(true),
      respawnTimer(0.0f),
      m_active(&m_normal),
      m_shootAnimTimer(0.0f),
      m_lastFireCooldown(0.0f),
      m_grenTimer(0.0f),
      saturationDrainTimer(kSatDrainPeriod)
{
    width  = 40.0f;
    height = 64.0f;
    for (int i = 0; i < PENDING_CAP; ++i) pendingExtras[i] = nullptr;
    currentDamageState = new NormalDamageState();
    currentDamageState->enter(this);



    inventory.setGrenadePrototype(new HandGrenadePrototype());
}

void PlayerSoldier::addSaturation(int n)
{
    saturationStat += n;
    if (saturationStat < 0) saturationStat = 0;
    checkSaturationTransition();
}

void PlayerSoldier::addLives(int n)
{
    lives += n;
    if (lives < 0) lives = 0;
}

PlayerSoldier::~PlayerSoldier()
{
    if (pendingProjectile != nullptr)
    {
        delete pendingProjectile;
        pendingProjectile = nullptr;
    }
    for (int i = 0; i < pendingExtraCount; ++i)
    {
        if (pendingExtras[i] != nullptr) { delete pendingExtras[i]; pendingExtras[i] = nullptr; }
    }
    pendingExtraCount = 0;
}



void PlayerSoldier::attack()
{
    m_shootAnimTimer = 0.4f;
}


void PlayerSoldier::respawn()
{
    lives -= 1;
    if (lives > 0)
    {
        healthPoints   = maxHealthPoints;
        isAlive        = true;
        invulnTimer    = 1.5f;
        isInvelnerable = true;

        if (currentDamageState != nullptr) delete currentDamageState;
        currentDamageState = new NormalDamageState();
        currentDamageState->enter(this);
        saturationStat       = 0;
        saturationDrainTimer = kSatDrainPeriod;
        changeState(new NormalTransformState());
    }
    else
    {



        if (lives < 0) lives = 0;
    }
}

void PlayerSoldier::throwGrenade()
{
    Grenade* g = inventory.consumeGrenade();
    if (g == nullptr) return;
    m_grenTimer = 0.6f;
    float rad = aimAngle * 3.14159265f / 180.0f;
    int   sgn = (facing != nullptr) ? facing->getXSign() : +1;
    coordSyst aim((float)sgn * std::cos(rad), -std::sin(rad) - 0.4f);

    Projectile* p = g->spawnProjectile(this, aim);
    if (p != nullptr) queueProjectile(p);
    delete g;
}

void PlayerSoldier::meleeAttack()
{
    if (!canMelee) return;



    if (m_active != nullptr) m_active->play("melee_prep", true);

    Knife* k = inventory.getKnife();
    if (k == nullptr) return;
    int sgn = (facing != nullptr) ? facing->getXSign() : +1;
    coordSyst aim((float)sgn, 0.0f);
    Entity* spawned = k->fire(this, aim);
    if (spawned != nullptr) queueProjectile(spawned);
}

void PlayerSoldier::pickupWeapon(Weapon* w)
{
    inventory.pickupWeapon(w);
}

void PlayerSoldier::takeDamage(int amt, DamageSource* src)
{
    Soldier::takeDamage(amt, src);
    if (!isAlive && respawnTimer <= 0.0f)
    {
        lives -= 1;
        if (lives < 0) lives = 0;
        respawnTimer = RESPAWN_HUE_DURATION;
    }
}

bool PlayerSoldier::onVehicleDestroyed()
{
    return false;
}

void PlayerSoldier::checkSaturationTransition()
{
    const char* p = (currentTransformState != nullptr)
                        ? currentTransformState->getAnimPrefix()
                        : "";
    bool isFatNow = (p[0] == 'f');

    if (saturationStat > 5 && !isFatNow)
    {
        changeState(new FatTransformState());
    }
    else if (saturationStat <= 0 && isFatNow)
    {
        changeState(new NormalTransformState());
    }
}

Grenade* PlayerSoldier::getGrenadePrototype()
{
    return inventory.getGrenadePrototype();
}

void PlayerSoldier::setActiveSlot(bool active)
{
    m_isActiveSlot = active;
    if (!active)
    {
        isInvelnerable = true;
    }
    else
    { if (invulnTimer <= 0.0f) 
        isInvelnerable = false;
    }
}

void PlayerSoldier::update(TileMap& tm, float dt)
{
    if (respawnTimer > 0.0f)
    {
        respawnTimer -= dt;
        if (respawnTimer <= 0.0f)
        {
            respawnTimer = 0.0f;
            if (lives > 0)
            {
                healthPoints   = maxHealthPoints;
                isAlive        = true;
                isInvelnerable = true;
                invulnTimer    = 1.5f;
                if (currentDamageState != nullptr) delete currentDamageState;
                currentDamageState = new NormalDamageState();
                currentDamageState->enter(this);
            }


        }
    }
    if (!m_isActiveSlot) return;
    if (!isAlive)        return;

    if (isRiding)
    {
        if (currentDamageState != nullptr)
            currentDamageState->update(this, dt);
        if (powerUpActive)
        {
            powerUpTimer -= dt;
            if (powerUpTimer <= 0.0f) { powerUpActive = false; onPowerUpExpire(); }
        }
        return;
    }

    int ts = tm.getTileSize();
    int cgx = (int)((position.x + width  * 0.5f) / ts);
    int cgy = (int)((position.y + height * 0.5f) / ts);
    Tile* here = tm.getTile(cgx, cgy);
    bool inWater = (here != nullptr && here->isWater());
    inWaterCached = inWater;
  const float AIR_GRAVITY   = 1400.0f;
    const float WATER_GRAVITY = 900.0f;
    velocity.y += (inWater ? WATER_GRAVITY : AIR_GRAVITY) * dt;
    if (velocity.y > 1500.0f) velocity.y = 1500.0f;
    if (inWater && velocity.y > 260.0f) velocity.y = 260.0f;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;


    if (position.x < 0.0f) position.x = 0.0f;
    float maxX = (float)((tm.getWidth() - 1) * tm.getTileSize());
    if (position.x + width > maxX) position.x = maxX - width;


    int gx  = (int)((position.x + width * 0.5f) / ts);
    int feR = (int)((position.y + height) / ts);
    Tile* below = tm.getTile(gx, feR);
    if (below != nullptr && below->isSolid())
    {
        position.y = (float)(feR * ts) - height;
        velocity.y = 0.0f;
        isOnGround = true;
    }
    else
    {
        isOnGround = false;
    }
    const float FLOOR_Y = 1800.0f;
    if (position.y + height >= FLOOR_Y)
    {
        position.y = FLOOR_Y - height;
        velocity.y = 0.0f;
        isOnGround = true;
    }
    bool isMovingH = (std::fabs(velocity.x) > 5.0f);


    velocity.x *= 0.50f;
    if (std::fabs(velocity.x) < 15.0f) velocity.x = 0.0f;
    if (fireCooldown > 0.0f) fireCooldown -= dt;
    if (invulnTimer > 0.0f)
    {
        invulnTimer -= dt;
        isInvelnerable = (invulnTimer > 0.0f);


        bool show = ((int)(invulnTimer * 16.0f) & 1) == 0;
        if (m_active != nullptr) m_active->setVisible(show);
    }
    else if (m_active != nullptr && !m_active->isVisible())
    {
        m_active->setVisible(true);
    }
    if (powerUpActive)
    {
        powerUpTimer -= dt;
        if (powerUpTimer <= 0.0f)
        {
            powerUpActive = false;
            onPowerUpExpire();
        }
    }

    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);

    if (currentTransformState != nullptr)
        currentTransformState->update(this, dt);

    {
        float vx = velocity.x;
        if (vx < 0.0f) vx = -vx;
        bool isActive = (vx > 5.0f) ||
                        (m_shootAnimTimer > 0.0f) ||
                        !isOnGround;

        if (isActive && saturationStat > 0)
        {
            saturationDrainTimer -= dt;
            if (saturationDrainTimer <= 0.0f)
            {
                saturationStat--;
                saturationDrainTimer = kSatDrainPeriod;
                checkSaturationTransition();
            }
        }
        else
        {
            saturationDrainTimer = kSatDrainPeriod;
        }
    }

    if (m_active != nullptr)
    {
        if (m_shootAnimTimer > 0.0f) m_shootAnimTimer -= dt;
        if (m_grenTimer     > 0.0f) m_grenTimer     -= dt;

        bool grenading = (m_grenTimer     > 0.0f);
        bool shooting  = (m_shootAnimTimer > 0.0f);


        const char* dir = "";
        if      (aimAngle >  45.0f) dir = "_up";
        else if (aimAngle < -45.0f) dir = "_down";

        if (grenading)
        {
            m_active->play("grenade_idle");
        }
        else if (!isOnGround)
        {
            m_active->play(buildClipName("jump"));
        }
        else if (shooting)
        {

            char clip[48];
            const char* base = buildClipName("shoot");
            int i = 0;
            for (int j = 0; base[j] && i < 47; ++j) clip[i++] = base[j];
            for (int j = 0; dir[j]  && i < 47; ++j) clip[i++] = dir[j];
            clip[i] = '\0';
            m_active->play(clip);
        }
        else if (isMovingH)
        {
            m_active->play(buildClipName("run"));
        }
        else
        {
            m_active->play(buildClipName("idle"));
        }

        if (facing != nullptr)
            m_active->setFlipX(facing->getXSign() < 0);

        m_active->update(dt);
        m_active->setPosition(position.x, position.y);
    }
}

void PlayerSoldier::handlePlayerInput(InputHandler& in, float dt)
{
    if (!isAlive) return;


    if (in.isLeftHeld())
    {
        velocity.x = -(baseSpeed * speedMultiplier);
        if (facing == nullptr || facing->getXSign() > 0)
            setFacing(new LeftDirection());
    }
    else if (in.isRightHeld())
    {
        velocity.x = +(baseSpeed * speedMultiplier);
        if (facing == nullptr || facing->getXSign() < 0)
            setFacing(new RightDirection());
    }
    else
    {
        velocity.x = 0.f;
    }
    if (in.isJumpPressed() && isOnGround)
    {
        velocity.y  = inWaterCached ? -380.0f : -700.0f;
        isOnGround  = false;
    }



    if (in.isAimUpHeld())
    {
        aimAngle += 250.0f * dt;
        if (aimAngle > 90.0f) aimAngle = 90.0f;
    }
    else if (in.isDownHeld() && !isOnGround)
    {
        aimAngle = -90.0f;
    }
    else
    {
        aimAngle -= 250.0f * dt;
        if (aimAngle < 0.0f) aimAngle = 0.0f;
    }

    if (in.isFireHeld() && fireCooldown <= 0.0f)
    {
        Weapon* w = inventory.getCurrentWeapon();
        if (w != nullptr && !w->hasAmmo() && inventory.hasWeapon())
        {
            inventory.revertToPistol();
            w = inventory.getCurrentWeapon();
        }
        if (w != nullptr && w->hasAmmo())
        {

            attack();

            float rad = aimAngle * 3.14159265f / 180.0f;
            int   sgn = (facing != nullptr) ? facing->getXSign() : +1;
            coordSyst aim((float)sgn * std::cos(rad), -std::sin(rad));

            Entity* spawned = w->fire(this, aim);
            if (spawned != nullptr)
                queueProjectile(spawned);


            if (powerUpActive && dualFireWhilePoweredUp())
            {
                coordSyst aim2(-aim.x, aim.y);
                Entity* mirror = w->fire(this, aim2);
                if (mirror != nullptr) queueProjectile(mirror);
            }


            float effectiveRateMult = fireRateMultiplier;
            if (powerUpActive) effectiveRateMult *= superchargedFireRate();
            float rate = w->getFireRate() / (effectiveRateMult > 0.01f ? effectiveRateMult : 1.0f);
            if (rate <= 0.0f) rate = 0.25f;
            fireCooldown = rate;
        }
    }

    if (in.isMeleePressed())
        meleeAttack();
    if (in.isThrowGrenadePressed())
        throwGrenade();
}

Entity* PlayerSoldier::takePendingProjectile()
{
    Entity* p = pendingProjectile;
    pendingProjectile = nullptr;
    return p;
}

void PlayerSoldier::queueProjectile(Entity* p)
{
    if (p == nullptr) return;
    if (pendingProjectile == nullptr)
    {
        pendingProjectile = p;
        return;
    }
    if (pendingExtraCount < PENDING_CAP)
    {
        pendingExtras[pendingExtraCount++] = p;
        return;
    }
    delete p;
}


Entity* PlayerSoldier::takeQueuedProjectile()
{
    if (pendingExtraCount <= 0) return nullptr;
    Entity* p = pendingExtras[0];
    for (int i = 1; i < pendingExtraCount; ++i)
        pendingExtras[i - 1] = pendingExtras[i];
    pendingExtras[pendingExtraCount - 1] = nullptr;
    pendingExtraCount--;
    return p;
}

void PlayerSoldier::render(sf::RenderWindow& rw)
{
    if (!m_isActiveSlot) return;
    if (m_active != nullptr)
        m_active->draw(rw);
}
















const char* PlayerSoldier::buildClipName(const char* suffix) const
{
    static char buf[48];
    const char* prefix = "pistol";


    if (currentTransformState != nullptr)
    {
        const char* tp = currentTransformState->getAnimPrefix();
        if (tp != nullptr && tp[0] != '\0') prefix = tp;
    }



    if (prefix[0] == 'p' && prefix[1] == 'i')
    {
        Weapon* w = inventory.getCurrentWeapon();
        if (w != nullptr)
        {
            const char* wp = w->getAnimPrefix();
            if (wp != nullptr) prefix = wp;
        }
    }
    if (prefix == nullptr) prefix = "pistol";

    int i = 0;
    for (int j = 0; prefix[j] && i < 47; ++j) buf[i++] = prefix[j];
    if (i < 47) buf[i++] = '_';
    for (int j = 0; suffix[j] && i < 47; ++j) buf[i++] = suffix[j];
    buf[i] = '\0';
    return buf;
}
