#include "CampaignMode.h"
#include "LevelManager.h"

void CampaignMode::setupLevels(LevelManager& lm)
{
    lm.loadLevel(5, this);
}

bool CampaignMode::isComplete(PlayState& )
{
    return false;
}

void CampaignMode::onLevelCleared(PlayState& )
{}

char* CampaignMode::modeName()
{
    static char nm[] = "Campaign";
    return nm;
}
