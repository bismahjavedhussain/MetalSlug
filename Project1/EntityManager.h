#pragma once
#include <SFML/Graphics.hpp>
class Entity;
class TileMap;
class Camera;



class EntityManager
{
    static const int INITIAL_CAP = 256;

    Entity** entities;
    int entityCount;
    int capacity;

    void growRoster();

public:
    EntityManager();
    ~EntityManager();

    void addEntity(Entity* e);
    void removeEntity(Entity* e);
    void purgeDead();
    void clearTransientEntities();

    void updateAll(TileMap& tm, float dt);
    void renderAll(sf::RenderWindow& rw, Camera& cam);

    Entity** getEntities() { return entities; }
    int getCount() const { return entityCount; }
};
