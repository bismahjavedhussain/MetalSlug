#include "BossPhase.h"
#include "BossLevel.h"
#include "IronNokana.h"
#include "HairBusterRiberts.h"
#include "SeaSatan.h"
#include "UltimateBoss.h"
#include "Boss.h"
void BossPhase1Ground::enter(BossLevel* lvl)
{
    lvl->enterPhase1();
}
BossPhase* BossPhase1Ground::tick(BossLevel* lvl)
{
    if (lvl->activeBoss == nullptr) return nullptr;
    if (lvl->groundBoss != nullptr && !lvl->groundBoss->getIsAlive())
    {
        return new BossPhase2Aerial();
    }
    return nullptr;
}

void BossPhase2Aerial::enter(BossLevel* lvl)
{
    lvl->enterPhase2();
}
BossPhase* BossPhase2Aerial::tick(BossLevel* lvl)
{
    if (lvl->activeBoss == nullptr) return nullptr;
    if (lvl->aerialBoss != nullptr && !lvl->aerialBoss->getIsAlive())
    {
        return new BossPhase3Aquatic();
    }
    return nullptr;
}

void BossPhase3Aquatic::enter(BossLevel* lvl)
{
    lvl->enterPhase3();
}
BossPhase* BossPhase3Aquatic::tick(BossLevel* lvl)
{
    if (lvl->activeBoss == nullptr) return nullptr;
    if (lvl->aquaticBoss != nullptr && !lvl->aquaticBoss->getIsAlive())
    {
        return new BossPhase4Fused();
    }
    return nullptr;
}

void BossPhase4Fused::enter(BossLevel* lvl)
{
    lvl->enterPhase4();
}
BossPhase* BossPhase4Fused::tick(BossLevel* lvl)
{
    if (lvl->activeBoss == nullptr) return nullptr;

    if (lvl->ultimateBoss != nullptr && !lvl->ultimateBoss->getIsAlive())
    {
        return new BossPhaseDone();
    }
    return nullptr;
}

void BossPhaseDone::enter(BossLevel* lvl)
{
    lvl->complete   = true;
    lvl->activeBoss = nullptr;
}
