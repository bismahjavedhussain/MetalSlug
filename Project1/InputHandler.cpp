#include "InputHandler.h"

InputHandler::InputHandler()
    : currSpace(false), prevSpace(false),
      currZ(false), prevZ(false),
      currR(false), prevR(false),
      currP(false), prevP(false),
      currB(false), prevB(false),
      currC(false), prevC(false),
      currEnter(false), prevEnter(false),
      currE(false), prevE(false),
      currEsc(false), prevEsc(false),
      currF(false), prevF(false),
      mouseX(0), mouseY(0),
      currMouseL(false), prevMouseL(false) {}

void InputHandler::poll(const sf::RenderWindow& window)
{

    prevSpace  = currSpace;
    prevZ      = currZ;
    prevR      = currR;
    prevP      = currP;
    prevB      = currB;
    prevC      = currC;
    prevEnter  = currEnter;
    prevE      = currE;
    prevEsc    = currEsc;
    prevF      = currF;
    prevMouseL = currMouseL;

    currSpace  = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    currZ      = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    currR      = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    currP      = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
    currB      = sf::Keyboard::isKeyPressed(sf::Keyboard::B);
    currC      = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
    currEnter  = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
    currE      = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    currEsc    = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    currF      = sf::Keyboard::isKeyPressed(sf::Keyboard::F);


    sf::Vector2i mp = sf::Mouse::getPosition(window);
    mouseX     = mp.x;
    mouseY     = mp.y;
    currMouseL = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool InputHandler::isLeftHeld()  const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);  }
bool InputHandler::isRightHeld() const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Right); }
bool InputHandler::isUpHeld()    const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);    }
bool InputHandler::isDownHeld()  const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);  }
bool InputHandler::isAimUpHeld() const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);    }
bool InputHandler::isFireHeld()  const { return sf::Keyboard::isKeyPressed(sf::Keyboard::X);     }

bool InputHandler::isJumpPressed()            const { return currSpace && !prevSpace; }
bool InputHandler::isThrowGrenadePressed()    const { return currC     && !prevC;     }
bool InputHandler::isMeleePressed()           const { return currP     && !prevP;     }
bool InputHandler::isSwitchCharacterPressed() const { return currZ     && !prevZ;     }
bool InputHandler::isRewindPressed()          const { return currR     && !prevR;     }
bool InputHandler::isBestPlayerPressed()      const { return currB     && !prevB;     }
bool InputHandler::isStartPressed()           const { return currEnter && !prevEnter; }
bool InputHandler::isInteractPressed()        const { return currE     && !prevE;     }
bool InputHandler::isMenuBackPressed()        const { return currEsc   && !prevEsc;   }
bool InputHandler::isFusionPressed()          const { return currF     && !prevF;     }
bool InputHandler::isMouseLeftPressed()       const { return currMouseL && !prevMouseL; }

bool InputHandler::isEscapeHeld()             const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape); }
