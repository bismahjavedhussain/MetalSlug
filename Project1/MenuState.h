#pragma once
#include "GameState.h"

class MainMenu;
class InputHandler;

class MenuState : public GameState
{
    MainMenu* menu;

public:
    MenuState();
    ~MenuState() override;

    void enter()  override;
    void exit() override;
    void update(float dt)  override;
    void render(sf::RenderWindow& rw)override;
    void handleInput(InputHandler& in) override;
};
