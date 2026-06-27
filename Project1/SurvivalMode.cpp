#include "SurvivalMode.h"
#include "LevelManager.h"
#include "PlayState.h"
#include "Level.h"







static const bool DEV_OVERRIDE_START_LEVEL = true;
static const int  DEV_START_LEVEL          = 1;

void SurvivalMode::setupLevels(LevelManager& lm)
{
    int startIdx = DEV_OVERRIDE_START_LEVEL ? DEV_START_LEVEL : 1;
    lm.loadLevel(startIdx, this);
}




bool SurvivalMode::isComplete(PlayState& ps)
{
    LevelManager* lm = ps.getLevelManager();
    if (lm == nullptr) return false;
    Level* lvl = lm->getCurrent();
    if (lvl == nullptr) return false;
    return lm->getCurrentIdx() >= 4 && lvl->isComplete();
}





void SurvivalMode::onLevelCleared(PlayState& ps)
{
    LevelManager* lm = ps.getLevelManager();
    if (lm == nullptr) return;
    int idx = lm->getCurrentIdx();
    if (idx < 3)        ps.advanceLevel();
    else if (idx == 3)  lm->loadBossLevel();

}

char* SurvivalMode::modeName()
{
    static char nm[] = "Survival";
    return nm;
}
