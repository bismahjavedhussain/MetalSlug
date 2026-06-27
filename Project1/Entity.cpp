#include "Entity.h"

Entity::Entity()
    : position(), velocity(), width(0.0f), height(0.0f),
      isAlive(true), isOnGround(false), touchesWall(false) {}
Box Entity::getHitbox()
{
    return Box(position.x, position.y, width, height);
}

bool Entity::checkCollision(Entity& other)
{
    Box a = this->getHitbox();
    Box b = other.getHitbox();
    return (a.x < b.x + b.width  &&
            a.x + a.width  > b.x &&
            a.y < b.y + b.height &&
            a.y + a.height > b.y);
}

Entity* Entity::clone()
{
    return nullptr;
}
