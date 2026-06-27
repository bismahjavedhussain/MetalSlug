#pragma once

class Enemy;
class ScoreManager
{
    int currentScore;
    int bestScore;
    int enemyKillCount;
    int scoreAtLevelStart;
    int killsAtLevelStart;

public:
    ScoreManager();

    void addPoints(int n);
    void addEnemyKill(Enemy* e);
    void addEnemyKill(int scoreValue);
    void addBossKill(bool isUltimate);


    void addMeleeKillBonus();
    void addAerialKillBonus();
    void addMultiKillBonus(int enemyCount);
    void addMassacreBonus(int enemyCount);


    void addSurvivalLevelClearBonus();
    void addCampaignClearBonus();
    void addFlawlessVictoryBonus();
    void addLevelClearBonus();

    void resetForNewRun();
    void snapshotLevelStart();
    int  getLevelScoreDelta() const;
    int  getLevelKillsDelta() const;

    int getScore()          const { return currentScore;   }
    int getBest()           const { return bestScore;      }
    int getEnemyKillCount() const { return enemyKillCount; }

    static const int MAX_HIGH_SCORES = 5;
    void saveHighScore(int score);
    int  loadHighScores(int* outScores, int max);
};
