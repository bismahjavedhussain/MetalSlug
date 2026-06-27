#include "CollisionManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Projectile.h"
#include "DamagableEntity.h"
#include "Enemy.h"
#include "PlayerSoldier.h"
#include "BulletDamage.h"
#include "ContactDamage.h"
#include "FireDamage.h"
#include "ExplosionDamage.h"
#include "MeleeDamage.h"
#include "ScoreManager.h"
#include "AreaHazard.h"
#include "Collectible.h"
#include "PlayState.h"
#include "Vehicle.h"
#include <cmath>
#include <iostream>

static coordSyst projectileDir(Projectile* p)
{
    coordSyst v = p->getVelocity();
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    if (len < 0.0001f) return coordSyst(1.0f, 0.0f);
    return coordSyst(v.x / len, v.y / len);
}

bool CollisionManager::isPlayerKill(Projectile* p) const
{
    if (p == nullptr) return false;
    return !p->isOwnerHostile();
}

void CollisionManager::resolve(EntityManager& em, TileMap& ,
                               PlayerSoldier* activePlayer,
                               ScoreManager* scoreMgr,
                               PlayState* ps)
{
    Entity** roster = em.getEntities();
    int n  = em.getCount();

    const float BLAST_RADIUS_PX    = 192.0f;
    const float BLAST_RADIUS_PX_SQ = BLAST_RADIUS_PX * BLAST_RADIUS_PX;

    for (int i = 0; i < n; ++i)
    {
        Projectile* p = roster[i]->asProjectile();
        if (p == nullptr || !p->getIsAlive()) continue;
        Entity* shooter = p->getOwner();

        coordSyst dir   = projectileDir(p);
        bool isExplosive = p->isExplosiveImpact();
        bool isMelee     = p->isMeleeImpact();


        int   primaryJ      = -1;
        bool  blockedShield = false;
        for (int j = 0; j < n; ++j)
        {
            if (i == j) continue;
            DamagableEntity* d = roster[j]->asDamagableEntity();
            if (d == nullptr || !d->getIsAlive()) continue;
            if ((Entity*)d == shooter) continue;

            Enemy* parked = d->asEnemy();
            if (parked != nullptr && parked->getInReserve()) 
            continue;
            if (!p->isOwnerHostile() && d->isPlayer()) continue;

            if (!p->checkCollision(*d))
             continue;
            Enemy* asEnemy = d->asEnemy();

            bool wouldBlock = (asEnemy != nullptr) &&
                              asEnemy->blocksProjectile(dir, isExplosive);
            if (wouldBlock && !p->isPiercingShield())
            {
                blockedShield = true;
            }
            primaryJ = j;
            break;
        }

        if (blockedShield)
        {
            p->onImpact();
            continue;
        }
        if (primaryJ < 0) continue;

        DamagableEntity* primary    = roster[primaryJ]->asDamagableEntity();
        Enemy*           primaryEn  = primary != nullptr ? primary->asEnemy() : nullptr;

        int dmg = p->getDamage();

        if (isExplosive)
        {

            ExplosionDamage ed(shooter, BLAST_RADIUS_PX);
            if (dmg <= 0) dmg = ed.amount();

            coordSyst pp = p->getPosition();
            int killCount = 0;

            for (int k = 0; k < n; ++k)
            {
                if (k == i) continue;
                DamagableEntity* dk = roster[k]->asDamagableEntity();
                if (dk == nullptr || !dk->getIsAlive()) continue;
                if ((Entity*)dk == shooter) continue;


                Enemy* parkedK = dk->asEnemy();
                if (parkedK != nullptr && parkedK->getInReserve()) continue;


                coordSyst kp = roster[k]->getPosition();
                float cx = kp.x + roster[k]->getWidth()  * 0.5f;
                float cy = kp.y + roster[k]->getHeight() * 0.5f;
                float ddx = cx - pp.x;
                float ddy = cy - pp.y;
                if (ddx * ddx + ddy * ddy > BLAST_RADIUS_PX_SQ) continue;

                Enemy* ek = dk->asEnemy();
                bool wasAlive = dk->getIsAlive();
                dk->takeDamage(dmg, &ed);
                if (ek != nullptr && wasAlive && !ek->getIsAlive())
                {
                    if (scoreMgr != nullptr && isPlayerKill(p))
                    {
                        scoreMgr->addEnemyKill(ek);
                        if (ek->isAerial()) scoreMgr->addAerialKillBonus();
                        ++killCount;
                    }
                }
            }

            if (scoreMgr != nullptr && isPlayerKill(p))
            {
                if (killCount == 2)      scoreMgr->addMultiKillBonus(2);
                else if (killCount >= 3) scoreMgr->addMassacreBonus(killCount);
            }
        }
        else if (isMelee)
        {
            MeleeDamage md(shooter);
            if (dmg <= 0) dmg = md.amount();
            primary->takeDamage(dmg, &md);
            if (scoreMgr != nullptr && primaryEn != nullptr && !primaryEn->getIsAlive()
                && isPlayerKill(p))
            {
                scoreMgr->addEnemyKill(primaryEn);
                if (primaryEn->isAerial()) scoreMgr->addAerialKillBonus();
                scoreMgr->addMeleeKillBonus();
            }
        }
        else
        {
            BulletDamage bd(shooter);
            if (dmg <= 0) dmg = bd.amount();
            primary->takeDamage(dmg, &bd);
            if (scoreMgr != nullptr && primaryEn != nullptr && !primaryEn->getIsAlive()
                && isPlayerKill(p))
            {
                scoreMgr->addEnemyKill(primaryEn);
                if (primaryEn->isAerial()) scoreMgr->addAerialKillBonus();
            }
        }

        p->onImpact();
    }

    for (int i = 0; i < n; ++i)
    {
        Projectile* p = roster[i]->asProjectile();
        if (p == nullptr) continue;
        if (p->getIsAlive()) continue;
        if (!p->isExplosiveImpact()) continue;
        if (!p->getAoePending()) continue;

        Entity*   shooter = p->getOwner();
        coordSyst pp      = p->getPosition();
        ExplosionDamage ed(shooter, BLAST_RADIUS_PX);
        int dmg = p->getDamage();
        if (dmg <= 0) dmg = ed.amount();

        int killCount = 0;
        for (int k = 0; k < n; ++k)
        {
            if (k == i) continue;
            DamagableEntity* dk = roster[k]->asDamagableEntity();
            if (dk == nullptr || !dk->getIsAlive()) continue;
            if ((Entity*)dk == shooter) continue;


            Enemy* parkedK = dk->asEnemy();
            if (parkedK != nullptr && parkedK->getInReserve()) continue;

            coordSyst kp = roster[k]->getPosition();
            float cx = kp.x + roster[k]->getWidth()  * 0.5f;
            float cy = kp.y + roster[k]->getHeight() * 0.5f;
            float ddx = cx - pp.x;
            float ddy = cy - pp.y;
            if (ddx * ddx + ddy * ddy > BLAST_RADIUS_PX_SQ) continue;

            Enemy* ek = dk->asEnemy();
            bool wasAlive = dk->getIsAlive();
            dk->takeDamage(dmg, &ed);
            if (ek != nullptr && wasAlive && !ek->getIsAlive())
            {
                if (scoreMgr != nullptr && isPlayerKill(p))
                {
                    scoreMgr->addEnemyKill(ek);
                    if (ek->isAerial()) scoreMgr->addAerialKillBonus();
                    ++killCount;
                }
            }
        }

        if (scoreMgr != nullptr && isPlayerKill(p))
        {
            if (killCount == 2)      scoreMgr->addMultiKillBonus(2);
            else if (killCount >= 3) scoreMgr->addMassacreBonus(killCount);
        }
        p->setAoePending(false);
    }

    for (int i = 0; i < n; ++i)
    {
        AreaHazard* h = roster[i]->asAreaHazard();
        if (h == nullptr || !h->getIsAlive()) continue;

        for (int j = 0; j < n; ++j)
        {
            if (i == j) continue;
            DamagableEntity* d = roster[j]->asDamagableEntity();
            if (d == nullptr || !d->getIsAlive()) continue;


            Enemy* parked = d->asEnemy();
            if (parked != nullptr && parked->getInReserve()) continue;

            if (!h->checkCollision(*d)) continue;

            FireDamage fd(h);
            int frameDmg = h->getDamagePerSecond();
            if (frameDmg <= 0) frameDmg = 1;
            d->takeDamage(frameDmg, &fd);

            Enemy* asEnemy = d->asEnemy();
            if (scoreMgr != nullptr && asEnemy != nullptr && !asEnemy->getIsAlive())
            {
                scoreMgr->addEnemyKill(asEnemy);
                if (asEnemy->isAerial()) scoreMgr->addAerialKillBonus();
            }
        }
    }


    if (activePlayer != nullptr && activePlayer->getIsAlive() && !activePlayer->getIsRiding())
    {
        for (int i = 0; i < n; ++i)
        {
            Enemy* e = roster[i]->asEnemy();
            if (e == nullptr || !e->getIsAlive()) continue;
            if (e->getInReserve()) continue;
            if (activePlayer->checkCollision(*e))
                e->onPlayerContact(activePlayer);
        }
    }
    else if (activePlayer != nullptr && activePlayer->getIsRiding() && ps != nullptr)
    {
        Vehicle* v = ps->getActiveVehicle();
        if (v != nullptr && v->getIsAlive())
        {
            for (int i = 0; i < n; ++i)
            {
                Enemy* e = roster[i]->asEnemy();
                if (e == nullptr || !e->getIsAlive()) continue;
                if (e->getInReserve()) continue;
                if (v->checkCollision(*e))
                {
                    ContactDamage cd(e);
                    v->takeDamage(cd.amount(), &cd);
                }
            }
        }
    }
    if (activePlayer != nullptr && activePlayer->getIsAlive() && !activePlayer->getIsRiding())
    {

        if (ps != nullptr)
        {
            for (int i = 0; i < n; ++i)
            {
                Collectible* c = roster[i]->asCollectible();
                if (c == nullptr || !c->getIsAlive() || c->isConsumed()) continue;
                if (c->requiresKeyPress()) continue;
                if (activePlayer->checkCollision(*c))
                    c->onPickup(activePlayer, *ps);
            }
        }
    }
}
