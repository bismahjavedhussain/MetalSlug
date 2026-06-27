#include "MenuState.h"
#include "MainMenu.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "InputHandler.h"

MenuState::MenuState() : menu(nullptr) {}

MenuState::~MenuState()
{
    if (menu != nullptr) { delete menu; menu = nullptr; }
}

void MenuState::enter()
{
    if (menu == nullptr) menu = new MainMenu();
}

void MenuState::exit() {  }

void MenuState::update(float dt)
{
    if (menu == nullptr || owner == nullptr) return;

    menu->update(dt);

    if (menu->isReady())
    {

        GameMode* picked = menu->getSelectedMode();
        owner->replaceTop(new PlayState(picked));
    }

}

void MenuState::render(sf::RenderWindow& rw)
{
    if (menu != nullptr) menu->render(rw);
}

void MenuState::handleInput(InputHandler& in)
{
    if (menu != nullptr) menu->handleInput(in);
}
