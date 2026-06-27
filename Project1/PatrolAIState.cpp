#include "PatrolAIState.h"
#include "Enemy.h"
#include "TileMap.h"

PatrolAIState::PatrolAIState() : patrolSpeed(40.0f), facingSign(-1) {}

void PatrolAIState::enter(Enemy* e) { owner = e; }
void PatrolAIState::exit(Enemy* ) {}
void PatrolAIState::update(Enemy* , TileMap& , float ) {}
