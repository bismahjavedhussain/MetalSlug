#include "ParatrooperKind.h"
#include "RebelSoldier.h"
#include "ShieldedSoldier.h"
#include "BazookaSoldier.h"
#include "Grenadier.h"

int RebelParatrooperKind::scoreBase() { return 50; }
Infantry* RebelParatrooperKind::spawnLanded(TextureManager& tm, float x, float y, int batchId)
{
    return new RebelSoldier(tm, x, y, batchId);
}
ParatrooperKind* RebelParatrooperKind::clone() { return new RebelParatrooperKind(); }

int ShieldedParatrooperKind::scoreBase() { return 75; }
Infantry* ShieldedParatrooperKind::spawnLanded(TextureManager& tm, float x, float y, int batchId)
{
    return new ShieldedSoldier(tm, x, y, batchId);
}
ParatrooperKind* ShieldedParatrooperKind::clone() { return new ShieldedParatrooperKind(); }

int BazookaParatrooperKind::scoreBase() { return 100; }
Infantry* BazookaParatrooperKind::spawnLanded(TextureManager& tm, float x, float y, int batchId)
{
    return new BazookaSoldier(tm, x, y, batchId);
}
ParatrooperKind* BazookaParatrooperKind::clone() { return new BazookaParatrooperKind(); }

int GrenadierParatrooperKind::scoreBase() { return 100; }
Infantry* GrenadierParatrooperKind::spawnLanded(TextureManager& tm, float x, float y, int batchId)
{
    return new Grenadier(tm, x, y, batchId);
}
ParatrooperKind* GrenadierParatrooperKind::clone() { return new GrenadierParatrooperKind(); }
