#include "ScoreManager.h"
#include "Enemy.h"
#include <fstream>

ScoreManager::ScoreManager()
    : currentScore(0), bestScore(0), enemyKillCount(0),
      scoreAtLevelStart(0), killsAtLevelStart(0) {}

void ScoreManager::addPoints(int n)
{
    currentScore += n;
    if (currentScore > bestScore) bestScore = currentScore;
}

void ScoreManager::addEnemyKill(Enemy* e)
{
    if (e == nullptr) return;
    addPoints(e->getScoreValue());
    ++enemyKillCount;
}

void ScoreManager::addEnemyKill(int scoreValue)
{
    addPoints(scoreValue);
    ++enemyKillCount;
}

void ScoreManager::addBossKill(bool isUltimate)
{
    addPoints(isUltimate ? 1500 : 500);
}

void ScoreManager::addMeleeKillBonus()                { addPoints(50);  }
void ScoreManager::addAerialKillBonus()               { addPoints(100); }

void ScoreManager::addMultiKillBonus(int enemyCount)
{
    if (enemyCount == 2) addPoints(200);
}

void ScoreManager::addMassacreBonus(int enemyCount)
{
    if (enemyCount < 3) return;
    int extra = enemyCount - 3;
    addPoints(300 + extra * 50);
}

void ScoreManager::addSurvivalLevelClearBonus() { addPoints(1000); }
void ScoreManager::addCampaignClearBonus()      { addPoints(3000); }
void ScoreManager::addFlawlessVictoryBonus()    { addPoints(5000); }
void ScoreManager::addLevelClearBonus()         { addPoints(1000); }

void ScoreManager::resetForNewRun()
{
    currentScore      = 0;
    enemyKillCount    = 0;
    scoreAtLevelStart = 0;
    killsAtLevelStart = 0;
}

void ScoreManager::snapshotLevelStart()
{
    scoreAtLevelStart = currentScore;
    killsAtLevelStart = enemyKillCount;
}

int ScoreManager::getLevelScoreDelta() const
{
    return currentScore - scoreAtLevelStart;
}

int ScoreManager::getLevelKillsDelta() const
{
    return enemyKillCount - killsAtLevelStart;
}

int ScoreManager::loadHighScores(int* outScores, int max)
{
    if (outScores == nullptr || max <= 0) return 0;
    for (int i = 0; i < max; ++i) outScores[i] = 0;

    std::ifstream in("assets/highscores.txt");
    if (!in.is_open()) return 0;

    int count = 0;
    int v;
    while (count < max && (in >> v)) outScores[count++] = v;
    return count;
}

void ScoreManager::saveHighScore(int score)
{
    int top[MAX_HIGH_SCORES];
    int existing = loadHighScores(top, MAX_HIGH_SCORES);


    int merged[MAX_HIGH_SCORES + 1];
    for (int i = 0; i < existing; ++i) merged[i] = top[i];
    merged[existing] = score;
    int n = existing + 1;
    for (int i = 1; i < n; ++i)
    {
        int key = merged[i];
        int j   = i - 1;
        while (j >= 0 && merged[j] < key)
        {
            merged[j + 1] = merged[j];
            --j;
        }
        merged[j + 1] = key;
    }

    int writeCount = (n < MAX_HIGH_SCORES) ? n : MAX_HIGH_SCORES;
    std::ofstream out("assets/highscores.txt");
    if (!out.is_open()) return;
    for (int i = 0; i < writeCount; ++i) out << merged[i] << '\n';
}
