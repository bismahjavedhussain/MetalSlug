#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "MenuState.h"
#include "InputHandler.h"

Game::Game(): window(nullptr), stateMgr(nullptr), isRunning(true)
{
    window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Metal Slug");
    stateMgr = new GameStateManager();
    stateMgr->pushState(new MenuState());
}

Game::~Game()
{
    shutdown();
}

void Game::run()
{
    InputHandler input;
    clock.restart();

    while (isRunning)
    {

        sf::Time elapsed = clock.getElapsedTime();
        float dt = elapsed.asSeconds();
        clock.restart();
        if (dt > 0.05f) dt = 0.05f;

        processEvents();
        input.poll(*window);


        GameState* top = stateMgr->currentState();
        if (top != nullptr) top->handleInput(input);


        if (input.isEscapeHeld()) isRunning = false;

        update(dt);
        render();
    }

    if (window != nullptr) window->close();
}

void Game::processEvents()
{
    if (window == nullptr) return;
    sf::Event ev;
    while (window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
            isRunning = false;
    }
}

void Game::update(float dt)
{
    if (stateMgr != nullptr) stateMgr->update(dt);
}

void Game::render()
{
    if (window == nullptr) return;
    window->clear();
    if (stateMgr != nullptr) stateMgr->render(*window);
    window->display();
}

void Game::shutdown()
{
    if (stateMgr != nullptr) { delete stateMgr; stateMgr = nullptr; }
    if (window   != nullptr)
    {
        window->close();
        delete window;
        window = nullptr;
    }
}
