#pragma once
#include <SFML/Graphics.hpp>

class GameState;
class GameStateManager
{
    static const int GSM_CAP = 8;
    GameState* states[GSM_CAP];
    int stateCount;

public:
    GameStateManager();
    ~GameStateManager();

    void pushState(GameState* s);
    void popState();
    void replaceTop(GameState* s);
    GameState*  currentState();

    void update(float dt);
    void render(sf::RenderWindow& rw);
    void handleInputForTop();
};
