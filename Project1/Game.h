#pragma once
#include <SFML/Graphics.hpp>

class GameStateManager;
class Game
{
    sf::RenderWindow* window;
    sf::Clock         clock;
    GameStateManager* stateMgr;
    bool isRunning;

public:
    Game();
    ~Game();

    void run();
    void processEvents();
    void update(float dt);
    void render();
    void shutdown();
};
