#include "MainMenu.h"
#include "SurvivalMode.h"
#include "CampaignMode.h"
#include "SelfPlayingMode.h"
#include "InputHandler.h"
#include "ScoreManager.h"

static const float CENTER_X    = 800.0f;
static const float COL_TOP_Y   = 360.0f;
static const float BTN_DY      = 70.0f;
static const float CURSOR_GAP  = 0.0f;


static const float TITLE_CENTER_X = 800.0f;
static const float TITLE_TOP_Y    = 20.0f;


static const char* MENU_LABEL_PATHS[MainMenu::OPT_COUNT] = {
    "assets/menu/survival.png",
    "assets/menu/campaign.png",
    "assets/menu/selfplay.png",
    "assets/menu/highscores.png"
};

MainMenu::MainMenu()
    : cursorIdx(0), ready(false), wantsHighScores(false),
      selectedMode(nullptr), cursorPulseTimer(0.0f),
      scoreFontLoaded(false), cachedScoreCount(0), scoresFresh(false)
{
    for (int i = 0; i < 5; ++i) cachedScores[i] = 0;


    scoreFontLoaded = scoreFont.loadFromFile("assets/fonts/hud.ttf");
    if (!scoreFontLoaded) scoreFontLoaded = scoreFont.loadFromFile("assets/fonts/arial.ttf");
    if (!scoreFontLoaded) scoreFontLoaded = scoreFont.loadFromFile("C:/Windows/Fonts/arial.ttf");

    if (scoreFontLoaded)
    {
        scoreTitleText.setFont(scoreFont);
        scoreTitleText.setString("HIGH SCORES");
        scoreTitleText.setCharacterSize(48);
        scoreTitleText.setFillColor(sf::Color::Yellow);
        scoreTitleText.setPosition(620.0f, 200.0f);

        for (int i = 0; i < 8; ++i)
        {
            scoreEntryText[i].setFont(scoreFont);
            scoreEntryText[i].setCharacterSize(32);
            scoreEntryText[i].setFillColor(sf::Color::White);
            scoreEntryText[i].setPosition(680.0f, 280.0f + (float)i * 40.0f);
        }

        scoreHintText.setFont(scoreFont);
        scoreHintText.setString("Press Esc to return");
        scoreHintText.setCharacterSize(20);
        scoreHintText.setFillColor(sf::Color(200, 200, 200));
        scoreHintText.setPosition(640.0f, 700.0f);
    }


    bgTex.loadFromFile("assets/menu/title_bg.png");
    bgSpr.setTexture(bgTex);
    bgSpr.setPosition(0.0f, 0.0f);


    titleTex.loadFromFile("assets/menu/title.png");
    titleSpr.setTexture(titleTex);
    {
        sf::Vector2u sz = titleTex.getSize();
        float tx = TITLE_CENTER_X - (float)sz.x * 0.45f;
        titleSpr.setPosition(tx, TITLE_TOP_Y);
    }


    cursorTex.loadFromFile("assets/menu/cursor1.png");
    cursorSpr.setTexture(cursorTex);

    for (int i = 0; i < OPT_COUNT; ++i)
    {
        lblTex[i].loadFromFile(MENU_LABEL_PATHS[i]);
        lblSpr[i].setTexture(lblTex[i]);

        sf::Vector2u sz = lblTex[i].getSize();
        btnW[i] = (float)sz.x;
        btnH[i] = (float)sz.y;
        btnX[i] = CENTER_X - btnW[i] * 0.5f;
        btnY[i] = COL_TOP_Y + (float)i * BTN_DY;

        lblSpr[i].setPosition(btnX[i], btnY[i]);
    }
}

MainMenu::~MainMenu()
{
    if (selectedMode != nullptr) { delete selectedMode; selectedMode = nullptr; }
}

void MainMenu::update(float dt)
{
    cursorPulseTimer += dt;
}

bool MainMenu::mouseOverOption(int mx, int my, int i) const
{
    return (float)mx >= btnX[i] && (float)mx <= btnX[i] + btnW[i]
        && (float)my >= btnY[i] && (float)my <= btnY[i] + btnH[i];
}

void MainMenu::handleInput(InputHandler& in)
{
    if (ready) return;


    if (wantsHighScores)
    {
        if (in.isMenuBackPressed())
        {
            wantsHighScores = false;
            scoresFresh     = false;
        }
        return;
    }

    int mx = in.getMouseX();
    int my = in.getMouseY();



    for (int i = 0; i < OPT_COUNT; ++i)
    {
        if (mouseOverOption(mx, my, i)) { cursorIdx = i; break; }
    }

    bool confirm = in.isStartPressed()
                || (in.isMouseLeftPressed() && mouseOverOption(mx, my, cursorIdx));

    if (confirm)
    {
        switch (cursorIdx)
        {
            case OPT_SURVIVAL:
                if (selectedMode == nullptr) selectedMode = new SurvivalMode();
                ready = true;
                break;
            case OPT_CAMPAIGN:
                if (selectedMode == nullptr) selectedMode = new CampaignMode();
                ready = true;
                break;
            case OPT_SELF_PLAY:
                if (selectedMode == nullptr) selectedMode = new SelfPlayingMode();
                ready = true;
                break;
            case OPT_HIGHSCORES:
                wantsHighScores = true;
                scoresFresh     = false;
                break;
            default: break;
        }
    }
}

void MainMenu::render(sf::RenderWindow& rw)
{
    rw.draw(bgSpr);
    rw.draw(titleSpr);

    if (wantsHighScores)
    {

        if (!scoresFresh)
        {
            ScoreManager sm;
            cachedScoreCount = sm.loadHighScores(cachedScores, 5);
            formatScoresIntoTexts();
            scoresFresh = true;
        }
        if (scoreFontLoaded)
        {
            rw.draw(scoreTitleText);
            int rows = (cachedScoreCount > 0) ? cachedScoreCount : 1;
            for (int i = 0; i < rows && i < 8; ++i)
                rw.draw(scoreEntryText[i]);
            rw.draw(scoreHintText);
        }
        return;
    }

    for (int i = 0; i < OPT_COUNT; ++i)
        rw.draw(lblSpr[i]);


    float phase = cursorPulseTimer * 3.0f;
    int   ip    = (int)phase;
    float f     = phase - (float)ip;
    if ((ip & 1) == 1) f = 1.0f - f;
    float scale = 0.95f + 0.10f * f;

    cursorSpr.setScale(scale, scale);



    float cx = btnX[cursorIdx] - CURSOR_GAP - (float)cursorTex.getSize().x;
    float cy = btnY[cursorIdx] + btnH[cursorIdx] * 0.5f
                                - (float)cursorTex.getSize().y * 0.5f;
    cursorSpr.setPosition(cx, cy);
    rw.draw(cursorSpr);
}




int MainMenu::writeIntInto(char* dst, int idx, int v)
{
    if (v < 0) { dst[idx++] = '-'; v = -v; }
    char tmp[12];
    int  n = 0;
    if (v == 0) { tmp[n++] = '0'; }
    else { while (v > 0) { tmp[n++] = (char)('0' + (v % 10)); v /= 10; } }
    while (n > 0) dst[idx++] = tmp[--n];
    return idx;
}

void MainMenu::formatScoresIntoTexts()
{
    if (!scoreFontLoaded) return;


    if (cachedScoreCount <= 0)
    {
        scoreEntryText[0].setString("(no runs yet)");
        return;
    }

    char buf[64];
    for (int i = 0; i < cachedScoreCount && i < 5; ++i)
    {
        int n = 0;

        buf[n++] = (char)('1' + i);
        buf[n++] = '.';
        buf[n++] = ' ';
        n = writeIntInto(buf, n, cachedScores[i]);
        buf[n] = '\0';
        scoreEntryText[i].setString(buf);
    }
}

GameMode* MainMenu::getSelectedMode()
{
    GameMode* m  = selectedMode;
    selectedMode = nullptr;
    return m;
}
