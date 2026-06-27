#pragma once
#include <SFML/Graphics.hpp>

class PlayerSoldier;
class ScoreManager;
class Level;

class HUD
{
    sf::Font    font;
    sf::Text    scoreText;
    sf::Text    livesText;
    sf::Text    hpText;
    sf::Text    killsText;
    sf::Text    phaseText;
    sf::Text    bossInfoText;
    bool        fontLoaded;

    sf::Texture texOverlayInjured;
    sf::Texture texOverlayCritical;
    sf::Texture texOverlayDead;
    sf::Sprite  sprOverlayInjured;
    sf::Sprite  sprOverlayCritical;
    sf::Sprite  sprOverlayDead;
    bool        overlaysLoaded;

    static const int BANNER_COUNT = 4;
    sf::Texture bannerTex[BANNER_COUNT];
    sf::Sprite  bannerSpr[BANNER_COUNT];
    bool        bannerLoaded[BANNER_COUNT];
    int         activeBannerIdx;
    float       bannerTimer;

    sf::Text    lvlScoreText;
    sf::Text    lvlKillsText;
    sf::Text    lvlBonusText;
    sf::Text    lvlTotalText;
    int         snapLevelIdx;
    int         snapLevelScore;
    int         snapLevelKills;
    int         snapClearBonus;
    int         snapTotal;
    bool        snapValid;

    int writeStr(char* dst, int i, const char* src);
    int writeInt(char* dst, int i, int v);

public:
    HUD();
    void render(sf::RenderWindow& rw, PlayerSoldier* p, ScoreManager& sm,
                Level* lvl);
    void  showLevelBanner(int levelIdx, float seconds);
    void  tickBanner(float dt);
    bool  isBannerActive() const;
    void  setLevelClearStats(int idx, int lvlScore, int lvlKills,
                             int clearBonus, int totalRun);
};
