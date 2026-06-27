#include "SelfPlayingMode.h"
#include "LevelManager.h"



SelfPlayingMode::SelfPlayingMode() : neat(nullptr) {}

SelfPlayingMode::~SelfPlayingMode()
{
    neat = nullptr;
}

void SelfPlayingMode::setupLevels(LevelManager& lm)
{
    lm.loadLevel(1, this);
}

bool SelfPlayingMode::isComplete(PlayState& )
{
    return false;
}

void SelfPlayingMode::onLevelCleared(PlayState& )
{

}

char* SelfPlayingMode::modeName()
{
    static char nm[] = "Self-Playing";
    return nm;
}
