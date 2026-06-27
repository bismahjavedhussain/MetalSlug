#pragma once
#include "Undead.h"
#include "TextureManager.h"

class Weapon;
class Zombie : public Undead
{
private:
    float    walkSpeed;
    float    shootCooldown;
    int      facingDir;
    Weapon*  weapon;

public:
    Zombie(TextureManager& tm, float spawnX, float spawnY);
    Zombie(const Zombie& other);
    Zombie& operator=(const Zombie& other);
    ~Zombie() override;

    void  update(TileMap& tm, float dt)             override;
    void  attack()                                  override;
    void  onPlayerContact(PlayerSoldier* p)         override;
    Enemy* clone()                                  override;
};
