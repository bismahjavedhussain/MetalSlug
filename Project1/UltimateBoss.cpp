#include "UltimateBoss.h"
#include "IronNokana.h"
#include "HairBusterRiberts.h"
#include "SeaSatan.h"
#include "TileMap.h"
#include "DamageState.h"
#include "DamageSource.h"
#include "EntityAnims.h"
#include "SpriteAnimator.h"


const float UltimateBoss::kIntroDuration    = 3.0f;
const float UltimateBoss::kIntroCyclePeriod = 0.6f;

UltimateBoss::UltimateBoss(TextureManager& tm,
                           float spawnX,
                           float groundY,
                           float aerialY,
                           float aquaticY)
    : Boss(1500, 45),
      currentFormIdx(0),
      currentForm(nullptr),
      formTimer(0.0f),
      formTransitionInterval(12.5f),
      introTimer(kIntroDuration),
      introCycleTimer(kIntroCyclePeriod)
{


    formY[0] = groundY;
    formY[1] = aerialY;
    formY[2] = aquaticY;
    forms[0] = new IronNokana       (tm, spawnX, groundY);
    forms[1] = new HairBusterRiberts(tm, spawnX, aerialY);
    forms[2] = new SeaSatan         (tm, spawnX, aquaticY);


    for (int i = 0; i < NUM_FORMS; ++i)
    {
        if (forms[i] != nullptr) forms[i]->setMaxHealth(15);
    }

    width      = 192.0f;
    height     = 96.0f;
    position.x = spawnX;
    position.y = groundY;
    m_tex      = &tm;

    selectInitialForm();
}

UltimateBoss::~UltimateBoss()
{
    for (int i = 0; i < NUM_FORMS; ++i)
    {
        if (forms[i] != nullptr) { delete forms[i]; forms[i] = nullptr; }
    }
    currentForm = nullptr;
}

bool UltimateBoss::formAlive(int idx) const
{
    if (idx < 0 || idx >= NUM_FORMS) return false;
    return forms[idx] != nullptr && forms[idx]->getIsAlive();
}

void UltimateBoss::selectInitialForm()
{


    currentFormIdx = 0;
    currentForm    = forms[currentFormIdx];
}

void UltimateBoss::transitionForm()
{
    for (int step = 1; step <= NUM_FORMS; ++step)
    {
        int candidate = (currentFormIdx + step) % NUM_FORMS;
        if (formAlive(candidate))
        {
            currentFormIdx = candidate;
            currentForm    = forms[candidate];





            position.y = formY[currentFormIdx];
            currentForm->setPosition(position.x, position.y);
            return;
        }
    }

    isAlive = false;
}

bool UltimateBoss::canUseForm(Boss* form)
{
    return form != nullptr && form->getIsAlive();
}


bool UltimateBoss::checkRetreat() { return false; }

void UltimateBoss::takeDamage(int amt, DamageSource* src)
{
    if (introTimer > 0.0f) return;

    if (currentForm != nullptr)
        currentForm->takeDamage(amt, src);


    bool anyAlive = false;
    for (int i = 0; i < NUM_FORMS; ++i)
    {
        if (formAlive(i)) { anyAlive = true; break; }
    }
    if (!anyAlive) isAlive = false;
}

void UltimateBoss::update(TileMap& tm, float dt)
{
    if (!isAlive) return;

    if (introTimer > 0.0f)
    {
        introTimer      -= dt;
        introCycleTimer -= dt;



        if (introCycleTimer <= 0.0f)
        {
            introCycleTimer = kIntroCyclePeriod;
            currentFormIdx  = (currentFormIdx + 1) % NUM_FORMS;
            currentForm     = forms[currentFormIdx];
            position.y      = formY[currentFormIdx];
            if (currentForm != nullptr)
                currentForm->setPosition(position.x, position.y);
        }




        if (currentForm != nullptr)
            currentForm->update(tm, dt);




        if (introTimer <= 0.5f && currentForm != nullptr)
        {
            SpriteAnimator* a = currentForm->getRenderable();
            if (a != nullptr) a->play("damaged", true);
        }
        return;
    }

    if (currentForm != nullptr)
    {
        currentForm->update(tm, dt);
        position = currentForm->getPosition();

    }


    formTimer += dt;
    if (formTimer >= formTransitionInterval)
    {
        formTimer = 0.0f;
        transitionForm();
    }
}



void UltimateBoss::attack()
{
    if (introTimer > 0.0f) return;
    if (currentForm != nullptr) currentForm->attack();
}


void UltimateBoss::spawnMinions(EntityManager* em)
{
    if (introTimer > 0.0f) return;
    if (currentForm != nullptr) currentForm->spawnMinions(em);
}

SpriteAnimator* UltimateBoss::getRenderable()
{
    return (currentForm != nullptr) ? currentForm->getRenderable() : &m_anim;
}

void UltimateBoss::render(sf::RenderWindow& rw)
{
    if (currentForm != nullptr) currentForm->render(rw);
    else                        m_anim.draw(rw);
}
