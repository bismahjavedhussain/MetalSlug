#pragma once
#include "DamagableEntity.h"
#include "coordSyst.h"
#include "SpriteAnimator.h"

class EnemyAIState;
class TileMap;
class Collectible;
class PlayerSoldier;
class TextureManager;
class Weapon;

class Enemy : public DamagableEntity
{
protected:
    int            scoreValue;
    bool           isGrudgeful;
    EnemyAIState*  currentAIState;
    SpriteAnimator m_anim;
    bool           m_inReserve;
    TextureManager* m_tex;
    Weapon* weapon;

public:
    Enemy(int scoreVal, int hp, bool grudgeful);
    Enemy(const Enemy& other);
    Enemy& operator=(const Enemy& other);
    virtual ~Enemy();

    virtual void attack()                                = 0;
    virtual void update(TileMap& tm, float dt) override;
    virtual void render(sf::RenderWindow& rw) override;
    virtual void onDeath();
    void         die() override;

    void  pathToPlayer(TileMap& tm, coordSyst target);
    void  changeAIState(EnemyAIState* s);
    virtual Enemy* clone() = 0;

    virtual void onPlayerContact(PlayerSoldier* p);
    virtual bool blocksProjectile(coordSyst , bool ) { return false; }
    virtual bool isAerial() const { return false; }

    int   getScoreValue() const { return scoreValue; }
    bool  getIsGrudgeful() const { return isGrudgeful; }
    void  setIsGrudgeful(bool g) { isGrudgeful = g; }

    bool  getInReserve() const { return m_inReserve; }
    void  setInReserve(bool b) { m_inReserve = b; }

    SpriteAnimator* getRenderable() override { return &m_anim; }
    Enemy* asEnemy() override { return this; }
    Collectible* takePendingDrop();
    Entity* takePendingProjectile();
    Entity* takePendingSpawn() override;
protected:
    Collectible* pendingDrop;
    Entity*      pendingProjectile;
    void rollDeathDrop();
};
