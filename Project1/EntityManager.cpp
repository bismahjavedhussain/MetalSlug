#include "EntityManager.h"
#include "Entity.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

EntityManager::EntityManager()
    : entities(nullptr), entityCount(0), capacity(INITIAL_CAP)
{
    entities = new Entity*[capacity];
    for (int i = 0; i < capacity; ++i) entities[i] = nullptr;
}

EntityManager::~EntityManager()
{
    for (int i = 0; i < entityCount; ++i)
    {
        if (entities[i] != nullptr)
        {
            delete entities[i];
            entities[i] = nullptr;
        }
    }
    delete[] entities;
}

void EntityManager::growRoster()
{
    int newCap = capacity * 2;
    Entity** bigger = new Entity*[newCap];
    for (int i = 0; i < newCap; ++i) bigger[i] = nullptr;
    for (int i = 0; i < entityCount; ++i) bigger[i] = entities[i];
    delete[] entities;
    entities = bigger;
    capacity = newCap;
}

void EntityManager::addEntity(Entity* e)
{
    if (e == nullptr) return;
    if (entityCount >= capacity) growRoster();
    entities[entityCount++] = e;
}

void EntityManager::removeEntity(Entity* e)
{
    for (int i = 0; i < entityCount; ++i)
    {
        if (entities[i] == e)
        {

            entities[i]->kill();
            return;
        }
    }
}

void EntityManager::clearTransientEntities()
{
    int write = 0;
    for (int read = 0; read < entityCount; ++read)
    {
        Entity* e = entities[read];
        if (e == nullptr) continue;

        bool keep = e->isPlayer() || (e->asProjectile() != nullptr);
        if (keep)
        {
            entities[write++] = e;
        }
        else
        {
            delete e;
        }
    }
    for (int i = write; i < entityCount; ++i) entities[i] = nullptr;
    entityCount = write;
}

void EntityManager::purgeDead()
{
    int write = 0;
    for (int read = 0; read < entityCount; ++read)
    {
        if (entities[read] == nullptr) continue;

        Enemy* en = entities[read]->asEnemy();
        bool reservedEnemy = (en != nullptr && en->getInReserve());
        bool isBoss        = (entities[read]->asBoss() != nullptr);

        if (entities[read]->getIsAlive() || entities[read]->isPlayer()
            || reservedEnemy || isBoss)
        {
            entities[write++] = entities[read];
        }
        else
        {
            delete entities[read];
        }
    }
    for (int i = write; i < entityCount; ++i) entities[i] = nullptr;
    entityCount = write;
}

void EntityManager::updateAll(TileMap& tm, float dt)
{
    for (int i = 0; i < entityCount; ++i)
    {
        if (entities[i] == nullptr) continue;
        Enemy* en = entities[i]->asEnemy();
        if (en != nullptr && en->getInReserve()) continue;
        if (entities[i]->getIsAlive() || entities[i]->isPlayer())
            entities[i]->update(tm, dt);
    }
}

void EntityManager::renderAll(sf::RenderWindow& rw, Camera& )
{
    for (int i = 0; i < entityCount; ++i)
    {
        if (entities[i] != nullptr && entities[i]->getIsAlive())
            entities[i]->render(rw);
    }
}
