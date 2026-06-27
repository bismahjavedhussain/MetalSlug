#pragma once

class LevelManager;
class PlayState;
class GameMode
{
public:
    virtual ~GameMode() = default;
    virtual void  setupLevels(LevelManager& lm)    = 0;
    virtual bool  isComplete(PlayState& ps) = 0;
    virtual void  onLevelCleared(PlayState& ps)    = 0;
    virtual char* modeName()  = 0;
};
