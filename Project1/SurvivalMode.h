#pragma once
#include "GameMode.h"


class SurvivalMode : public GameMode
{
public:
    void  setupLevels(LevelManager& lm) override;
    bool  isComplete(PlayState& ps)     override;
    void  onLevelCleared(PlayState& ps) override;
    char* modeName()                    override;
};
