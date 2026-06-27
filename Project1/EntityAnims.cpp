#include "EntityAnims.h"

static const char* M_STAND = "Sprites/Marco/stand.png";
static const char* M_WALK = "Sprites/Marco/walk.png";
static const char* M_RUN = "Sprites/Marco/run.png";
static const char* M_JUMP = "Sprites/Marco/jump.png";
static const char* M_CROUCH = "Sprites/Marco/crouch.png";
static const char* M_LAND = "Sprites/Marco/land.png";
static const char* M_DIE = "Sprites/Marco/die.png";
static const char* M_PRONE = "Sprites/Marco/prone.png";


static const char* M_PISTOL_IDLE = "Sprites/Marco/pistol_idle.png";
static const char* M_PISTOL_PREP = "Sprites/Marco/pistol_prep.png";
static const char* M_PISTOL_SHOOT = "Sprites/Marco/pistol_shoot.png";
static const char* M_PISTOL_PREP_UP = "Sprites/Marco/pistol_prep_up.png";
static const char* M_PISTOL_SHOOT_UP = "Sprites/Marco/pistol_shoot_up.png";
static const char* M_PISTOL_PREP_DN = "Sprites/Marco/pistol_prep_down.png";
static const char* M_PISTOL_SHOOT_DN = "Sprites/Marco/pistol_shoot_down.png";


static const char* M_HMG_IDLE = "Sprites/Marco/hmg_idle.png";
static const char* M_HMG_PREP_UP = "Sprites/Marco/hmg_prep_up.png";
static const char* M_HMG_PREP_DOWN = "Sprites/Marco/hmg_prep_down.png";
static const char* M_HMG_PREP_UP_TO_DOWN = "Sprites/Marco/hmg_transition_up_down.png";
static const char* M_HMG_SHOOT = "Sprites/Marco/hmg_shoot.png";
static const char* M_HMG_SHOOT_UP = "Sprites/Marco/hmg_shoot_up.png";
static const char* M_HMG_SHOOT_DN = "Sprites/Marco/hmg_shoot_down.png";

static const char* M_HMG_CROUCH = "Sprites/Marco/hmg_crouch.png";
static const char* M_HMG_CROUCH_SHOOT = "Sprites/Marco/hmg_crouch_shoot.png";
static const char* M_HMG_MELEE_CROUCH = "Sprites/Marco/hmg_melee_crouch.png";

static const char* M_HMG_PREP_LAIDBACK = "Sprites/Marco/hmg_prep_laidback.png";
static const char* M_HMG_SHOOT_LAIDBACK = "Sprites/Marco/hmg_shoot_laidback.png";



static const char* M_ROCKET_IDLE = "Sprites/Marco/rocket_idle.png";
static const char* M_ROCKET_PREP = "Sprites/Marco/rocket_prep.png";
static const char* M_ROCKET_SHOOT = "Sprites/Marco/rocket_shoot.png";
static const char* M_ROCKET_SHOOT_UP = "Sprites/Marco/rocket_shoot_up.png";
static const char* M_ROCKET_RELOAD = "Sprites/Marco/rocket_reload.png";


static const char* M_FLAME_IDLE = "Sprites/Marco/flame_idle.png";
static const char* M_FLAME_MELEE = "Sprites/Marco/flame_melee.png";
static const char* M_FLAME_SHOOT = "Sprites/Marco/flame_shoot.png";
static const char* M_FLAME_PREP = "Sprites/Marco/flame_prep.png";
static const char* M_FLAME_PREP_LAIDBACK = "Sprites/Marco/flame_prep_laidback.png";
static const char* M_FLAME_SHOOT_LAIDBACK = "Sprites/Marco/flame_shoot_laidback.png";
static const char* M_FLAME_CROUCH_PREP = "Sprites/Marco/flame_crouch_prep.png";
static const char* M_FLAME_CROUCH = "Sprites/Marco/flame_crouch.png";
static const char* M_FLAME_CROUCH_SHOOT = "Sprites/Marco/flame_crouch_shoot.png";
static const char* M_FLAME_DOWN = "Sprites/Marco/flame_prep_down.png";
static const char* M_FLAME_PREP_LEFT = "Sprites/Marco/flame_prep_left.png";
static const char* M_FLAME_SHOOT_LEFT = "Sprites/Marco/flame_shoot_left.png";
static const char* M_FLAME_PREP_360 = "Sprites/Marco/flame_prep_360.png";
static const char* M_FLAME_SHOOT_360 = "Sprites/Marco/flame_360.png";
static const char* M_FLAME_SHOOT_UP = "Sprites/Marco/flame_shoot_up.png";
static const char* M_FLAME_SHOOT_DN = "Sprites/Marco/flame_shoot_down.png";


static const char* M_LASER_IDLE = "Sprites/Marco/laser_idle.png";
static const char* M_LASER_SHOOT = "Sprites/Marco/laser_shoot.png";
static const char* M_LASER_SHOOT_UP = "Sprites/Marco/laser_shoot_up.png";


static const char* M_MELEE_PREP = "Sprites/Marco/melee_prep.png";
static const char* M_MELEE_SWING = "Sprites/Marco/melee_swing.png";
static const char* M_GRENADE_THROW = "Sprites/Marco/grenade_throw.png";
static const char* M_GRENADE_IDLE  = "Sprites/Marco/grenade_idle.png";


static const char* M_HURT = "Sprites/Marco/hurt.png";
static const char* M_BURN = "Sprites/Marco/burn.png";

void setupMarcoNormal(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("stand",            "Sprites/Marco/pistol_prep.png",       4, 0.22f, true,  tm);
    a.addClipAuto("run",              "Sprites/Marco/pistol_run.png",        5, 0.10f, true,  tm);
    a.addClipAuto("pistol_jump",      "Sprites/Marco/pistol_jump.png",       4, 0.12f, false, tm);
    a.addClipAuto("die",              M_DIE,                                19, 0.10f, false, tm);
    a.addClipAuto("hurt",             M_HURT,                               19, 0.07f, false, tm);


    a.addClipAuto("pistol_idle",       "Sprites/Marco/pistol_prep.png",       4, 0.22f, true,  tm);
    a.addClipAuto("pistol_run",        "Sprites/Marco/pistol_run.png",        5, 0.10f, true,  tm);
    a.addClipAuto("pistol_shoot",      "Sprites/Marco/pistol_shoot.png",      5, 0.09f, true,  tm);
    a.addClipAuto("pistol_shoot_up",   "Sprites/Marco/pistol_shoot_up.png",   4, 0.09f, true,  tm);
    a.addClipAuto("pistol_shoot_down", "Sprites/Marco/pistol_shoot_down.png", 4, 0.09f, true,  tm);
    a.addClipAuto("pistol_shoot_left", "Sprites/Marco/pistol_shoot_left.png", 5, 0.09f, false, tm);
    a.addClipAuto("pistol_prep_up",    "Sprites/Marco/pistol_shoot_up.png",   4, 0.10f, false, tm);
    a.addClipAuto("pistol_prep_down",  "Sprites/Marco/pistol_shoot_down.png", 3, 0.10f, false, tm);


    a.addClipAuto("hmg_idle",          "Sprites/Marco/hmg_run.png",           4, 0.18f, true,  tm);
    a.addClipAuto("hmg_run",           "Sprites/Marco/hmg_run.png",           3, 0.10f, true,  tm);
    a.addClipAuto("hmg_shoot",         "Sprites/Marco/hmg_shoot.png",         4, 0.07f, true,  tm);
    a.addClipAuto("hmg_shoot_up",      "Sprites/Marco/hmg_shoot_up.png",      4, 0.07f, true,  tm);
    a.addClipAuto("hmg_shoot_down",    "Sprites/Marco/hmg_shoot_down.png",    4, 0.07f, true,  tm);


    a.addClipAuto("rocket_idle",       M_ROCKET_IDLE,      3, 0.20f, true,  tm);
    a.addClipAuto("rocket_shoot",      M_ROCKET_SHOOT,     2, 0.10f, false, tm);
    a.addClipAuto("rocket_shoot_up",   M_ROCKET_SHOOT_UP,  2, 0.10f, false, tm);
    a.addClipAuto("rocket_reload",     M_ROCKET_RELOAD,    5, 0.20f, false, tm);


    a.addClipAuto("flame_idle",        M_FLAME_IDLE,       3, 0.20f, true,  tm);
    a.addClipAuto("flame_shoot",       M_FLAME_SHOOT,      4, 0.07f, true,  tm);
    a.addClipAuto("flame_shoot_up",    M_FLAME_SHOOT_UP,   4, 0.07f, true,  tm);
    a.addClipAuto("flame_shoot_down",  M_FLAME_SHOOT_DN,   4, 0.07f, true,  tm);


    a.addClipAuto("laser_idle",        M_LASER_IDLE,       3, 0.20f, true,  tm);
    a.addClipAuto("laser_shoot",       M_LASER_SHOOT,      2, 0.05f, false, tm);
    a.addClipAuto("laser_shoot_up",    M_LASER_SHOOT_UP,   2, 0.05f, false, tm);


    a.addClipAuto("melee_prep",        M_MELEE_PREP,       7, 0.08f, false, tm);
    a.addClipAuto("melee_swing",       M_MELEE_SWING,      6, 0.07f, false, tm);
    a.addClipAuto("grenade_throw",     M_GRENADE_THROW,    5, 0.08f, false, tm);
    a.addClipAuto("grenade_idle",      M_GRENADE_IDLE,     4, 0.15f, true,  tm);

    a.play("pistol_idle");
}


static const char* MM_TRANSFORM            = "Sprites/MarcoMummy/transform_in.png";
static const char* MM_WALK                 = "Sprites/MarcoMummy/walk.png";
static const char* MM_STAND                = "Sprites/MarcoMummy/stand.png";
static const char* MM_CROUCH_START         = "Sprites/MarcoMummy/crouch_start.png";
static const char* MM_CROUCH               = "Sprites/MarcoMummy/crouch.png";
static const char* MM_GRENADE_CROUCH       = "Sprites/MarcoMummy/grenade_crouch.png";
static const char* MM_PISTOL_PREP          = "Sprites/MarcoMummy/pistol_prep.png";
static const char* MM_PISTOL_PREP_UP       = "Sprites/MarcoMummy/pistol_prep_up.png";
static const char* MM_PISTOL_PREP_DOWN     = "Sprites/MarcoMummy/pistol_prep_down.png";
static const char* MM_PISTOL_SHOOT         = "Sprites/MarcoMummy/pistol_shoot.png";
static const char* MM_PISTOL_SHOOT_UP      = "Sprites/MarcoMummy/pistol_shoot_up.png";
static const char* MM_PISTOL_SHOOT_DOWN    = "Sprites/MarcoMummy/pistol_shoot_down.png";
static const char* MM_PISTOL_SHOOT_CROUCH  = "Sprites/MarcoMummy/pistol_shoot_crouch.png";
static const char* MM_CURSE_BURST          = "Sprites/MarcoMummy/curse_burst.png";
static const char* MM_CURSE_FADE           = "Sprites/MarcoMummy/curse_fade.png";

static const char* MU_TRANSFORM       = "Sprites/_LegacyMU/transform.png";
static const char* MU_STAND           = "Sprites/_LegacyMU/stand.png";
static const char* MU_WALK            = "Sprites/_LegacyMU/walk.png";
static const char* MU_PISTOL_SHOOT    = "Sprites/_LegacyMU/pistol_shoot.png";
static const char* MU_PISTOL_SHOOT_UP = "Sprites/_LegacyMU/pistol_shoot_up.png";
static const char* MU_KNIFE_SWING     = "Sprites/_LegacyMU/knife_swing.png";
static const char* MU_GRENADE_THROW   = "Sprites/_LegacyMU/grenade_throw.png";
static const char* MU_DIE             = "Sprites/_LegacyMU/die.png";


static const char* MUND_TRANSFORM        = "Sprites/MarcoUndead/transform_in.png";
static const char* MUND_WALK             = "Sprites/MarcoUndead/walk.png";
static const char* MUND_REVIVAL          = "Sprites/MarcoUndead/revival.png";
static const char* MUND_HURT             = "Sprites/MarcoUndead/hurt.png";
static const char* MUND_STRIKE           = "Sprites/MarcoUndead/strike.png";
static const char* MUND_PISTOL_SHOOT     = "Sprites/MarcoUndead/pistol_hand_shoot.png";
static const char* MUND_PISTOL_SHOOT_UP  = "Sprites/MarcoUndead/pistol_hand_shoot_up.png";
static const char* MUND_PISTOL_PREP      = "Sprites/MarcoUndead/pistol_prep.png";
static const char* MUND_PISTOL_PREP_LEFT = "Sprites/MarcoUndead/pistol_prep_left.png";
static const char* MUND_END_INTENSIFIES  = "Sprites/MarcoUndead/ending_intensifies.png";
static const char* MUND_END_STATE        = "Sprites/MarcoUndead/ending_state.png";

static const char* MF_STAND                   = "Sprites/MarcoFat/stand.png";
static const char* MF_WALK                    = "Sprites/MarcoFat/walk.png";
static const char* MF_EXIT                    = "Sprites/MarcoFat/exit.png";


static const char* MF_PISTOL_TRANSFORM        = "Sprites/MarcoFat/pistol_transform.png";
static const char* MF_PISTOL_UP               = "Sprites/MarcoFat/pistol_up.png";
static const char* MF_PISTOL_LAIDBACK         = "Sprites/MarcoFat/pistol_laidback.png";
static const char* MF_PISTOL_PREP_UP          = "Sprites/MarcoFat/pistol_prep_up.png";
static const char* MF_PISTOL_PREP_DOWN        = "Sprites/MarcoFat/pistol_prep_down.png";
static const char* MF_PISTOL_PREP_LAIDBACK    = "Sprites/MarcoFat/pistol_prep_laidback.png";
static const char* MF_PISTOL_SHOOT            = "Sprites/MarcoFat/pistol_shoot.png";
static const char* MF_PISTOL_SHOOT_UP         = "Sprites/MarcoFat/pistol_shoot_up.png";
static const char* MF_PISTOL_SHOOT_DOWN       = "Sprites/MarcoFat/pistol_shoot_down.png";
static const char* MF_PISTOL_SHOOT_LAIDBACK   = "Sprites/MarcoFat/pistol_shoot_laidback.png";


static const char* MF_HMG_TRANSFORM           = "Sprites/MarcoFat/hmg_transform.png";
static const char* MF_HMG_UP                  = "Sprites/MarcoFat/hmg_up.png";
static const char* MF_HMG_360                 = "Sprites/MarcoFat/hmg_360.png";
static const char* MF_HMG_MELEE               = "Sprites/MarcoFat/hmg_meleeidk.png";
static const char* MF_HMG_PREP                = "Sprites/MarcoFat/hmg_prep.png";
static const char* MF_HMG_PREP_DOWN           = "Sprites/MarcoFat/hmg_prep_down.png";
static const char* MF_HMG_SHOOT               = "Sprites/MarcoFat/hmg_shoot.png";
static const char* MF_HMG_SHOOT_UP            = "Sprites/MarcoFat/hmg_shoot_up.png";
static const char* MF_HMG_SHOOT_DOWN          = "Sprites/MarcoFat/hmg_shoot_down.png";

static const char* T_STAND            = "Sprites/Tarma/stand.png";
static const char* T_IDLE             = "Sprites/Tarma/idle.png";
static const char* T_WALK             = "Sprites/Tarma/walk.png";
static const char* T_RUN              = "Sprites/Tarma/run.png";
static const char* T_JUMP_UP          = "Sprites/Tarma/jump_up.png";
static const char* T_JUMP_DN          = "Sprites/Tarma/jump_down.png";
static const char* T_LAND             = "Sprites/Tarma/land.png";
static const char* T_CROUCH           = "Sprites/Tarma/crouch.png";
static const char* T_PISTOL_SHOOT     = "Sprites/Tarma/pistol_shoot.png";
static const char* T_PISTOL_SHOOT_UP  = "Sprites/Tarma/pistol_shoot_up.png";
static const char* T_HMG_SHOOT        = "Sprites/Tarma/hmg_shoot.png";
static const char* T_HMG_SHOOT_UP     = "Sprites/Tarma/hmg_shoot_up.png";
static const char* T_ROCKET_SHOOT     = "Sprites/Tarma/rocket_shoot.png";
static const char* T_ROCKET_SHOOT_UP  = "Sprites/Tarma/rocket_shoot_up.png";
static const char* T_FLAME_SHOOT      = "Sprites/Tarma/flame_shoot.png";
static const char* T_FLAME_SHOOT_UP   = "Sprites/Tarma/flame_shoot_up.png";
static const char* T_LASER_SHOOT      = "Sprites/Tarma/laser_shoot.png";
static const char* T_SHOOT            = T_PISTOL_SHOOT;
static const char* T_MELEE            = "Sprites/Tarma/melee.png";
static const char* T_GRENADE          = "Sprites/Tarma/grenade.png";
static const char* T_HURT             = "Sprites/Tarma/hurt.png";
static const char* T_DIE              = "Sprites/Tarma/die.png";
static const char* T_MUMMY            = "Sprites/Tarma/mummy.png";
static const char* T_UNDEAD           = "Sprites/Tarma/undead.png";

static const char* E_WALK               = "Sprites/Eri/walk.png";
static const char* E_RUN                = "Sprites/Eri/run.png";
static const char* E_JUMP_UP            = "Sprites/Eri/jump_up.png";
static const char* E_ROLLING            = "Sprites/Eri/rolling.png";


static const char* E_LEGS_WALK          = "Sprites/Eri/legs/walk.png";
static const char* E_LEGS_RUN           = "Sprites/Eri/legs/run.png";
static const char* E_LEGS_JUMP_UP       = "Sprites/Eri/legs/jump_up.png";


static const char* E_PISTOL_IDLE              = "Sprites/Eri/pistol_idle.png";
static const char* E_PISTOL_PREP              = "Sprites/Eri/pistol_prep.png";
static const char* E_PISTOL_PREP_UP           = "Sprites/Eri/pistol_prep_up.png";
static const char* E_PISTOL_PREP_DOWN         = "Sprites/Eri/pistol_prep_down.png";
static const char* E_PISTOL_PREP_LAIDBACK     = "Sprites/Eri/pistol_prep_laidback.png";
static const char* E_PISTOL_PREP_CROUCH       = "Sprites/Eri/pistol_prep_crouch.png";
static const char* E_PISTOL_SHOOT             = "Sprites/Eri/pistol_shoot.png";
static const char* E_PISTOL_SHOOT_UP          = "Sprites/Eri/pistol_shoot_up.png";
static const char* E_PISTOL_SHOOT_DOWN        = "Sprites/Eri/pistol_shoot_down.png";
static const char* E_PISTOL_SHOOT_LAIDBACK    = "Sprites/Eri/pistol_shoot_laidback.png";
static const char* E_PISTOL_CROUCH            = "Sprites/Eri/pistol_crouch.png";
static const char* E_PISTOL_CROUCH_PREP       = "Sprites/Eri/pistol_crouch_prep.png";
static const char* E_PISTOL_LOADING           = "Sprites/Eri/pistol_loading.png";
static const char* E_PISTOL_LOADING_CROUCH    = "Sprites/Eri/pistol_loading_crouch.png";
static const char* E_PISTOL_KICK              = "Sprites/Eri/pistol_kick.png";
static const char* E_PISTOL_MELLEE            = "Sprites/Eri/pistol_mellee.png";
static const char* E_PISTOL_MELLEE_CROUCH     = "Sprites/Eri/pistol_mellee_crouch.png";
static const char* E_PISTOL_JUMP_GLOW         = "Sprites/Eri/pistol_jump_glow.png";
static const char* E_PISTOL_TOPPLING          = "Sprites/Eri/pistol_toppling.png";


static const char* E_FLAME_IDLE               = "Sprites/Eri/flame_idle.png";
static const char* E_FLAME_PREP_UP            = "Sprites/Eri/flame_prep_up.png";
static const char* E_FLAME_PREP_DOWN          = "Sprites/Eri/flame_prep_down.png";
static const char* E_FLAME_PREP_LAIDBACK      = "Sprites/Eri/flame_prep_laidback.png";
static const char* E_FLAME_PREP_CROUCH        = "Sprites/Eri/flame_prep_crouch.png";
static const char* E_FLAME_PREP_UP_CROUCH     = "Sprites/Eri/flame_prep_up_crouch.png";
static const char* E_FLAME_PRE_CROUCH         = "Sprites/Eri/flame_pre_crouch.png";
static const char* E_FLAME_SHOOT              = "Sprites/Eri/flame_shoot.png";
static const char* E_FLAME_SHOOT_UP           = "Sprites/Eri/flame_shoot_up.png";
static const char* E_FLAME_SHOOT_DOWN         = "Sprites/Eri/flame_shoot_down.png";
static const char* E_FLAME_SHOOT_LAIDBACK     = "Sprites/Eri/flame_shoot_laidback.png";
static const char* E_FLAME_SHOOT_CROUCH       = "Sprites/Eri/flame_shoot_crouch.png";
static const char* E_FLAME_SHOOT_AIM_UP       = "Sprites/Eri/flame_shoot_aim_up.png";
static const char* E_FLAME_SHOOT_AIM_DOWN     = "Sprites/Eri/flame_shoot_aim_down.png";
static const char* E_FLAME_SHOOT_DOWN_TO_UP   = "Sprites/Eri/flame_shoot_down_to_up.png";
static const char* E_FLAME_CROUCH             = "Sprites/Eri/flame_crouch.png";
static const char* E_FLAME_KICK               = "Sprites/Eri/flame_kick.png";
static const char* E_FLAME_MELLEE_SWING       = "Sprites/Eri/flame_mellee_swing.png";
static const char* E_FLAME_JUMP_GLOW          = "Sprites/Eri/flame_jump_glow.png";
static const char* E_FLAME_TOPPLE             = "Sprites/Eri/flame_topple.png";
static const char* E_FLAME_HURT               = "Sprites/Eri/flame_hurt.png";

static const char* F_STAND            = "Sprites/Fio/stand.png";
static const char* F_IDLE             = "Sprites/Fio/idle.png";
static const char* F_WALK             = "Sprites/Fio/walk.png";
static const char* F_RUN              = "Sprites/Fio/run.png";
static const char* F_JUMP_UP          = "Sprites/Fio/jump_up.png";
static const char* F_JUMP_DN          = "Sprites/Fio/jump_down.png";
static const char* F_LAND             = "Sprites/Fio/land.png";
static const char* F_CROUCH           = "Sprites/Fio/crouch.png";
static const char* F_PISTOL_SHOOT     = "Sprites/Fio/pistol_shoot.png";
static const char* F_PISTOL_SHOOT_UP  = "Sprites/Fio/pistol_shoot_up.png";
static const char* F_HMG_SHOOT        = "Sprites/Fio/hmg_shoot.png";
static const char* F_HMG_SHOOT_UP     = "Sprites/Fio/hmg_shoot_up.png";
static const char* F_ROCKET_SHOOT     = "Sprites/Fio/rocket_shoot.png";
static const char* F_FLAME_SHOOT      = "Sprites/Fio/flame_shoot.png";
static const char* F_LASER_SHOOT      = "Sprites/Fio/laser_shoot.png";
static const char* F_SHOOT            = F_PISTOL_SHOOT;
static const char* F_MELEE            = "Sprites/Fio/melee.png";
static const char* F_GRENADE          = "Sprites/Fio/grenade.png";
static const char* F_HURT             = "Sprites/Fio/hurt.png";
static const char* F_DIE              = "Sprites/Fio/die.png";
static const char* F_MUMMY            = "Sprites/Fio/mummy.png";
static const char* F_UNDEAD           = "Sprites/Fio/undead.png";

static const char* R_IDLE          = "Sprites/Rebel/idle.png";
static const char* R_WALK          = "Sprites/Rebel/walk.png";
static const char* R_RUN           = "Sprites/Rebel/run.png";
static const char* R_HURT          = "Sprites/Rebel/hurt.png";
static const char* R_WIN           = "Sprites/Rebel/win.png";
static const char* R_SHOOT         = "Sprites/Rebel/rebelShooting1.png";
static const char* R_SHOOT360      = "Sprites/Rebel/shoot360.png";
static const char* R_SHIELD_WEAPON = "Sprites/Rebel/Sheild Soldier (weapon).png";


static const char* S_WALK   = "Sprites/Shielded/walk.png";
static const char* S_BLOCK  = "Sprites/Shielded/block.png";
static const char* S_SHOOT  = "Sprites/Shielded/shoot.png";
static const char* S_KNIFE  = "Sprites/Shielded/knife.png";


static const char* B_IDLE   = "Sprites/Bazooka/idle.png";
static const char* B_WALK   = "Sprites/Bazooka/walk.png";
static const char* B_RUN    = "Sprites/Bazooka/run.png";
static const char* B_HURT   = "Sprites/Bazooka/hurt.png";

static const char* G_IDLE   = "Sprites/Grenadier/idle.png";
static const char* G_WALK   = "Sprites/Grenadier/walk.png";
static const char* G_THROW_PREP = "Sprites/Grenadier/throw_prep.png";
static const char* G_THROW  = "Sprites/Grenadier/throw.png";
static const char* G_DIE    = "Sprites/Grenadier/die.png";

static const char* P_CHUTE_OPEN = "Sprites/Paratroopers/paratype01.png";
static const char* P_CHUTE_FALL = "Sprites/Paratroopers/paratype01.png";
static const char* P_LAND       = "Sprites/Paratroopers/paratype01.png";
static const char* P_DIE        = "Sprites/Paratroopers/paratype01.png";

static const char* MMY_WALK             = "Sprites/Mummy/walk.png";
static const char* MMY_WALK_BURNING     = "Sprites/Mummy/walk_burning.png";
static const char* MMY_WALK_RIGHT_LEFT  = "Sprites/Mummy/walk_right_left.png";
static const char* MMY_FALLING_BURNING  = "Sprites/Mummy/falling_burning.png";
static const char* MMY_FALLING_HANGING  = "Sprites/Mummy/falling_in_hanging.png";
static const char* MMY_HANG_BURNING     = "Sprites/Mummy/hang_burning.png";
static const char* MMY_HANGING          = "Sprites/Mummy/hanging.png";
static const char* MMY_DIE              = "Sprites/Mummy/die.png";

static const char* Z_STAND       = "Sprites/Zombie/stand.png";
static const char* Z_WALK        = "Sprites/Zombie/walk.png";
static const char* Z_EMERGE      = "Sprites/Zombie/emerge.png";
static const char* Z_COLLAPSE    = "Sprites/Zombie/collapse.png";
static const char* Z_BURN_ONE    = "Sprites/Zombie/burn_phase_one.png";
static const char* Z_BURN_TWO    = "Sprites/Zombie/burn_phase_two.png";

static const char* MA_IDLE                 = "Sprites/Martian/idle.png";
static const char* MA_WALK                 = "Sprites/Martian/walk.png";
static const char* MA_TURN                 = "Sprites/Martian/turn.png";
static const char* MA_JUMPING              = "Sprites/Martian/jumping.png";
static const char* MA_FALLING              = "Sprites/Martian/falling.png";
static const char* MA_SHOOT                = "Sprites/Martian/shoot.png";
static const char* MA_SHOOT_PREP           = "Sprites/Martian/shoot_prep.png";
static const char* MA_TRAJECTORY           = "Sprites/Martian/trajectory.png";
static const char* MA_TELEPORT_ONE         = "Sprites/Martian/teleport_phase_one.png";
static const char* MA_TELEPORT_TWO         = "Sprites/Martian/teleport_phase_two.png";
static const char* MA_DEATH_ONE            = "Sprites/Martian/death_phase_one.png";
static const char* MA_DEATH_TWO            = "Sprites/Martian/death_phase_two.png";
static const char* MA_DEATH_THREE          = "Sprites/Martian/death_phase_three.png";
static const char* MA_BURN_DEATH_ONE       = "Sprites/Martian/burn_death_phase_one.png";
static const char* MA_BURN_DEATH_TWO       = "Sprites/Martian/burn_death_phase_two.png";
static const char* MA_BURN_DEATH_THREE     = "Sprites/Martian/burn_death_phase_three.png";

static const char* TA_IDLE      = "Sprites/Tara/idle.png";
static const char* TA_FLY_DN    = "Sprites/Tara/fly_down.png";
static const char* TA_FLY_UP    = "Sprites/Tara/fly_up.png";

static const char* TA_DROP_BOMB = "Sprites/Tara/drop_bomb.png";
static const char* TA_PROP      = "Sprites/Tara/prop.png";
static const char* TA_EXPLODE   = "Sprites/Tara/explode.png";
static const char* TA_PILOT     = "Sprites/Tara/pilot.png";

static const char* BR_IDLE             = "Sprites/Bradley/idle.png";
static const char* BR_WALKING          = "Sprites/Bradley/walking.png";
static const char* BR_LAUNCHER_IDLE    = "Sprites/Bradley/launcherdown(idle).png";
static const char* BR_LAUNCHER_WALKING = "Sprites/Bradley/launcherdown(walking).png";
static const char* BR_WRECKED          = "Sprites/Bradley/wrecked.png";
static const char* BR_EXPLODE          = "Sprites/Bradley/explode.png";


static const char* SU_MOVE          = "Sprites/Sub/move.png";
static const char* SU_TURNING       = "Sprites/Sub/turning.png";
static const char* SU_GET_HIT       = "Sprites/Sub/get_hit.png";
static const char* SU_FALLING_APART = "Sprites/Sub/falling_apart.png";
static const char* SU_DEBRIS        = "Sprites/Sub/debris.png";

static const char* MS_IDLE                  = "Sprites/MetalSlug/idle.png";
static const char* MS_MOVE                  = "Sprites/MetalSlug/move.png";
static const char* MS_FIRE                  = "Sprites/MetalSlug/shoot.png";
static const char* MS_JUMP                  = "Sprites/MetalSlug/jump.png";
static const char* MS_LAND                  = "Sprites/MetalSlug/land.png";
static const char* MS_FORWARD_ACCEL         = "Sprites/MetalSlug/forward_acceleration.png";
static const char* MS_GROUCHING             = "Sprites/MetalSlug/grouching.png";
static const char* MS_HIT                   = "Sprites/MetalSlug/hit.png";


static const char* MS_BACKWARD_ACCEL        = "Sprites/_LegacyMS/backward_acceleration.png";
static const char* MS_FORWARD_ACCEL_PILOT   = "Sprites/_LegacyMS/forward_acceleration(pilot).png";
static const char* MS_BACKWARD_ACCEL_PILOT  = "Sprites/_LegacyMS/backward_acceleration(pilot).png";
static const char* MS_DRIVING_PILOT         = "Sprites/_LegacyMS/driving(pilot).png";
static const char* MS_SHOOTING_PILOT        = "Sprites/_LegacyMS/shooting(pilot).png";
static const char* MS_TILT_UP               = "Sprites/_LegacyMS/tilt_up.png";
static const char* MS_TILT_DN               = "Sprites/_LegacyMS/tilt_down.png";
static const char* MS_VULCAN                = "Sprites/_LegacyMS/vulcan.png";
static const char* MS_DAMAGED               = "Sprites/_LegacyMS/damaged.png";
static const char* MS_EXPLODE               = "Sprites/_LegacyMS/explode.png";


static const char* SF_IDLE     = "Sprites/SlugFlyer/idle.png";
static const char* SF_STRAFE   = "Sprites/SlugFlyer/strafe.png";
static const char* SF_FLY_DN   = "Sprites/SlugFlyer/fly_down.png";
static const char* SF_FLY_UP   = "Sprites/SlugFlyer/fly_up.png";
static const char* SF_LOOP     = "Sprites/SlugFlyer/loop.png";
static const char* SF_FIRE     = "Sprites/SlugFlyer/fire.png";
static const char* SF_MISSILE  = "Sprites/SlugFlyer/missile.png";
static const char* SF_DAMAGED  = "Sprites/SlugFlyer/damaged.png";
static const char* SF_EXPLODE  = "Sprites/SlugFlyer/explode.png";

static const char* SM_IDLE     = "Sprites/SlugMariner/idle.png";
static const char* SM_MOVE     = "Sprites/SlugMariner/move.png";
static const char* SM_FIRE_H   = "Sprites/SlugMariner/fire_horiz.png";
static const char* SM_FIRE_V   = "Sprites/SlugMariner/fire_vert.png";
static const char* SM_FIRE_R   = "Sprites/SlugMariner/fire_reverse.png";
static const char* SM_DAMAGED  = "Sprites/SlugMariner/damaged.png";
static const char* SM_EXPLODE  = "Sprites/SlugMariner/explode.png";

static const char* IN_IDLE          = "Sprites/IronNokana/idle.png";
static const char* IN_HATCH_OPEN    = "Sprites/IronNokana/hatch_open.png";
static const char* IN_TURRET_L      = "Sprites/IronNokana/turret_left.png";
static const char* IN_TURRET_R      = "Sprites/IronNokana/turret_right.png";
static const char* IN_MOVE_FWD      = "Sprites/IronNokana/move_fwd.png";
static const char* IN_MOVE_REV      = "Sprites/IronNokana/move_rev.png";
static const char* IN_FIRE          = "Sprites/IronNokana/fire.png";
static const char* IN_FIRE_UP       = "Sprites/IronNokana/fire_up.png";
static const char* IN_FLAME_PRIME   = "Sprites/IronNokana/flame_prime.png";
static const char* IN_FLAME         = "Sprites/IronNokana/flame.png";
static const char* IN_BOMB_PREP     = "Sprites/IronNokana/bomb_prep.png";
static const char* IN_BOMB          = "Sprites/IronNokana/bomb.png";
static const char* IN_DAMAGED       = "Sprites/IronNokana/damaged.png";
static const char* IN_HATCH_SHAKE   = "Sprites/IronNokana/hatch_shake.png";
static const char* IN_RETREAT       = "Sprites/IronNokana/retreat.png";
static const char* IN_PILOT_EJECT   = "Sprites/IronNokana/pilot_eject.png";
static const char* IN_EXPLODE_1     = "Sprites/IronNokana/explode_1.png";
static const char* IN_EXPLODE_2     = "Sprites/IronNokana/explode_2.png";

static const char* HB_ROTOR         = "Sprites/HairBuster/rotor.png";
static const char* HB_IDLE          = "Sprites/HairBuster/idle.png";
static const char* HB_DRIFT_L       = "Sprites/HairBuster/drift_left.png";
static const char* HB_DRIFT_R       = "Sprites/HairBuster/drift_right.png";
static const char* HB_ARM_PODS      = "Sprites/HairBuster/arm_pods.png";
static const char* HB_ROCKET_L      = "Sprites/HairBuster/rocket_left.png";
static const char* HB_ROCKET_R      = "Sprites/HairBuster/rocket_right.png";
static const char* HB_ROCKET_BOTH   = "Sprites/HairBuster/rocket_both.png";
static const char* HB_BOMB          = "Sprites/HairBuster/bomb.png";
static const char* HB_DIVE          = "Sprites/HairBuster/dive.png";
static const char* HB_PULLUP        = "Sprites/HairBuster/pullup.png";
static const char* HB_DAMAGED       = "Sprites/HairBuster/damaged.png";
static const char* HB_HEAVY_DMG     = "Sprites/HairBuster/heavy_damage.png";
static const char* HB_RETREAT       = "Sprites/HairBuster/retreat.png";
static const char* HB_PILOT_BAIL    = "Sprites/HairBuster/pilot_bail.png";
static const char* HB_EXPLODE_1     = "Sprites/HairBuster/explode_1.png";
static const char* HB_EXPLODE_2     = "Sprites/HairBuster/explode_2.png";

static const char* SS_IDLE          = "Sprites/SeaSatan/idle.png";
static const char* SS_MOVE_FWD      = "Sprites/SeaSatan/move_fwd.png";
static const char* SS_MOVE_REV      = "Sprites/SeaSatan/move_rev.png";
static const char* SS_HMG_L         = "Sprites/SeaSatan/hmg_left.png";
static const char* SS_HMG_R         = "Sprites/SeaSatan/hmg_right.png";
static const char* SS_HMG_BOTH      = "Sprites/SeaSatan/hmg_both.png";
static const char* SS_ROCKET_OPEN   = "Sprites/SeaSatan/rocket_open.png";
static const char* SS_ROCKET        = "Sprites/SeaSatan/rocket.png";
static const char* SS_ROCKET_UP     = "Sprites/SeaSatan/rocket_up.png";
static const char* SS_SURFACE       = "Sprites/SeaSatan/surface.png";
static const char* SS_DIVE          = "Sprites/SeaSatan/dive.png";
static const char* SS_DAMAGED       = "Sprites/SeaSatan/damaged.png";
static const char* SS_RETREAT       = "Sprites/SeaSatan/retreat.png";
static const char* SS_EXPLODE_1     = "Sprites/SeaSatan/explode_1.png";
static const char* SS_EXPLODE_2     = "Sprites/SeaSatan/explode_2.png";

static const char* UB_MORPH_IN   = "Sprites/UltimateBoss/morph_in.png";
static const char* UB_GROUND     = "Sprites/UltimateBoss/ground.png";
static const char* UB_AERIAL    = "Sprites/UltimateBoss/aerial.png";
static const char* UB_AQUATIC   = "Sprites/UltimateBoss/aquatic.png";
static const char* UB_MORPH      = "Sprites/UltimateBoss/morph.png";
static const char* UB_DAMAGED    = "Sprites/UltimateBoss/damaged.png";
static const char* UB_EXPLODE    = "Sprites/UltimateBoss/explode.png";

static const char* IT_TURKEY    = "Sprites/Items/turkey.png";
static const char* IT_FRUIT     = "Sprites/Items/fruit.png";
static const char* IT_CRATE     = "Sprites/Items/crate.png";
static const char* IT_POW_IDLE  = "Sprites/Items/pow_idle.png";
static const char* IT_POW_CHEER = "Sprites/Items/pow_cheer.png";

static const char* FC_IDLE      = "Sprites/Fusion/idle.png";
static const char* FC_FOLLOW    = "Sprites/Fusion/follow.png";
static const char* FC_FIRE      = "Sprites/Fusion/fire.png";
static const char* FC_DESPAWN   = "Sprites/Fusion/despawn.png";
void setupMarcoAnims(SpriteAnimator& a, TextureManager& tm)
{

    setupMarcoNormal(a, tm);
}

void setupMarcoMummyTransition(SpriteAnimator& a, TextureManager& tm)
{

    a.setScale(3.f, 3.f);
    a.addClipAuto("transform_in", MM_TRANSFORM, 2, 0.18f, false, tm);
    a.play("transform_in");
}

void setupMarcoMummyCurse(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(2.f, 2.f);
    a.addClipAuto("burst", MM_CURSE_BURST, 8, 0.06f, false, tm);
    a.addClipAuto("fade",  MM_CURSE_FADE,  7, 0.08f, false, tm);
    a.play("burst");
}

void setupTarmaAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);

    a.addClipAuto("stand",          T_STAND,          4, 0.20f, true,  tm);
    a.addClipAuto("idle",           T_IDLE,           4, 0.20f, true,  tm);
    a.addClipAuto("walk",           T_WALK,           6, 0.08f, true,  tm);
    a.addClipAuto("run",            T_RUN,            8, 0.08f, true,  tm);
    a.addClipAuto("jump_up",        T_JUMP_UP,        4, 0.10f, false, tm);
    a.addClipAuto("jump_down",      T_JUMP_DN,        4, 0.10f, false, tm);
    a.addClipAuto("land",           T_LAND,           2, 0.08f, false, tm);
    a.addClipAuto("crouch",         T_CROUCH,         4, 0.10f, false, tm);

    a.addClipAuto("shoot",          T_SHOOT,          3, 0.06f, false, tm);
    a.addClipAuto("pistol_shoot",   T_PISTOL_SHOOT,   3, 0.06f, false, tm);
    a.addClipAuto("pistol_shoot_up",T_PISTOL_SHOOT_UP,3, 0.06f, false, tm);
    a.addClipAuto("hmg_shoot",      T_HMG_SHOOT,      4, 0.05f, true,  tm);
    a.addClipAuto("hmg_shoot_up",   T_HMG_SHOOT_UP,   4, 0.05f, true,  tm);
    a.addClipAuto("rocket_shoot",   T_ROCKET_SHOOT,   2, 0.10f, false, tm);
    a.addClipAuto("rocket_shoot_up",T_ROCKET_SHOOT_UP,2, 0.10f, false, tm);
    a.addClipAuto("flame_shoot",    T_FLAME_SHOOT,    4, 0.07f, true,  tm);
    a.addClipAuto("flame_shoot_up", T_FLAME_SHOOT_UP, 4, 0.07f, true,  tm);
    a.addClipAuto("laser_shoot",    T_LASER_SHOOT,    2, 0.05f, false, tm);

    a.addClipAuto("melee",          T_MELEE,          4, 0.07f, false, tm);
    a.addClipAuto("grenade",        T_GRENADE,        5, 0.08f, false, tm);
    a.addClipAuto("hurt",           T_HURT,           4, 0.06f, false, tm);
    a.addClipAuto("die",            T_DIE,            6, 0.10f, false, tm);
    a.addClipAuto("mummy",          T_MUMMY,          4, 0.20f, true,  tm);
    a.addClipAuto("undead",         T_UNDEAD,         4, 0.22f, true,  tm);

    a.play("idle");
}

void setupTarmaMummy(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("stand", MM_STAND, 1,  0.20f, true,  tm);
    a.addClipAuto("walk",  MM_WALK,  12, 0.10f, true,  tm);
    a.play("stand");
}

void setupTarmaUndead(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("stand", MU_STAND, 4, 0.20f, true,  tm);
    a.addClipAuto("walk",  MU_WALK,  8, 0.16f, true,  tm);
    a.play("walk");
}

void setupTarmaFat(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("stand", MF_STAND, 3, 0.22f, true,  tm);
    a.addClipAuto("walk",  MF_WALK,  6, 0.12f, true,  tm);
    a.play("stand");
}

void setupEriAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("stand",          E_PISTOL_IDLE,             4, 0.18f, true,  tm);
    a.addClipAuto("idle",           E_PISTOL_IDLE,             4, 0.18f, true,  tm);
    a.addClipAuto("walk",           E_WALK,                   12, 0.07f, true,  tm);
    a.addClipAuto("run",            E_RUN,                     5, 0.07f, true,  tm);
    a.addClipAuto("jump_up",        E_JUMP_UP,                 6, 0.08f, false, tm);
    a.addClipAuto("jump_down",      E_JUMP_UP,                 6, 0.08f, false, tm);
    a.addClipAuto("rolling",        E_ROLLING,                12, 0.05f, false, tm);
    a.addClipAuto("roll",           E_ROLLING,                12, 0.05f, false, tm);
    a.addClipAuto("crouch",         E_PISTOL_CROUCH,           4, 0.10f, false, tm);
    a.addClipAuto("hurt",           E_FLAME_HURT,              6, 0.07f, false, tm);


    a.addClipAuto("shoot",                   E_PISTOL_SHOOT,           10, 0.05f, false, tm);
    a.addClipAuto("pistol_idle",             E_PISTOL_IDLE,             4, 0.18f, true,  tm);
    a.addClipAuto("pistol_prep",             E_PISTOL_PREP,             6, 0.06f, false, tm);
    a.addClipAuto("pistol_prep_up",          E_PISTOL_PREP_UP,          8, 0.06f, false, tm);
    a.addClipAuto("pistol_prep_down",        E_PISTOL_PREP_DOWN,        3, 0.07f, false, tm);
    a.addClipAuto("pistol_prep_laidback",    E_PISTOL_PREP_LAIDBACK,    5, 0.07f, false, tm);
    a.addClipAuto("pistol_prep_crouch",      E_PISTOL_PREP_CROUCH,      8, 0.06f, false, tm);
    a.addClipAuto("pistol_shoot",            E_PISTOL_SHOOT,           10, 0.05f, false, tm);
    a.addClipAuto("pistol_shoot_up",         E_PISTOL_SHOOT_UP,        10, 0.05f, false, tm);
    a.addClipAuto("pistol_shoot_down",       E_PISTOL_SHOOT_DOWN,       6, 0.06f, false, tm);
    a.addClipAuto("pistol_shoot_laidback",   E_PISTOL_SHOOT_LAIDBACK,   5, 0.06f, false, tm);
    a.addClipAuto("pistol_crouch",           E_PISTOL_CROUCH,           4, 0.10f, false, tm);
    a.addClipAuto("pistol_crouch_prep",      E_PISTOL_CROUCH_PREP,      9, 0.06f, false, tm);
    a.addClipAuto("pistol_loading",          E_PISTOL_LOADING,          6, 0.07f, false, tm);
    a.addClipAuto("pistol_loading_crouch",   E_PISTOL_LOADING_CROUCH,   8, 0.07f, false, tm);
    a.addClipAuto("pistol_kick",             E_PISTOL_KICK,             6, 0.06f, false, tm);
    a.addClipAuto("pistol_mellee",           E_PISTOL_MELLEE,           6, 0.06f, false, tm);
    a.addClipAuto("pistol_mellee_crouch",    E_PISTOL_MELLEE_CROUCH,    4, 0.07f, false, tm);
    a.addClipAuto("pistol_jump_glow",        E_PISTOL_JUMP_GLOW,        6, 0.06f, false, tm);
    a.addClipAuto("pistol_toppling",         E_PISTOL_TOPPLING,        14, 0.07f, false, tm);


    a.addClipAuto("flame_idle",              E_FLAME_IDLE,              4, 0.18f, true,  tm);
    a.addClipAuto("flame_prep_up",           E_FLAME_PREP_UP,           5, 0.07f, false, tm);
    a.addClipAuto("flame_prep_down",         E_FLAME_PREP_DOWN,         3, 0.07f, false, tm);
    a.addClipAuto("flame_prep_laidback",     E_FLAME_PREP_LAIDBACK,     5, 0.07f, false, tm);
    a.addClipAuto("flame_prep_crouch",       E_FLAME_PREP_CROUCH,       4, 0.07f, false, tm);
    a.addClipAuto("flame_prep_up_crouch",    E_FLAME_PREP_UP_CROUCH,    4, 0.07f, false, tm);
    a.addClipAuto("flame_pre_crouch",        E_FLAME_PRE_CROUCH,        3, 0.08f, false, tm);
    a.addClipAuto("flame_shoot",             E_FLAME_SHOOT,             7, 0.06f, true,  tm);
    a.addClipAuto("flame_shoot_up",          E_FLAME_SHOOT_UP,          4, 0.06f, true,  tm);
    a.addClipAuto("flame_shoot_down",        E_FLAME_SHOOT_DOWN,        4, 0.06f, true,  tm);
    a.addClipAuto("flame_shoot_laidback",    E_FLAME_SHOOT_LAIDBACK,    4, 0.06f, true,  tm);
    a.addClipAuto("flame_shoot_crouch",      E_FLAME_SHOOT_CROUCH,      4, 0.06f, true,  tm);
    a.addClipAuto("flame_shoot_aim_up",      E_FLAME_SHOOT_AIM_UP,      2, 0.08f, true,  tm);
    a.addClipAuto("flame_shoot_aim_down",    E_FLAME_SHOOT_AIM_DOWN,    2, 0.08f, true,  tm);
    a.addClipAuto("flame_shoot_down_to_up",  E_FLAME_SHOOT_DOWN_TO_UP,  2, 0.08f, false, tm);
    a.addClipAuto("flame_crouch",            E_FLAME_CROUCH,            4, 0.10f, false, tm);
    a.addClipAuto("flame_kick",              E_FLAME_KICK,              6, 0.06f, false, tm);
    a.addClipAuto("flame_mellee_swing",      E_FLAME_MELLEE_SWING,      6, 0.06f, false, tm);
    a.addClipAuto("flame_jump_glow",         E_FLAME_JUMP_GLOW,         6, 0.06f, false, tm);
    a.addClipAuto("flame_topple",            E_FLAME_TOPPLE,           14, 0.07f, false, tm);
    a.addClipAuto("flame_hurt",              E_FLAME_HURT,              6, 0.07f, false, tm);

    a.play("idle");
}

void setupEriMummy(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("transform_in", "Sprites/EriMummy/transform.png",  4, 0.12f, false, tm);
    a.addClipAuto("walk",         "Sprites/EriMummy/walk.png",       8, 0.10f, true,  tm);
    a.addClipAuto("stand",        "Sprites/EriMummy/stand.png",      1, 0.20f, true,  tm);
    a.addClipAuto("pistol_shoot", "Sprites/EriMummy/shoot.png",      3, 0.08f, false, tm);
    a.addClipAuto("throw",        "Sprites/EriMummy/throw.png",      4, 0.08f, false, tm);
    a.addClipAuto("curse",        "Sprites/EriMummy/curse.png",      5, 0.10f, false, tm);
    a.play("transform_in");
}

void setupEriUndead(SpriteAnimator& a, TextureManager& tm)
{

    a.setScale(3.f, 3.f);
    a.addClipAuto("stand", MU_STAND, 4, 0.20f, true,  tm);
    a.addClipAuto("walk",  MU_WALK,  8, 0.16f, true,  tm);
    a.play("walk");
}

void setupEriFat(SpriteAnimator& a, TextureManager& tm)
{

    a.setScale(3.f, 3.f);
    a.addClipAuto("stand", MF_STAND, 3, 0.22f, true,  tm);
    a.addClipAuto("walk",  MF_WALK,  6, 0.12f, true,  tm);
    a.play("stand");
}

void setupFioAnims(SpriteAnimator& a, TextureManager& tm)
{

    a.setScale(3.f, 3.f);

    a.addClipAuto("stand",          F_STAND,          4, 0.15f, true,  tm);
    a.addClipAuto("idle",           F_IDLE,           4, 0.15f, true,  tm);
    a.addClipAuto("walk",           F_WALK,           6, 0.08f, true,  tm);
    a.addClipAuto("run",            F_RUN,            7, 0.08f, true,  tm);
    a.addClipAuto("jump_up",        F_JUMP_UP,        4, 0.10f, false, tm);
    a.addClipAuto("jump_down",      F_JUMP_DN,        4, 0.10f, false, tm);
    a.addClipAuto("land",           F_LAND,           2, 0.08f, false, tm);
    a.addClipAuto("crouch",         F_CROUCH,         4, 0.10f, false, tm);

    a.addClipAuto("shoot",          F_SHOOT,          3, 0.06f, false, tm);
    a.addClipAuto("pistol_shoot",   F_PISTOL_SHOOT,   3, 0.06f, false, tm);
    a.addClipAuto("pistol_shoot_up",F_PISTOL_SHOOT_UP,3, 0.06f, false, tm);
    a.addClipAuto("hmg_shoot",      F_HMG_SHOOT,      4, 0.05f, true,  tm);
    a.addClipAuto("hmg_shoot_up",   F_HMG_SHOOT_UP,   4, 0.05f, true,  tm);
    a.addClipAuto("rocket_shoot",   F_ROCKET_SHOOT,   2, 0.10f, false, tm);
    a.addClipAuto("flame_shoot",    F_FLAME_SHOOT,    4, 0.07f, true,  tm);
    a.addClipAuto("laser_shoot",    F_LASER_SHOOT,    2, 0.05f, false, tm);

    a.addClipAuto("melee",          F_MELEE,          4, 0.07f, false, tm);
    a.addClipAuto("grenade",        F_GRENADE,        5, 0.08f, false, tm);
    a.addClipAuto("hurt",           F_HURT,           4, 0.06f, false, tm);
    a.addClipAuto("die",            F_DIE,            6, 0.10f, false, tm);
    a.addClipAuto("mummy",          F_MUMMY,          4, 0.20f, true,  tm);
    a.addClipAuto("undead",         F_UNDEAD,         4, 0.22f, true,  tm);

    a.play("idle");
}

void setupFioMummy(SpriteAnimator& a, TextureManager& tm)
{

    a.setScale(3.f, 3.f);
    a.addClipAuto("stand", MM_STAND, 1,  0.20f, true,  tm);
    a.addClipAuto("walk",  MM_WALK,  12, 0.10f, true,  tm);
    a.play("stand");
}

void setupFioUndead(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("stand", MU_STAND, 4, 0.20f, true,  tm);
    a.addClipAuto("walk",  MU_WALK,  8, 0.16f, true,  tm);
    a.play("walk");
}

void setupFioFat(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("stand", MF_STAND, 3, 0.22f, true,  tm);
    a.addClipAuto("walk",  MF_WALK,  6, 0.12f, true,  tm);
    a.play("stand");
}
void setupRebelAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("idle",            R_IDLE,           4, 0.18f, true,  tm);
    a.addClipAuto("walk",            R_WALK,           2, 0.18f, true,  tm);
    a.addClipAuto("run",             R_RUN,           12, 0.06f, true,  tm);
    a.addClipAuto("hurt",            R_HURT,           8, 0.06f, false, tm);
    a.addClipAuto("win",             R_WIN,            6, 0.10f, true,  tm);
    a.addClipAuto("rebelShooting1",  R_SHOOT,          7, 0.05f, false, tm);
    a.addClipAuto("shoot",           R_SHOOT,          7, 0.05f, false, tm);
    a.addClipAuto("shoot360",        R_SHOOT360,      13, 0.05f, false, tm);
    a.addClipAuto("full_auto",       R_SHOOT360,      13, 0.05f, false, tm);
    a.addClipAuto("shield_weapon",   R_SHIELD_WEAPON,  4, 0.10f, true,  tm);


    a.addClipAuto("die",             R_HURT,           8, 0.06f, false, tm);

    a.play("idle");
}

void setupShieldedAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("walk",        S_WALK,   6, 0.09f, true,  tm);
    a.addClipAuto("block",       S_BLOCK,  5, 0.10f, false, tm);
    a.addClipAuto("shoot",       S_SHOOT, 10, 0.05f, false, tm);
    a.addClipAuto("knife",       S_KNIFE,  9, 0.06f, false, tm);


    a.addClipAuto("idle",        S_BLOCK,  5, 0.18f, true,  tm);
    a.addClipAuto("shield_hit",  S_BLOCK,  5, 0.10f, false, tm);
    a.addClipAuto("die",         S_BLOCK,  5, 0.10f, false, tm);

    a.play("idle");
}

void setupBazookaAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("idle", B_IDLE,  6, 0.18f, true,  tm);
    a.addClipAuto("walk", B_WALK,  5, 0.10f, true,  tm);
    a.addClipAuto("run",  B_RUN,  11, 0.06f, true,  tm);
    a.addClipAuto("hurt", B_HURT,  7, 0.06f, false, tm);

    a.play("idle");
}
void setupGrenadierAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("idle",       G_IDLE,        1, 0.15f, true,  tm);
    a.addClipAuto("walk",       G_WALK,        8, 0.10f, true,  tm);
    a.addClipAuto("throw_prep", G_THROW_PREP,  4, 0.08f, false, tm);
    a.addClipAuto("throw",      G_THROW,       4, 0.08f, false, tm);
    a.addClipAuto("fire",       G_THROW,       4, 0.08f, false, tm);
    a.addClipAuto("die",        G_DIE,         8, 0.10f, false, tm);

    a.play("idle");
}

void setupParatrooperAnims(SpriteAnimator& a, TextureManager& tm)
{

    a.setScale(3.f, 3.f);

    a.addClipAuto("chute_open", P_CHUTE_OPEN, 2, 0.10f, false, tm);
    a.addClipAuto("chute_fall", P_CHUTE_FALL, 2, 0.12f, true,  tm);
    a.addClipAuto("walk",       P_CHUTE_FALL, 2, 0.12f, true,  tm);
    a.addClipAuto("fall",       P_CHUTE_FALL, 2, 0.12f, true,  tm);
    a.addClipAuto("land",       P_LAND,       2, 0.10f, false, tm);
    a.addClipAuto("die",        P_DIE,        2, 0.10f, false, tm);

    a.play("chute_open");
}

void setupMummyAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("idle",      "Sprites/Mummy/idle.png",              5, 0.20f, true,  tm);
    a.addClipAuto("walk",      "Sprites/Mummy/walk.png",              6, 0.15f, true,  tm);
    a.addClipAuto("resurrect", "Sprites/Mummy/resurrect.png",         8, 0.12f, false, tm);
    a.addClipAuto("hurt",      "Sprites/Mummy/walk_right_left.png",  12, 0.10f, false, tm);


    a.addClipAuto("hang_idle", "Sprites/Mummy/hanging.png",            9, 0.15f, true,  tm);
    a.addClipAuto("hang_drop", "Sprites/Mummy/falling_in_hanging.png",21, 0.10f, false, tm);


    a.addClipAuto("burn_walk", "Sprites/Mummy/walk_burning.png",      18, 0.10f, true,  tm);
    a.addClipAuto("crumble",   "Sprites/Mummy/falling_burning.png",   18, 0.10f, false, tm);
    a.addClipAuto("hang_burn", "Sprites/Mummy/hang_burning.png",      18, 0.10f, true,  tm);
    a.addClipAuto("explode",   "Sprites/Mummy/explode.png",           18, 0.10f, true,  tm);
    a.addClipAuto("die",       "Sprites/Mummy/die.png",                5, 0.10f, false, tm);

    a.play("walk");
}

void setupZombieAnims(SpriteAnimator& a, TextureManager& tm)
{


    a.setScale(3.f, 3.f);
    a.addClipAuto("stand",          Z_STAND,     7, 0.20f, true,  tm);
    a.addClipAuto("idle",           Z_STAND,     7, 0.20f, true,  tm);
    a.addClipAuto("walk",           Z_WALK,     14, 0.13f, true,  tm);
    a.addClipAuto("emerge",         Z_EMERGE,   10, 0.11f, false, tm);
    a.addClipAuto("collapse",       Z_COLLAPSE, 12, 0.10f, false, tm);
    a.addClipAuto("die",            Z_COLLAPSE, 12, 0.10f, false, tm);
    a.addClipAuto("burn_phase_one", Z_BURN_ONE,  9, 0.10f, false, tm);
    a.addClipAuto("burn_phase_two", Z_BURN_TWO,  7, 0.10f, false, tm);
    a.addClipAuto("burn",           Z_BURN_ONE,  9, 0.10f, false, tm);


    a.addClipAuto("shuffle",        Z_WALK,     14, 0.15f, true,  tm);
    a.addClipAuto("reach",          Z_WALK,     14, 0.13f, true,  tm);
    a.addClipAuto("hurt",           Z_BURN_ONE,  9, 0.10f, false, tm);

    a.play("walk");
}

void setupMartianAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("idle",         MA_IDLE,             16, 0.08f, true,  tm);
    a.addClipAuto("pod_idle",     MA_IDLE,             16, 0.08f, true,  tm);
    a.addClipAuto("brain_idle",   MA_IDLE,             16, 0.08f, true,  tm);
    a.addClipAuto("walk",         MA_WALK,             18, 0.07f, true,  tm);
    a.addClipAuto("brain_walk",   MA_WALK,             18, 0.07f, true,  tm);
    a.addClipAuto("loop",         MA_WALK,             18, 0.07f, true,  tm);
    a.addClipAuto("turn",         MA_TURN,              8, 0.08f, false, tm);
    a.addClipAuto("jumping",      MA_JUMPING,          14, 0.07f, false, tm);
    a.addClipAuto("pod_jump",     MA_JUMPING,          14, 0.07f, false, tm);
    a.addClipAuto("falling",      MA_FALLING,           9, 0.07f, true,  tm);
    a.addClipAuto("pod_fall",     MA_FALLING,           9, 0.07f, true,  tm);


    a.addClipAuto("shoot_prep",   MA_SHOOT_PREP,       11, 0.06f, false, tm);
    a.addClipAuto("pod_open",     MA_SHOOT_PREP,       11, 0.06f, false, tm);
    a.addClipAuto("shoot",        MA_SHOOT,             6, 0.06f, false, tm);
    a.addClipAuto("pod_fire",     MA_SHOOT,             6, 0.06f, false, tm);
    a.addClipAuto("brain_shoot",  MA_SHOOT,             6, 0.06f, false, tm);
    a.addClipAuto("trajectory",   MA_TRAJECTORY,       16, 0.06f, false, tm);


    a.addClipAuto("teleport_one", MA_TELEPORT_ONE,     12, 0.06f, false, tm);
    a.addClipAuto("teleport_two", MA_TELEPORT_TWO,      2, 0.10f, false, tm);

    a.addClipAuto("death_one",    MA_DEATH_ONE,        16, 0.07f, false, tm);
    a.addClipAuto("death_two",    MA_DEATH_TWO,        11, 0.07f, false, tm);
    a.addClipAuto("death_three",  MA_DEATH_THREE,      16, 0.07f, false, tm);
    a.addClipAuto("explode",      MA_DEATH_ONE,        16, 0.07f, false, tm);
    a.addClipAuto("die",          MA_DEATH_THREE,      16, 0.07f, false, tm);


    a.addClipAuto("burn_one",     MA_BURN_DEATH_ONE,   15, 0.07f, false, tm);
    a.addClipAuto("burn_two",     MA_BURN_DEATH_TWO,   14, 0.07f, false, tm);
    a.addClipAuto("burn_three",   MA_BURN_DEATH_THREE, 13, 0.07f, false, tm);
    a.addClipAuto("brain_burn",   MA_BURN_DEATH_ONE,   15, 0.07f, true,  tm);

    a.play("idle");
}
void setupFlyingTaraAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("idle",      TA_IDLE,      1, 0.30f, true,  tm);
    a.addClipAuto("fly_down",  TA_FLY_DN,    2, 0.18f, true,  tm);
    a.addClipAuto("fly_up",    TA_FLY_UP,    2, 0.18f, true,  tm);


    a.addClipAuto("drop_bomb", TA_DROP_BOMB, 3, 0.10f, false, tm);
    a.addClipAuto("propeller", TA_PROP,      3, 0.04f, true,  tm);
    a.addClipAuto("explode",   TA_EXPLODE,   6, 0.08f, false, tm);
    a.addClipAuto("pilot",     TA_PILOT,     4, 0.10f, true,  tm);

    a.play("idle");
}
void setupBradleyAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("idle",          BR_IDLE,             2, 0.22f, true,  tm);
    a.addClipAuto("move",          BR_WALKING,          6, 0.08f, true,  tm);
    a.addClipAuto("walking",       BR_WALKING,          6, 0.08f, true,  tm);
    a.addClipAuto("launcher_idle", BR_LAUNCHER_IDLE,    2, 0.22f, true,  tm);
    a.addClipAuto("launcher_walk", BR_LAUNCHER_WALKING, 6, 0.08f, true,  tm);
    a.addClipAuto("crumble",       BR_WRECKED,          4, 0.10f, false, tm);
    a.addClipAuto("wrecked",       BR_WRECKED,          4, 0.10f, false, tm);
    a.addClipAuto("explode",       BR_EXPLODE,          6, 0.08f, false, tm);

    a.play("idle");
}
void setupSubAnims(SpriteAnimator& a, TextureManager& tm)
{


    a.setScale(3.f, 3.f);

    a.addClipAuto("move",          SU_MOVE,           7, 0.08f, true,  tm);
    a.addClipAuto("turning",       SU_TURNING,       10, 0.07f, false, tm);
    a.addClipAuto("get_hit",       SU_GET_HIT,        6, 0.07f, false, tm);
    a.addClipAuto("falling_apart", SU_FALLING_APART,  6, 0.08f, false, tm);
    a.addClipAuto("debris",        SU_DEBRIS,        15, 0.06f, true,  tm);
    a.addClipAuto("dive",          SU_TURNING,       10, 0.07f, false, tm);
    a.addClipAuto("damaged",       SU_GET_HIT,        6, 0.07f, true,  tm);
    a.addClipAuto("explode",       SU_FALLING_APART,  6, 0.08f, false, tm);

    a.play("move");
}

void setupMetalSlugAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("idle",          "Sprites/MetalTank/idle.png",     1, 0.20f, true,  tm);
    a.addClipAuto("explode",       "Sprites/MetalTank/explode.png",  2, 0.15f, false, tm);
    a.addClipAuto("shoot_up",      "Sprites/MetalTank/shoot_up.png", 3, 0.10f, true,  tm);
    a.addClipAuto("driving_pilot", "Sprites/MetalTank/move.png",     4, 0.10f, true,  tm);
    a.addClipAuto("jump",          "Sprites/MetalTank/jump.png",     3, 0.15f, false, tm);
    a.play("idle");
}
void setupSlugFlyerAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);
    a.addClipAuto("idle",     SF_IDLE,    5, 0.15f, true,  tm);
    a.addClipAuto("strafe",   SF_STRAFE,  6, 0.08f, true,  tm);
    a.addClipAuto("fly_down", SF_FLY_DN,  6, 0.10f, true,  tm);
    a.addClipAuto("fly_up",   SF_FLY_UP,  6, 0.10f, true,  tm);
    a.addClipAuto("loop",     SF_LOOP,    8, 0.08f, true,  tm);
    a.addClipAuto("fire",     SF_FIRE,    3, 0.06f, false, tm);
    a.addClipAuto("missile",  SF_MISSILE, 4, 0.08f, false, tm);
    a.addClipAuto("damaged",  SF_DAMAGED, 4, 0.10f, true,  tm);
    a.addClipAuto("explode",  SF_EXPLODE, 7, 0.08f, false, tm);

    a.play("idle");
}

void setupSlugMarinerAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);

    a.addClipAuto("idle",      "Sprites/SlugMariner/idle.png",       3, 0.20f, true,  tm);
    a.addClipAuto("move",      "Sprites/SlugMariner/fly_down.png",   4, 0.10f, true,  tm);
    a.addClipAuto("submerged", "Sprites/SlugMariner/fly_down.png",   4, 0.10f, true,  tm);
    a.addClipAuto("dive",      "Sprites/SlugMariner/in_and_out.png", 4, 0.10f, false, tm);
    a.addClipAuto("surface",   "Sprites/SlugMariner/in_and_out.png", 4, 0.10f, false, tm);
    a.play("idle");
}

void setupAmphibiousSlugAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);


    a.addClipAuto("slug_idle",     MS_IDLE,    2, 0.20f, true,  tm);
    a.addClipAuto("slug_move",     MS_MOVE,    6, 0.08f, true,  tm);
    a.addClipAuto("slug_fire",     MS_FIRE,    3, 0.05f, false, tm);
    a.addClipAuto("slug_explode",  MS_EXPLODE, 6, 0.08f, false, tm);


    a.addClipAuto("flyer_idle",    SF_IDLE,    5, 0.15f, true,  tm);
    a.addClipAuto("flyer_fly_up",  SF_FLY_UP,  6, 0.10f, true,  tm);
    a.addClipAuto("flyer_fly_dn",  SF_FLY_DN,  6, 0.10f, true,  tm);
    a.addClipAuto("flyer_fire",    SF_FIRE,    3, 0.06f, false, tm);
    a.addClipAuto("flyer_missile", SF_MISSILE, 4, 0.08f, false, tm);


    a.addClipAuto("mariner_idle",  SM_IDLE,    3, 0.18f, true,  tm);
    a.addClipAuto("mariner_move",  SM_MOVE,    6, 0.10f, true,  tm);
    a.addClipAuto("mariner_fire_h",SM_FIRE_H,  3, 0.10f, false, tm);
    a.addClipAuto("mariner_fire_v",SM_FIRE_V,  3, 0.10f, false, tm);
    a.addClipAuto("mariner_fire_r",SM_FIRE_R,  3, 0.10f, false, tm);


    a.addClipAuto("idle",          MS_IDLE,    2, 0.20f, true,  tm);
    a.addClipAuto("move",          MS_MOVE,    6, 0.08f, true,  tm);
    a.addClipAuto("explode",       MS_EXPLODE, 6, 0.08f, false, tm);

    a.play("idle");
}

void setupIronNokanaAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(1.5f, 1.5f);
    a.addClipAuto("idle",       "Sprites/IronNokana/idle.png",    3, 0.22f, true,  tm);
    a.addClipAuto("hatch_open", "Sprites/IronNokana/hatch.png",   1, 0.10f, false, tm);
    a.addClipAuto("damaged",    "Sprites/IronNokana/damaged.png", 1, 0.07f, false, tm);
    a.addClipAuto("retreat",    "Sprites/IronNokana/retreat.png", 1, 0.10f, false, tm);
    a.play("idle");
}




































void setupHairBusterRibertsAnims(SpriteAnimator& a, TextureManager& tm)
{




    a.setScale(1.5f, 1.5f);
    a.addClipAuto("idle",    "Sprites/HairBuster/idle.png",   1, 0.18f, true,  tm);
    a.addClipAuto("retreat", "Sprites/HairBuster/idle.png",   1, 0.10f, false, tm);
    a.addClipAuto("damaged", "Sprites/HairBuster/damage.png", 1, 0.07f, false, tm);
    a.play("idle");
}


































void setupSeaSatanAnims(SpriteAnimator& a, TextureManager& tm)
{





    a.setScale(1.5f, 1.5f);
    a.addClipAuto("idle",    "Sprites/SeaSatan/idle.png",   1, 0.20f, true,  tm);
    a.addClipAuto("retreat", "Sprites/SeaSatan/idle.png",   1, 0.10f, false, tm);
    a.addClipAuto("damaged", "Sprites/SeaSatan/damage.png", 1, 0.07f, false, tm);
    a.play("idle");
}









void setupUltimateBossAnims(SpriteAnimator& a, TextureManager& tm)
{


    a.setScale(3.f, 3.f);

    a.addClipAuto("morph_in",     UB_MORPH_IN, 8, 0.10f, false, tm);
    a.addClipAuto("ground",       UB_GROUND,   4, 0.18f, true,  tm);
    a.addClipAuto("aerial",       UB_AERIAL,   4, 0.18f, true,  tm);
    a.addClipAuto("aquatic",      UB_AQUATIC,  4, 0.18f, true,  tm);
    a.addClipAuto("morph",        UB_MORPH,    5, 0.10f, false, tm);
    a.addClipAuto("damaged",      UB_DAMAGED,  4, 0.07f, false, tm);
    a.addClipAuto("explode",      UB_EXPLODE,  8, 0.08f, false, tm);




    a.addClipAuto("idle",         UB_GROUND,   4, 0.18f, true,  tm);
    a.addClipAuto("fire",         IN_FIRE,     4, 0.10f, false, tm);
    a.addClipAuto("flame",        IN_FLAME,    4, 0.07f, true,  tm);
    a.addClipAuto("rocket",       HB_ROCKET_BOTH, 5, 0.08f, false, tm);
    a.addClipAuto("dive",         HB_DIVE,     5, 0.10f, false, tm);
    a.addClipAuto("hmg",          SS_HMG_L,    4, 0.05f, true,  tm);
    a.addClipAuto("aquatic_rocket",SS_ROCKET,  4, 0.10f, false, tm);

    a.play("morph_in");
}








void setupTurkeyAnims(SpriteAnimator& a, TextureManager& tm)
{

    a.setScale(2.f, 2.f);
    a.addClipAuto("idle", IT_TURKEY, 11, 0.10f, true, tm);
    a.play("idle");
}

void setupFruitAnims(SpriteAnimator& a, TextureManager& tm)
{

    a.setScale(2.f, 2.f);
    a.addClipAuto("idle", IT_FRUIT, 24, 0.06f, true, tm);
    a.play("idle");
}

void setupPOWPrisonerAnims(SpriteAnimator& a, TextureManager& tm)
{

    a.setScale(3.f, 3.f);
    a.addClipAuto("idle",  IT_POW_IDLE,  2, 0.30f, true,  tm);
    a.addClipAuto("cheer", IT_POW_CHEER, 4, 0.10f, false, tm);
    a.play("idle");
}

void setupSupplyCrateAnims(SpriteAnimator& a, TextureManager& tm)
{


    a.setScale(2.f, 2.f);
    a.addClipAuto("idle", IT_CRATE, 7, 0.20f, true,  tm);
    a.addClipAuto("open", IT_CRATE, 7, 0.07f, false, tm);
    a.play("idle");
}




























void setupFusionCompanionAnims(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);

    a.addClipAuto("walk",   "Sprites/Fusion/fusion_walk.png", 2, 0.15f, true, tm);
    a.addClipAuto("shoot",    "Sprites/Fusion/fusion_shoot.png",  1, 0.06f, true, tm);


    a.addClipAuto("jump", "Sprites/Fusion/fusion_jump.png",  1, 0.10f, true, tm);

    a.play("idle");
}








void setupTarmaNormal(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(2.8f, 3.f);


    a.addClipAuto("pistol_idle",       "Sprites/Tarma/walk.png",                3, 0.20f, true,  tm);
    a.addClipAuto("pistol_jump",       "Sprites/Tarma/walk.png",                3, 0.10f, false, tm);
    a.addClipAuto("pistol_run",        "Sprites/Tarma/walk.png",                3, 0.10f, true,  tm);


    a.addClipAuto("pistol_shoot",      "Sprites/Tarma/flame_shoot.png",         3, 0.08f, true,  tm);
    a.addClipAuto("pistol_shoot_up",   "Sprites/Tarma/pistol_shoot_up.png",     2, 0.08f, true,  tm);
    a.addClipAuto("pistol_shoot_down", "Sprites/Tarma/pistol_shoot_down.png",   2, 0.08f, true,  tm);
    a.addClipAuto("pistol_prep_up",    "Sprites/Tarma/pistol_aim_up.png",       2, 0.10f, false, tm);
    a.addClipAuto("pistol_prep_down",  "Sprites/Tarma/pistol_aim_down.png",     2, 0.10f, false, tm);


    a.addClipAuto("melee_prep",        "Sprites/Tarma/pistol_melee.png",        2, 0.10f, false, tm);
    a.addClipAuto("melee_swing",       "Sprites/Tarma/pistol_melee.png",        2, 0.10f, false, tm);


    a.addClipAuto("flame_run",         "Sprites/Tarma/walk.png",                3, 0.10f, true,  tm);
    a.addClipAuto("flame_shoot",       "Sprites/Tarma/flame_shoot.png",         2, 0.10f, true,  tm);
    a.addClipAuto("flame_shoot_up",    "Sprites/Tarma/flame_shoot_up.png",      2, 0.10f, true,  tm);
    a.addClipAuto("flame_shoot_down",  "Sprites/Tarma/flame_shoot_down.png",    2, 0.10f, true,  tm);

    a.play("pistol_idle");
}

void setupEriNormal(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);

    a.addClipAuto("pistol_idle",       "Sprites/Eri/walk.png",                  2, 0.20f, true,  tm);
    a.addClipAuto("pistol_run",        "Sprites/Eri/run.png",                   5, 0.10f, true,  tm);
    a.addClipAuto("pistol_jump",       "Sprites/Eri/jump_up.png",               6, 0.08f, false, tm);


    a.addClipAuto("pistol_shoot",      "Sprites/Eri/flame_shoot.png",           5, 0.08f, false, tm);
    a.addClipAuto("pistol_shoot_up",   "Sprites/Eri/flame_shoot_up.png",        4, 0.08f, false, tm);
    a.addClipAuto("pistol_shoot_down", "Sprites/Eri/flame_shoot_down.png",      4, 0.08f, false, tm);


    a.addClipAuto("flame_run",         "Sprites/Eri/run.png",                   5, 0.08f, true,  tm);
    a.addClipAuto("flame_shoot",       "Sprites/Eri/flame_shoot.png",           5, 0.08f, true,  tm);
    a.addClipAuto("flame_shoot_up",    "Sprites/Eri/flame_shoot_up.png",        4, 0.08f, true,  tm);
    a.addClipAuto("flame_shoot_down",  "Sprites/Eri/flame_shoot_down.png",      4, 0.08f, true,  tm);
    a.addClipAuto("flame_prep_up",     "Sprites/Eri/flame_shoot_aim_up.png",    2, 0.10f, false, tm);
    a.addClipAuto("flame_prep_down",   "Sprites/Eri/flame_shoot_aim_down.png",  2, 0.10f, false, tm);

    a.play("pistol_idle");
}

void setupFioNormal(SpriteAnimator& a, TextureManager& tm)
{
    a.setScale(3.f, 3.f);

    a.addClipAuto("pistol_idle",       "Sprites/Fiolina/walk.png",              2, 0.20f, true,  tm);
    a.addClipAuto("pistol_run",        "Sprites/Fiolina/run.png",               3, 0.12f, true,  tm);
    a.addClipAuto("pistol_jump",       "Sprites/Fiolina/jump.png",              3, 0.12f, false, tm);
    a.addClipAuto("pistol_shoot",      "Sprites/Fiolina/shoot.png",             2, 0.08f, true,  tm);
    a.addClipAuto("pistol_shoot_up",   "Sprites/Fiolina/shoot_up.png",          2, 0.08f, true,  tm);
    a.addClipAuto("pistol_shoot_down", "Sprites/Fiolina/shoot_down.png",        3, 0.08f, true,  tm);
    a.addClipAuto("pistol_prep_up",    "Sprites/Fiolina/aim_up.png",            2, 0.10f, false, tm);
    a.addClipAuto("pistol_prep_down",  "Sprites/Fiolina/aim_down.png",          3, 0.10f, false, tm);

    a.play("pistol_idle");
}
















void setupMarcoTransformations(SpriteAnimator& a, TextureManager& tm)
{

    a.addClipAuto("fat_idle",            MF_STAND,                    4, 0.20f, true,  tm);
    a.addClipAuto("fat_run",             MF_WALK,                    12, 0.10f, true,  tm);
    a.addClipAuto("fat_shoot",           MF_PISTOL_SHOOT,            10, 0.06f, true,  tm);
    a.addClipAuto("fat_shoot_up",        MF_PISTOL_SHOOT_UP,          8, 0.06f, false, tm);
    a.addClipAuto("fat_shoot_down",      MF_PISTOL_SHOOT_DOWN,        4, 0.07f, false, tm);
    a.addClipAuto("fat_transform",       MF_PISTOL_TRANSFORM,        18, 0.10f, false, tm);
    a.addClipAuto("fat_revert",          MF_EXIT,                    14, 0.10f, false, tm);

    a.addClipAuto("fat_jump",            MF_WALK,                    12, 0.15f, false, tm);
    a.addClipAuto("fat_die",             MF_STAND,                    4, 0.20f, false, tm);


    a.addClipAuto("mummy_idle",          MM_STAND,                    1, 0.30f, true,  tm);
    a.addClipAuto("mummy_run",           MM_WALK,                    12, 0.10f, true,  tm);
    a.addClipAuto("mummy_shoot",         MM_PISTOL_SHOOT,             8, 0.06f, false, tm);
    a.addClipAuto("mummy_shoot_up",      MM_PISTOL_SHOOT_UP,          7, 0.06f, false, tm);
    a.addClipAuto("mummy_shoot_down",    MM_PISTOL_SHOOT_DOWN,        7, 0.06f, false, tm);
    a.addClipAuto("mummy_transform",     "Sprites/MarcoMummy/transform_in.png", 2, 0.18f, false, tm);

    a.addClipAuto("mummy_jump",          MM_WALK,                    12, 0.15f, false, tm);
    a.addClipAuto("mummy_die",           MM_STAND,                    1, 0.20f, false, tm);


    a.addClipAuto("undead_transform",    MUND_TRANSFORM,             21, 0.06f, false, tm);
    a.addClipAuto("undead_shoot",        MUND_PISTOL_SHOOT,          10, 0.05f, false, tm);
    a.addClipAuto("undead_shoot_up",     MUND_PISTOL_SHOOT_UP,        3, 0.07f, false, tm);
    a.addClipAuto("undead_die",          MUND_END_STATE,             21, 0.07f, false, tm);


    a.addClipAuto("undead_idle",         MUND_WALK,                  24, 0.20f, true,  tm);
    a.addClipAuto("undead_run",          MUND_WALK,                  24, 0.07f, true,  tm);
    a.addClipAuto("undead_jump",         MUND_PISTOL_PREP,            6, 0.10f, false, tm);
    a.addClipAuto("undead_shoot_down",   MUND_PISTOL_SHOOT,          10, 0.05f, false, tm);
}
