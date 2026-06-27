#pragma once
#include <SFML/Graphics.hpp>

class GameMode;
class InputHandler;



class MainMenu
{
public:
    static const int OPT_SURVIVAL    = 0;
    static const int OPT_CAMPAIGN    = 1;
    static const int OPT_SELF_PLAY   = 2;
    static const int OPT_HIGHSCORES  = 3;
    static const int OPT_COUNT       = 4;

private:

    sf::Texture bgTex;
    sf::Sprite  bgSpr;


    sf::Texture titleTex;
    sf::Sprite  titleSpr;


    sf::Texture lblTex[OPT_COUNT];
    sf::Sprite  lblSpr[OPT_COUNT];


    sf::Texture cursorTex;
    sf::Sprite  cursorSpr;


    float btnX[OPT_COUNT], btnY[OPT_COUNT];
    float btnW[OPT_COUNT], btnH[OPT_COUNT];

    int        cursorIdx;
    bool       ready;
    bool       wantsHighScores;
    GameMode*  selectedMode;
    float      cursorPulseTimer;

    sf::Font   scoreFont;
    bool       scoreFontLoaded;
    sf::Text   scoreTitleText;
    sf::Text   scoreEntryText[8];
    sf::Text   scoreHintText;
    int        cachedScores[5];
    int        cachedScoreCount;
    bool       scoresFresh;

    bool mouseOverOption(int mx, int my, int i) const;
    void formatScoresIntoTexts();
    int  writeIntInto(char* dst, int idx, int v);

public:
    MainMenu();
    ~MainMenu();

    void update(float dt);
    void render(sf::RenderWindow& rw);
    void handleInput(InputHandler& in);

    GameMode* getSelectedMode();
    bool      isReady()          const { return ready; }
    bool      shouldShowScores() const { return wantsHighScores; }
    void      consumeScoreRequest()    { wantsHighScores = false; }
    int       getCursorIndex()   const { return cursorIdx; }
};
