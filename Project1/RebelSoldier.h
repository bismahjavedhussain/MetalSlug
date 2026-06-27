#pragma once
#include "Infantry.h"
#include "TextureManager.h"

class TileMap;



class RebelSoldier : public Infantry
{
private:
    float m_walkSpeed;
    float m_shootCooldown;
    float m_shootDuration;
    int   m_facingDir;

public:
    RebelSoldier(TextureManager& tm, float spawnX, float spawnY, int batchId = 0);
    ~RebelSoldier() override = default;

    void update(TileMap& tm, float dt) override;
    void attack() override;
    Enemy* clone() override;
    void onPlayerContact(PlayerSoldier* p) override;
};
