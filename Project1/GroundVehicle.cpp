#include "GroundVehicle.h"
#include "TileMap.h"
#include "Tile.h"

void GroundVehicle::traverseStep(TileMap& tm)
{
    int ts = tm.getTileSize();
    int frontX = (int)((position.x + (velocity.x >= 0.0f ? width : 0.0f)) / ts);
    int feetY  = (int)((position.y + height) / ts);
    if (frontX < 0 || frontX >= tm.getWidth()) return;

    Tile* atFront = tm.getTile(frontX, feetY - 1);
    Tile* above   = tm.getTile(frontX, feetY - 2);

    if (atFront != nullptr && atFront->isSolid() &&
        (above == nullptr || !above->isSolid()))
    {

        position.y -= (float)ts;
    }
}
