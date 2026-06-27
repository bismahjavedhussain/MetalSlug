#pragma once
#include <SFML/Graphics.hpp>


class InputHandler
{

    bool currSpace, prevSpace;
    bool currZ,     prevZ;
    bool currR,     prevR;
    bool currP,     prevP;
    bool currB,     prevB;
    bool currC,     prevC;
    bool currEnter, prevEnter;
    bool currE,     prevE;
    bool currEsc,   prevEsc;
    bool currF,     prevF;

    int  mouseX, mouseY;
    bool currMouseL, prevMouseL;

public:
    InputHandler();



    void poll(const sf::RenderWindow& window);

    bool isLeftHeld()  const;
    bool isRightHeld() const;
    bool isUpHeld()    const;
    bool isDownHeld()  const;
    bool isAimUpHeld() const;
    bool isFireHeld()  const;
    bool isJumpPressed() const;
    bool isThrowGrenadePressed() const;
    bool isMeleePressed() const;
    bool isSwitchCharacterPressed() const;
    bool isRewindPressed() const;
    bool isBestPlayerPressed() const;
    bool isStartPressed() const;
    bool isInteractPressed() const;
    bool isMenuBackPressed() const;
    bool isFusionPressed() const;


    int  getMouseX() const { return mouseX; }
    int  getMouseY() const { return mouseY; }
    bool isMouseLeftPressed() const;

    bool isEscapeHeld() const;
};
