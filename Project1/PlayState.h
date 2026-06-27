#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <SFML/Audio.hpp> 

class EntityManager;
class LevelManager;
class PlayerSoldier;
class GameMode;
class CollisionManager;
class ScoreManager;
class HUD;
class Camera;
class InputHandler;
class Projectile;
class TextureManager;
class Vehicle;

class PlayState : public GameState
{
    EntityManager*    entityMgr;
    LevelManager*     levelMgr;
    PlayerSoldier*    players[4];
    int               numPlayers;
    int               activePlayerIdx;
    GameMode*         mode;
    bool              developerModeActive;
    CollisionManager* collisionMgr;
    ScoreManager*     scoreMgr;
    HUD*              hud;
    Camera*           camera;
    TextureManager*   textures;

    Vehicle*          pilotedVehicle[4];

    sf::Texture       skyTex,       grassTopTex, dirtTex, stoneTex, bedrockTex, waterTex;
    sf::Sprite        skySpr,       grassTopSpr, dirtSpr, stoneSpr, bedrockSpr, waterSpr;

    static const int  BG_COUNT = 4;
    sf::Texture       levelBgTex[BG_COUNT];
    sf::Sprite        levelBgSpr[BG_COUNT];
    bool              levelBgLoaded[BG_COUNT];

    void loadTileSprites();

    void applyMouseAim(class InputHandler& in, class PlayerSoldier* p);

    bool   fusionUsedThisLevel;
    int    fusionUsedAtLevelIdx;
    class FusionCompanion* activeFusion;
    void   trySpawnFusionCompanion();
    bool   highscoreSaved;
    void   maybeSaveHighScore();

    bool   levelClearPending;
    float  levelClearDelay;
    sf::Music bgMusic;
    int currentTrackID; // Tracks which song is playing (0 = none, 1 = main, 2 = boss)
    void playLevelMusic(const char* filepath, int trackID);
    void updateMusicForLevel();
public:
    PlayState(GameMode* m);
    ~PlayState() override;

    void enter()   override;
    void exit()    override;
    void update(float dt)                 override;
    void render(sf::RenderWindow& rw)     override;
    void handleInput(InputHandler& in)    override;

    void switchCharacter();
    PlayerSoldier* getActivePlayer();


    bool           isGameOver() const;
    ScoreManager&  getScoreManager();
    Camera*        getCamera() { return camera; }
    EntityManager* getEntityManager() { return entityMgr; }
    LevelManager*  getLevelManager()  { return levelMgr; }

    void advanceLevel();
    void toggleDeveloperMode();
    void spawnProjectile(Projectile* p);
    void setMode(GameMode* m) { mode = m; }


    void tryEnterNearestVehicle();
    void tryExitVehicle();
    Vehicle* getActiveVehicle();
    void tryReleaseNearestPOW();
};
