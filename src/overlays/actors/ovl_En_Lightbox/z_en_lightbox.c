/*
 * File: z_en_lightbox.c
 * Overlay: ovl_En_Lightbox
 * Description: Used to be some unused box, now it's Nejiron!
 */

#include "z_en_lightbox.h"
#include "objects/object_lightbox/object_lightbox.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4)

void Nejiron_Init(Actor* thisx, GlobalContext* globalCtx);
void Nejiron_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Nejiron_Update(Actor* thisx, GlobalContext* globalCtx);

void Nejiron_UndergroundIdle(Nejiron* this, GlobalContext* globalCtx);
void Nejiron_EmergeFromUnderground(Nejiron* this, GlobalContext* globalCtx);
void Nejiron_Idle(Nejiron* this, GlobalContext* globalCtx);
void Nejiron_DrawBody(Actor* thisx, GlobalContext* globalCtx);

typedef enum {
    /* 0x0 */ NEJIRON_ACTION_INACTIVE,   // The Nejiron is either underground or emerging from underground
    /* 0x1 */ NEJIRON_ACTION_ACTIVE,     // The Nejiron is above ground and actively chasing the player
    /* 0x2 */ NEJIRON_ACTION_RETREATING, // The Nejiron is burrowing back underground
    /* 0x3 */ NEJIRON_ACTION_EXPLODING   // The Nejiron has detonated
} NejironAction;

/**
 * These directions are relative to the Nejiron.
 */
typedef enum {
    /* 0x0 */ NEJIRON_DIRECTION_RIGHT,
    /* 0x1 */ NEJIRON_DIRECTION_LEFT
} NejironRollDirection;

const ActorInit En_Lightbox_InitVars = {
    ACTOR_EN_LIGHTBOX,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_LIGHTBOX,
    sizeof(Nejiron),
    (ActorFunc)Nejiron_Init,
    (ActorFunc)Nejiron_Destroy,
    (ActorFunc)Nejiron_Update,
    (ActorFunc)NULL,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x04, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HARD,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

typedef enum {
    /* 0x0 */ NEJIRON_DMGEFF_NONE,      // Does not interact with the Nejiron at all
    /* 0xE */ NEJIRON_DMGEFF_KILL = 14, // Kills and detonates the Nejiron
    /* 0xF */ NEJIRON_DMGEFF_RECOIL     // Deals no damage, but displays the appropriate hit mark and recoil animation
} NejironDamageEffect;

static DamageTable sDamageTable = {
    /* Deku nut      */ DMG_ENTRY(0, NEJIRON_DMGEFF_RECOIL),
    /* Deku stick    */ DMG_ENTRY(0, NEJIRON_DMGEFF_RECOIL),
    /* Slingshot     */ DMG_ENTRY(0, NEJIRON_DMGEFF_RECOIL),
    /* Explosive     */ DMG_ENTRY(1, NEJIRON_DMGEFF_KILL),
    /* Boomerang     */ DMG_ENTRY(3, NEJIRON_DMGEFF_KILL),
    /* Normal arrow  */ DMG_ENTRY(0, NEJIRON_DMGEFF_RECOIL),
    /* Hammer swing  */ DMG_ENTRY(2, NEJIRON_DMGEFF_KILL),
    /* Hookshot      */ DMG_ENTRY(3, NEJIRON_DMGEFF_KILL),
    /* Kokiri sword  */ DMG_ENTRY(1, NEJIRON_DMGEFF_KILL),
    /* Master sword  */ DMG_ENTRY(2, NEJIRON_DMGEFF_KILL),
    /* Giant's Knife */ DMG_ENTRY(4, NEJIRON_DMGEFF_KILL),
    /* Fire arrow    */ DMG_ENTRY(0, NEJIRON_DMGEFF_RECOIL),
    /* Ice arrow     */ DMG_ENTRY(0, NEJIRON_DMGEFF_RECOIL),
    /* Light arrow   */ DMG_ENTRY(1, NEJIRON_DMGEFF_KILL),
    /* Unk arrow 1   */ DMG_ENTRY(0, NEJIRON_DMGEFF_NONE),
    /* Unk arrow 2   */ DMG_ENTRY(0, NEJIRON_DMGEFF_NONE),
    /* Unk arrow 3   */ DMG_ENTRY(0, NEJIRON_DMGEFF_NONE),
    /* Fire magic    */ DMG_ENTRY(0, NEJIRON_DMGEFF_RECOIL),
    /* Ice magic     */ DMG_ENTRY(0, NEJIRON_DMGEFF_RECOIL),
    /* Light magic   */ DMG_ENTRY(1, NEJIRON_DMGEFF_KILL),
    /* Shield        */ DMG_ENTRY(0, NEJIRON_DMGEFF_NONE),
    /* Mirror Ray    */ DMG_ENTRY(0, NEJIRON_DMGEFF_NONE),
    /* Kokiri spin   */ DMG_ENTRY(1, NEJIRON_DMGEFF_KILL),
    /* Giant spin    */ DMG_ENTRY(4, NEJIRON_DMGEFF_KILL),
    /* Master spin   */ DMG_ENTRY(2, NEJIRON_DMGEFF_KILL),
    /* Kokiri jump   */ DMG_ENTRY(2, NEJIRON_DMGEFF_KILL),
    /* Giant jump    */ DMG_ENTRY(8, NEJIRON_DMGEFF_KILL),
    /* Master jump   */ DMG_ENTRY(4, NEJIRON_DMGEFF_KILL),
    /* Unknown 1     */ DMG_ENTRY(0, NEJIRON_DMGEFF_NONE),
    /* Unblockable   */ DMG_ENTRY(0, NEJIRON_DMGEFF_NONE),
    /* Hammer jump   */ DMG_ENTRY(4, NEJIRON_DMGEFF_KILL),
    /* Unknown 2     */ DMG_ENTRY(0, NEJIRON_DMGEFF_NONE),
};

void Nejiron_Init(Actor* thisx, GlobalContext* globalCtx) {
    Nejiron* this = (Nejiron*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 0.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gNejironSkel, NULL, this->jointTable, this->morphTable, 3);
    this->actor.naviEnemyId = 0xB;
    this->maxDistanceFromHome = 240.0f;
    this->maxDistanceFromHome += this->actor.world.rot.z * 40.0f;
    this->actor.world.rot.z = 0;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 3;
    this->actor.targetArrowOffset = 2000;
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);
    this->collider.elements[0].dim.modelSphere.radius = 30;
    this->collider.elements[0].dim.scale = 1.0f;
    this->collider.elements[0].dim.modelSphere.center.x = 80;
    this->collider.elements[0].dim.modelSphere.center.y = 80;
    this->collider.elements[0].dim.modelSphere.center.z = 0;
    this->actor.shape.yOffset = -3000.0f;
    this->actor.gravity = -3.0f;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    // this->actor.flags |= 0x8000000; // no clue wtf the equivalent of this is
    this->actor.flags &= ~ACTOR_FLAG_4;
    this->collider.base.acFlags |= AC_HARD;
    this->actionFunc = Nejiron_UndergroundIdle;
}

void Nejiron_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    Nejiron* this = (Nejiron*)thisx;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void Nejiron_UndergroundIdle(Nejiron* this, GlobalContext* globalCtx) {
    this->action = NEJIRON_ACTION_INACTIVE;
    if (this->actor.xzDistToPlayer < 200.0f) {
        this->actor.draw = Nejiron_DrawBody;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GANON_BREATH);
        this->actor.world.rot.z = 0;
        this->actor.world.rot.x = this->actor.world.rot.z;
        // this->actor.flags &= ~0x8000000;
        this->actor.flags |= ACTOR_FLAG_4;
        this->actionFunc = Nejiron_EmergeFromUnderground;
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void Nejiron_EmergeFromUnderground(Nejiron* this, GlobalContext* globalCtx) {
    this->actor.world.rot.y += 0x1518;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if ((globalCtx->gameplayFrames % 8) == 0) {
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale - 20.0f, 10, 8.0f,
                      500, 10, 1);
    }
    Math_ApproachF(&this->actor.shape.shadowScale, 50.0f, 0.3f, 5.0f);
    Math_ApproachF(&this->actor.shape.yOffset, 2700.0f, 100.0f, 500.0f);
    if (this->actor.shape.yOffset > 2650.0f) {
        this->action = NEJIRON_ACTION_ACTIVE;
        this->actor.shape.yOffset = 2700.0f;
        this->timer = 60;
        this->actionFunc = Nejiron_Idle;
    }
}

void Nejiron_Idle(Nejiron* this, GlobalContext* globalCtx) {

}

void Actor_SetHeight(Actor* actor, f32 height) {
    actor->focus.pos.x = actor->world.pos.x;
    actor->focus.pos.y = actor->world.pos.y + height;
    actor->focus.pos.z = actor->world.pos.z;
    actor->focus.rot.x = actor->world.rot.x;
    actor->focus.rot.y = actor->world.rot.y;
    actor->focus.rot.z = actor->world.rot.z;
}

void Nejiron_Update(Actor* thisx, GlobalContext* globalCtx) {
    Nejiron* this = (Nejiron*)thisx;

    Actor_SetHeight(&this->actor, 30.0f);
    // EnBaguo_UpdateParticles(this, globalCtx);
    // EnBaguo_CheckForDetonation(this, globalCtx);
    this->actionFunc(this, globalCtx);

    DECR(this->blinkTimer);
    DECR(this->timer);

    if (this->blinkTimer == 0) {
        this->eyeIndex++;
        if (this->eyeIndex >= 3) {
            this->eyeIndex = 0;
            this->blinkTimer = Rand_ZeroFloat(60.0f) + 20.0f;
        }
    }
}

void Nejiron_DrawBody(Actor* thisx, GlobalContext* globalCtx) {
    static void* sEyeTextures[] = { &gNejironEyeOpenTex, &gNejironEyeHalfTex, &gNejironEyeClosedTex };
    Nejiron* this = (Nejiron*)thisx;
    Gfx* gfx;
    s32 eyeIndex;
    void* virtualAddress;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_lightbox.c", 153);

    func_80093D18(globalCtx->state.gfxCtx);

    gfx = POLY_OPA_DISP;

    eyeIndex = this->eyeIndex;
    virtualAddress = SEGMENTED_TO_VIRTUAL(sEyeTextures[eyeIndex]);
    gSPSegment(&gfx[0], 0x08, virtualAddress);

    POLY_OPA_DISP = &gfx[1];

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL,
                      this);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_lightbox.c", 168);
}
