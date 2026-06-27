#pragma once

class EntityManager;
class TileMap;
class PlayerSoldier;
class ScoreManager;
class Entity;
class Projectile;
class CollisionManager
{
    bool isPlayerKill(Projectile* p) const;

public:
    CollisionManager() = default;
    void resolve(EntityManager& em, TileMap& tm,
                 PlayerSoldier* activePlayer,
                 ScoreManager*  scoreMgr,
                 class PlayState* ps);
};
