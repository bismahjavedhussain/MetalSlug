#include "GameStateManager.h"
#include "GameState.h"
#include "InputHandler.h"

GameStateManager::GameStateManager() : stateCount(0)
{
    for (int i = 0; i < GSM_CAP; ++i) 
    states[i] = nullptr;
}

GameStateManager::~GameStateManager()
{
    while (stateCount > 0) 
    popState();
}

void GameStateManager::pushState(GameState* s)
{
    if (s == nullptr) return;
    if (stateCount >= GSM_CAP) { delete s; return; }
    s->setOwner(this);
    states[stateCount++] = s;
    s->enter();
}

void GameStateManager::popState()
{
    if (stateCount <= 0) return;
    GameState* top = states[stateCount - 1];
    if (top != nullptr)
    {
        top->exit();
        delete top;
    }
    states[stateCount - 1] = nullptr;
    stateCount--;
}

void GameStateManager::replaceTop(GameState* s)
{
    popState();
    pushState(s);
}

GameState* GameStateManager::currentState()
{
    if (stateCount <= 0) return nullptr;
    return states[stateCount - 1];
}

void GameStateManager::update(float dt)
{
    GameState* top = currentState();
    if (top != nullptr) top->update(dt);
}

void GameStateManager::render(sf::RenderWindow& rw)
{
    GameState* top = currentState();
    if (top != nullptr) top->render(rw);
}

void GameStateManager::handleInputForTop()
{
}
