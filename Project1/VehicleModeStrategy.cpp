#include "VehicleModeStrategy.h"
#include "AmphibiousSlug.h"
#include "TileMap.h"
#include "Tile.h"




void NormalSlugMode::fire(coordSyst aim)
{
    if (owner != nullptr) owner->fireAsSlug(aim);
}

void NormalSlugMode::update(TileMap& , float ) {}



VehicleModeStrategy* NormalSlugMode::canSwitchTo(TileMap& tm)
{
    if (owner == nullptr) return nullptr;
    coordSyst pos = owner->getPosition();
    int ts = tm.getTileSize();
    int gx = (int)((pos.x + owner->getWidth() * 0.5f) / ts);
    int gy = (int)((pos.y + owner->getHeight()) / ts);
    Tile* below = tm.getTile(gx, gy);
    if (below != nullptr && below->isWater())  return new MarinerMode();
    if (below == nullptr || !below->isSolid()) return new FlyerMode();
    return nullptr;
}


void FlyerMode::fire(coordSyst aim)
{
    if (owner == nullptr) return;
    if (missilesRemaining > 0)
    {
        owner->fireAsFlyerMissile(aim);
        missilesRemaining--;
    }
    else
    {
        owner->fireAsFlyerBullet(aim);
    }
}

void FlyerMode::update(TileMap& , float ) {}


VehicleModeStrategy* FlyerMode::canSwitchTo(TileMap& tm)
{
    if (owner == nullptr) return nullptr;
    coordSyst pos = owner->getPosition();
    int ts = tm.getTileSize();
    int gx = (int)((pos.x + owner->getWidth() * 0.5f) / ts);
    int gy = (int)((pos.y + owner->getHeight()) / ts);
    Tile* below = tm.getTile(gx, gy);
    if (below != nullptr && below->isWater()) return new MarinerMode();
    if (below != nullptr && below->isSolid()) return new NormalSlugMode();
    return nullptr;
}





void MarinerMode::fire(coordSyst aim)
{
    if (owner == nullptr) return;
    if (aim.y > 0.6f && verticalMissiles > 0)
    {
        owner->fireAsMarinerVertical(aim);
        verticalMissiles--;
    }
    else if (aim.y < -0.6f && reverseArcMissiles > 0)
    {
        owner->fireAsMarinerReverse(aim);
        reverseArcMissiles--;
    }
    else if (horizontalMissiles > 0)
    {
        owner->fireAsMarinerHorizontal(aim);
        horizontalMissiles--;
    }
}

void MarinerMode::update(TileMap& , float ) {}




VehicleModeStrategy* MarinerMode::canSwitchTo(TileMap& tm)
{
    if (owner == nullptr) return nullptr;
    coordSyst pos = owner->getPosition();
    int ts = tm.getTileSize();
    int gx = (int)((pos.x + owner->getWidth()  * 0.5f) / ts);
    int gy = (int)((pos.y + owner->getHeight() * 0.5f) / ts);
    Tile* here = tm.getTile(gx, gy);
    if (here == nullptr || here->isWater()) return nullptr;
    int gFootY = (int)((pos.y + owner->getHeight()) / ts);
    Tile* below = tm.getTile(gx, gFootY);
    if (below != nullptr && below->isSolid()) return new NormalSlugMode();
    return new FlyerMode();
}
