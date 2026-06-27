#include "HUD.h"
#include "PlayerSoldier.h"
#include "ScoreManager.h"
#include "DamageState.h"
#include "DamagableEntity.h"
#include "Level.h"
#include "BossLevel.h"
#include "Boss.h"

int HUD::writeStr(char* dst, int i, const char* src)
{
    while (*src) dst[i++] = *src++;
    return i;
}

int HUD::writeInt(char* dst, int i, int v)
{
    if (v < 0) { dst[i++] = '-'; v = -v; }
    char tmp[12];
    int  n = 0;
    if (v == 0) { tmp[n++] = '0'; }
    else { while (v > 0) { tmp[n++] = (char)('0' + (v % 10)); v /= 10; } }
    while (n > 0) dst[i++] = tmp[--n];
    return i;
}

HUD::HUD() : fontLoaded(false), overlaysLoaded(false),
             activeBannerIdx(-1), bannerTimer(0.0f),
             snapLevelIdx(0), snapLevelScore(0), snapLevelKills(0),
             snapClearBonus(0), snapTotal(0), snapValid(false)
{
    for (int i = 0; i < BANNER_COUNT; ++i) bannerLoaded[i] = false;
    fontLoaded = font.loadFromFile("assets/fonts/hud.ttf");
    if (!fontLoaded) fontLoaded = font.loadFromFile("assets/fonts/arial.ttf");
    if (!fontLoaded) fontLoaded = font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    if (fontLoaded)
    {
        scoreText.setFont(font);
        livesText.setFont(font);
        hpText.setFont(font);
        killsText.setFont(font);
        phaseText.setFont(font);
        bossInfoText.setFont(font);
        lvlScoreText.setFont(font);
        lvlKillsText.setFont(font);
        lvlBonusText.setFont(font);
        lvlTotalText.setFont(font);
    }

    scoreText.setCharacterSize(24);
    livesText.setCharacterSize(24);
    hpText.setCharacterSize(24);
    killsText.setCharacterSize(24);
    phaseText.setCharacterSize(28);
    bossInfoText.setCharacterSize(20);
    lvlScoreText.setCharacterSize(28);
    lvlKillsText.setCharacterSize(28);
    lvlBonusText.setCharacterSize(28);
    lvlTotalText.setCharacterSize(32);

    scoreText.setFillColor(sf::Color::White);
    livesText.setFillColor(sf::Color::White);
    hpText.setFillColor(sf::Color::White);
    killsText.setFillColor(sf::Color::Yellow);
    phaseText.setFillColor(sf::Color::Red);
    bossInfoText.setFillColor(sf::Color::Cyan);
    lvlScoreText.setFillColor(sf::Color::White);
    lvlKillsText.setFillColor(sf::Color::White);
    lvlBonusText.setFillColor(sf::Color::Yellow);
    lvlTotalText.setFillColor(sf::Color::White);

    scoreText.setPosition(20.0f, 10.0f);
    livesText.setPosition(20.0f, 40.0f);
    hpText.setPosition(20.0f, 70.0f);
    killsText.setPosition(20.0f, 100.0f);


    phaseText.setPosition(1380.0f, 10.0f);
    bossInfoText.setPosition(1100.0f, 45.0f);
    bool ok1 = texOverlayInjured.loadFromFile ("assets/overlays/red_25.png");
    bool ok2 = texOverlayCritical.loadFromFile("assets/overlays/red_75.png");
    bool ok3 = texOverlayDead.loadFromFile    ("assets/overlays/red_dead.png");
    overlaysLoaded = ok1 && ok2 && ok3;

    if (overlaysLoaded)
    {
        sprOverlayInjured.setTexture (texOverlayInjured);
        sprOverlayCritical.setTexture(texOverlayCritical);
        sprOverlayDead.setTexture    (texOverlayDead);
        sprOverlayInjured.setPosition (0.0f, 0.0f);
        sprOverlayCritical.setPosition(0.0f, 0.0f);
        sprOverlayDead.setPosition    (0.0f, 0.0f);
    }
    static const char* BANNER_PATHS[BANNER_COUNT] = {
        "assets/menu/level1_complete.png",
        "assets/menu/level2_complete.png",
        "assets/menu/level3_complete.png",
        "assets/menu/boss_complete.png"
    };
    for (int i = 0; i < BANNER_COUNT; ++i)
    {
        bannerLoaded[i] = bannerTex[i].loadFromFile(BANNER_PATHS[i]);
        if (bannerLoaded[i])
        {
            bannerSpr[i].setTexture(bannerTex[i]);
            sf::Vector2u sz = bannerTex[i].getSize();
            float bx = 800.0f - (float)sz.x * 0.5f;
            float by = 450.0f - (float)sz.y * 0.5f;
            bannerSpr[i].setPosition(bx, by);
        }
    }
}

void HUD::render(sf::RenderWindow& rw, PlayerSoldier* p, ScoreManager& sm,
                 Level* lvl)
{
    char buf[64];
    int  n;

    n = writeStr(buf, 0, "Score: ");
    n = writeInt(buf, n, sm.getScore());
    buf[n] = '\0';
    scoreText.setString(buf);



    n = writeStr(buf, 0, "Kills: ");
    n = writeInt(buf, n, sm.getEnemyKillCount());
    buf[n] = '\0';
    killsText.setString(buf);
    bool showPhase = false;
    bool showBossInfo = false;
    int  phaseId   = 0;
    if (lvl != nullptr)
    {
        BossLevel* bl = lvl->asBossLevel();
        if (bl != nullptr)
        {
            phaseId   = bl->getPhase();
            showPhase = (phaseId > 0);
            Boss* active = bl->getActiveBoss();
            if (active != nullptr && active->getIsAlive())
            {
                showBossInfo = true;
                const char* bossName = "Boss";
                if      (phaseId == 1) bossName = "Iron Nokana";
                else if (phaseId == 2) bossName = "HairBuster Riberts";
                else if (phaseId == 3) bossName = "Sea Satan";
                else if (phaseId == 4) bossName = "Ultimate Boss";

                n = writeStr(buf, 0, "Boss: ");
                n = writeStr(buf, n, bossName);
                n = writeStr(buf, n, "  HP ");
                n = writeInt(buf, n, active->getHealth());
                n = writeStr(buf, n, "/");
                n = writeInt(buf, n, active->getMaxHealth());
                n = writeStr(buf, n, "  @ (");
                coordSyst bp = active->getPosition();
                n = writeInt(buf, n, (int)bp.x);
                n = writeStr(buf, n, ", ");
                n = writeInt(buf, n, (int)bp.y);
                n = writeStr(buf, n, ")");
                buf[n] = '\0';
                bossInfoText.setString(buf);
            }
        }
    }
    if (showPhase)
    {
        n = writeStr(buf, 0, "Phase: ");
        n = writeInt(buf, n, phaseId);
        if (phaseId >= 5) { n = writeStr(buf, n, " (CLEAR)"); }
        buf[n] = '\0';
        phaseText.setString(buf);
    }

    if (p != nullptr)
    {
        n = writeStr(buf, 0, "Lives: ");
        n = writeInt(buf, n, p->getLives());
        buf[n] = '\0';
        livesText.setString(buf);

        n = writeStr(buf, 0, "HP:    ");
        n = writeInt(buf, n, p->getHealth());
        buf[n] = '\0';
        hpText.setString(buf);

        if (overlaysLoaded)
        {
            if (p->isInRespawnWindow())
            {
                rw.draw(sprOverlayDead);
            }
            else
            {
                DamageState* ds = p->getDamageState();
                if (ds != nullptr)
                {
                    float a = ds->hueAlpha();
                    if      (a >= 0.95f) rw.draw(sprOverlayDead);
                    else if (a >= 0.5f)  rw.draw(sprOverlayCritical);
                    else if (a >  0.0f)  rw.draw(sprOverlayInjured);
                }
            }
        }
    }

    if (fontLoaded)
    {
        rw.draw(scoreText);
        rw.draw(livesText);
        rw.draw(hpText);
        rw.draw(killsText);
        if (showPhase)    rw.draw(phaseText);
        if (showBossInfo) rw.draw(bossInfoText);
    }

    if (bannerTimer > 0.0f
        && activeBannerIdx >= 0
        && activeBannerIdx < BANNER_COUNT
        && bannerLoaded[activeBannerIdx])
    {
        rw.draw(bannerSpr[activeBannerIdx]);
        if (snapValid && fontLoaded)
        {
            char buf[64];
            int  n;

            n = writeStr(buf, 0, "Level ");
            n = writeInt(buf, n, snapLevelIdx);
            n = writeStr(buf, n, " Score: ");
            n = writeInt(buf, n, snapLevelScore);
            buf[n] = '\0';
            lvlScoreText.setString(buf);

            n = writeStr(buf, 0, "Kills this level: ");
            n = writeInt(buf, n, snapLevelKills);
            buf[n] = '\0';
            lvlKillsText.setString(buf);

            n = writeStr(buf, 0, "Survival Bonus: +");
            n = writeInt(buf, n, snapClearBonus);
            buf[n] = '\0';
            lvlBonusText.setString(buf);

            n = writeStr(buf, 0, "Total Run Score: ");
            n = writeInt(buf, n, snapTotal);
            buf[n] = '\0';
            lvlTotalText.setString(buf);

            sf::Vector2u bannerSz = bannerTex[activeBannerIdx].getSize();
            float bannerBottomY = 450.0f + (float)bannerSz.y * 0.5f;
            float lineH         = 36.0f;
            float panelH        = lineH * 4.0f;
            float panelTop      = bannerBottomY + 24.0f;


            if (panelTop + panelH > 880.0f)
            {
                float bannerTopY = 450.0f - (float)bannerSz.y * 0.5f;
                panelTop = bannerTopY - panelH - 24.0f;
                if (panelTop < 8.0f) panelTop = 8.0f;
            }


            sf::FloatRect br;
            br = lvlScoreText.getLocalBounds();
            lvlScoreText.setPosition(800.0f - br.width * 0.5f, panelTop);
            br = lvlKillsText.getLocalBounds();
            lvlKillsText.setPosition(800.0f - br.width * 0.5f, panelTop + lineH);
            br = lvlBonusText.getLocalBounds();
            lvlBonusText.setPosition(800.0f - br.width * 0.5f, panelTop + lineH * 2.0f);
            br = lvlTotalText.getLocalBounds();
            lvlTotalText.setPosition(800.0f - br.width * 0.5f, panelTop + lineH * 3.0f);

            rw.draw(lvlScoreText);
            rw.draw(lvlKillsText);
            rw.draw(lvlBonusText);
            rw.draw(lvlTotalText);
        }
    }
}
void HUD::showLevelBanner(int levelIdx, float seconds)
{
    int slot = levelIdx - 1;
    if (slot < 0 || slot >= BANNER_COUNT)
    {
        activeBannerIdx = -1;
        bannerTimer     = 0.0f;
        return;
    }
    activeBannerIdx = slot;
    bannerTimer     = seconds;
}

void HUD::tickBanner(float dt)
{
    if (bannerTimer > 0.0f)
    {
        bannerTimer -= dt;
        if (bannerTimer <= 0.0f)
        {
            bannerTimer = 0.0f;



            snapValid = false;
        }
    }
}

bool HUD::isBannerActive() const
{
    return bannerTimer > 0.0f;
}
void HUD::setLevelClearStats(int idx, int lvlScore, int lvlKills,
                             int clearBonus, int totalRun)
{
    snapLevelIdx   = idx;
    snapLevelScore = lvlScore;
    snapLevelKills = lvlKills;
    snapClearBonus = clearBonus;
    snapTotal      = totalRun;
    snapValid      = true;
}
