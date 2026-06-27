#pragma once
#include "GameMode.h"

class NEATManager;
class LevelManager;
class PlayState;

class SelfPlayingMode : public GameMode
{
    NEATManager* neat;

public:
    SelfPlayingMode();
    ~SelfPlayingMode() override;

    void  setupLevels(LevelManager& lm) override;
    bool  isComplete(PlayState& ps)     override;
    void  onLevelCleared(PlayState& ps) override;
    char* modeName()                    override;
};
