#pragma once

#include "Boss.h"
#include "TextureManager.h"

class IronNokana;
class HairBusterRiberts;
class SeaSatan;
class TileMap;
class UltimateBoss : public Boss
{
private:
    static const int NUM_FORMS = 3;
    Boss* forms[NUM_FORMS];
    int  currentFormIdx;
    Boss*  currentForm;
    float formTimer;
    float formTransitionInterval;
    float formY[NUM_FORMS];
    float introTimer;
    float introCycleTimer;
    static const float  kIntroDuration;
    static const float  kIntroCyclePeriod;

    void selectInitialForm();
    bool formAlive(int idx) const;

public:
    UltimateBoss(TextureManager& tm,
                 float spawnX,
                 float groundY,
                 float aerialY,
                 float aquaticY);
    ~UltimateBoss() override;

    void update(TileMap& tm, float dt)  override;
    void attack()  override;
    void spawnMinions(EntityManager* em) override;
    bool checkRetreat() override;
    void takeDamage(int amt, DamageSource* src) override;

    SpriteAnimator* getRenderable() override;
    void render(sf::RenderWindow& rw)  override;

    void transitionForm();
    bool canUseForm(Boss* form);

    Enemy* clone() override { return new UltimateBoss(*this); }

    bool inIntro() const { return introTimer > 0.0f; }

    Boss* getCurrentForm() { return currentForm; }

    class Entity* takePendingShot() override
    {
        if (currentForm == nullptr) return nullptr;
        return currentForm->takePendingShot();
    }
    bool consumeMinionRequest() override
    {
        if (currentForm == nullptr) return false;
        return currentForm->consumeMinionRequest();
    }
    bool consumeCrateRequest() override
    {
        if (currentForm == nullptr) return false;
        return currentForm->consumeCrateRequest();
    }
    void requestCrateDrop() override
    {
        if (currentForm != nullptr) currentForm->requestCrateDrop();
    }

    void setChaseTarget(float x) override
    {
        Boss::setChaseTarget(x);
        if (currentForm != nullptr) currentForm->setChaseTarget(x);
    }
};
