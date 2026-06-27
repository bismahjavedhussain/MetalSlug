#pragma once
#include <SFML/Graphics.hpp>

class GameStateManager;
class InputHandler;


class GameState
{
protected:
    GameStateManager* owner;

public:
    GameState() : owner(nullptr) {}
    virtual ~GameState() = default;

    void setOwner(GameStateManager* o) { owner = o; }
    virtual void enter()  = 0;
    virtual void exit()  = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& rw) = 0;
    virtual void handleInput(InputHandler& in) = 0;
};
