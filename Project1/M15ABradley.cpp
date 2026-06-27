#include "M15ABradley.h"
#include "TileMap.h"
#include "Tile.h"
#include "DamageState.h"
#include "EntityAnims.h"
#include "BazookaShell.h"

M15ABradley::M15ABradley(TextureManager& tm, float spawnX, float spawnY)
    : EnemyVehicle(7, true, 200),
      isStationary(true),
      crawlSpeed(35.0f),
      facingDir(-1),
      fireCooldown(2.0f),
      hasPendingShell(false)
{
    setupBradleyAnims(m_anim, tm);
    width      = m_anim.scaledW(); if (width  < 1.0f) width  = 96.0f;
    height     = m_anim.scaledH(); if (height < 1.0f) height = 64.0f;
    position.x = spawnX;
    position.y = spawnY;
}

void M15ABradley::update(TileMap& tm, float dt)
{
    if (!isAlive)
    {
        m_anim.play("explode");
        m_anim.update(dt);
        return;
    }
    int ts = tm.getTileSize();
    int gy = (int)((position.y + height) / ts);
    int gxAhead = (int)((position.x + (facingDir > 0 ? width : 0.0f)) / ts);
    bool flatAhead = true;
    for (int i = 0; i < 4 && flatAhead; ++i)
    {
        Tile* t = tm.getTile(gxAhead + i * facingDir, gy);
        if (t == nullptr || !t->isSolid()) { flatAhead = false; break; }
        Tile* up = tm.getTile(gxAhead + i * facingDir, gy - 1);
        if (up != nullptr && up->isSolid()) { flatAhead = false; break; }
    }
    isStationary = !flatAhead;

    if (!isStationary)
    {
        velocity.x = crawlSpeed * (float)facingDir;
        position.x += velocity.x * dt;
    }
    else
    {
        velocity.x = 0.0f;
    }


    Tile* below = tm.getTile((int)((position.x + width * 0.5f) / ts),
                             (int)((position.y + height) / ts));
    if (below != nullptr && below->isSolid())
        position.y = (float)((int)((position.y + height) / ts) * ts) - height;

    fireCooldown -= dt;
    if (fireCooldown <= 0.0f)
    {
        attack();
        fireCooldown = 2.0f;
    }

    if (currentDamageState != nullptr)
        currentDamageState->update(this, dt);

    m_anim.play(isStationary ? "fire" : "move");
    m_anim.setFlipX(facingDir < 0);
    m_anim.setPosition(position.x, position.y);
    m_anim.update(dt);
}

void M15ABradley::attack()
{
    if (!getCanFire()) return;
    pendingShellOrigin.x = position.x + width * 0.5f;
    pendingShellOrigin.y = position.y;
    pendingShellAim.x    = (float)facingDir * 0.7f;
    pendingShellAim.y    = -0.7f;
    hasPendingShell = true;
}

bool M15ABradley::takePendingShell(coordSyst& outOrigin, coordSyst& outAim)
{
    if (!hasPendingShell) return false;
    outOrigin = pendingShellOrigin;
    outAim    = pendingShellAim;
    hasPendingShell = false;
    return true;
}

Entity* M15ABradley::takePendingSpawn()
{
    if (!hasPendingShell) return nullptr;
    hasPendingShell = false;
    BazookaShell* sh = new BazookaShell(this, 5, pendingShellAim,
                                        360.0f, 1100.0f,
                                        96.0f);
    sh->setPosition(pendingShellOrigin.x, pendingShellOrigin.y);
    return sh;
}

void M15ABradley::onDestroy()
{
    EnemyVehicle::onDestroy();
}

Entity* M15ABradley::clone()
{
    return new M15ABradley(*this);
}
