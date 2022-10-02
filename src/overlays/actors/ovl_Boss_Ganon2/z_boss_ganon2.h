#ifndef Z_BOSS_GANON2_H
#define Z_BOSS_GANON2_H

#include "ultra64.h"
#include "global.h"

struct BossGanon2;

typedef void (*BossGanon2ActionFunc)(struct BossGanon2*, PlayState*);

typedef enum {
    /*  0 */ GANON_LIMB_NONE,
    /*  1 */ GANON_LIMB_ROOT,
    /*  2 */ GANON_LIMB_TORSO,
    /*  3 */ GANON_LIMB_LEFT_SHOULDER,
    /*  4 */ GANON_LIMB_LEFT_UPPER_ARM,
    /*  5 */ GANON_LIMB_LEFT_FOREARM,
    /*  6 */ GANON_LIMB_LEFT_WRIST,
    /*  7 */ GANON_LIMB_LEFT_SWORD,
    /*  8 */ GANON_LIMB_LEFT_HAND,
    /*  9 */ GANON_LIMB_RIGHT_SHOULDER,
    /* 10 */ GANON_LIMB_RIGHT_UPPER_ARM,
    /* 11 */ GANON_LIMB_RIGHT_FOREARM,
    /* 12 */ GANON_LIMB_RIGHT_WRIST,
    /* 13 */ GANON_LIMB_RIGHT_SWORD,
    /* 14 */ GANON_LIMB_RIGHT_HAND,
    /* 15 */ GANON_LIMB_NECK,
    /* 16 */ GANON_LIMB_JEWEL,
    /* 17 */ GANON_LIMB_SNOUT,
    /* 18 */ GANON_LIMB_OUTER_TEETH,
    /* 19 */ GANON_LIMB_MOUTH,
    /* 20 */ GANON_LIMB_INNER_TEETH,
    /* 21 */ GANON_LIMB_JAW,
    /* 22 */ GANON_LIMB_MIDDLE_HAIR_1,
    /* 23 */ GANON_LIMB_MIDDLE_HAIR_2,
    /* 24 */ GANON_LIMB_MIDDLE_HAIR_3,
    /* 25 */ GANON_LIMB_LEFT_HAIR_1,
    /* 26 */ GANON_LIMB_LEFT_HAIR_2,
    /* 27 */ GANON_LIMB_LEFT_HAIR_3,
    /* 28 */ GANON_LIMB_RIGHT_HAIR_1,
    /* 29 */ GANON_LIMB_RIGHT_HAIR_2,
    /* 30 */ GANON_LIMB_RIGHT_HAIR_3,
    /* 31 */ GANON_LIMB_EYES,
    /* 32 */ GANON_LIMB_HEAD,
    /* 33 */ GANON_LIMB_LEFT_HORN,
    /* 34 */ GANON_LIMB_RIGHT_HORN,
    /* 35 */ GANON_LIMB_PELVIS,
    /* 36 */ GANON_LIMB_LEFT_THIGH,
    /* 37 */ GANON_LIMB_LEFT_SHIN,
    /* 38 */ GANON_LIMB_LEFT_FOOT,
    /* 39 */ GANON_LIMB_RIGHT_THIGH,
    /* 40 */ GANON_LIMB_RIGHT_SHIN,
    /* 41 */ GANON_LIMB_RIGHT_FOOT,
    /* 42 */ GANON_LIMB_TAIL1,
    /* 43 */ GANON_LIMB_TAIL2,
    /* 44 */ GANON_LIMB_TAIL3,
    /* 45 */ GANON_LIMB_TAIL4,
    /* 46 */ GANON_LIMB_TAIL5,
    /* 47 */ GANON_LIMB_MAX
} GanonLimb;

typedef struct BossGanon2 {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ BossGanon2ActionFunc actionFunc;
    /* 0x0194 */ f32 endFrame;
    /* 0x0198 */ f32 unk_198; // frame to play certain SFX?
    /* 0x019C */ s16 unk_19C; // timer for tail env color?
    /* 0x019E */ char unk_19E[0x4];
    /* 0x01A2 */ s16 unk_1A2[5]; // work timers?
    /* 0x01AC */ s16 unk_1AC; // something related to animations?
    /* 0x01B0 */ f32 unk_1B0; // tail env color?
    /* 0x01B4 */ f32 triforceAlpha;
    /* 0x01B8 */ Vec3f neckPos; // Also used for Ganondorf's hand
    /* 0x01C4 */ Vec3f tailTipPos;
    /* 0x01D0 */ Vec3f rightFootPos;
    /* 0x01D0 */ Vec3f leftFootPos;
    /* 0x01E8 */ Vec3f rightShoulderPos; // Set but never used
    /* 0x01F4 */ Vec3f leftShoulderPos; // Set but never used
    /* 0x0200 */ Vec3f swordTrailTipPos;
    /* 0x020C */ Vec3f swordTrailBasePos;
    /* 0x0218 */ Vec3f swordColliderPos;
    /* 0x0224 */ f32 swordScale;
    /* 0x0228 */ f32 hornScale;
    /* 0x022C */ char unk_22C[0x8];
    /* 0x0234 */ Vec3f bodyPartsPos[16];
    /* 0x02F4 */ s16 unk_2F4[5];
    /* 0x02FE */ s16 unk_2FE[5];
    /* 0x0308 */ char unk_308[4];
    /* 0x030C */ f32 bodyLightOrbScale;
    /* 0x0310 */ u8 eyeIndex;
    /* 0x0311 */ u8 swordSwingState;
    /* 0x0312 */ u8 unk_312;
    /* 0x0313 */ u8 unk_313; // "look_on"
    /* 0x0314 */ u8 unk_314;
    /* 0x0316 */ s16 unk_316; // "no_hit_time"
    /* 0x0318 */ s16 blinkTimer;
    /* 0x031A */ s16 neckRotX;
    /* 0x031C */ s16 neckRotY;
    /* 0x0320 */ f32 unk_320;
    /* 0x0324 */ f32 fireRingAlpha;
    /* 0x0328 */ s16 lightningAlpha;
    /* 0x032C */ f32 lightningScale;
    /* 0x0330 */ s16 lightningTimer;
    /* 0x0332 */ s16 lightningSpawnTimer;
    /* 0x0334 */ u8 unk_334;
    /* 0x0335 */ u8 bgCheckEnabled;
    /* 0x0336 */ u8 lightningState;
    /* 0x0337 */ u8 unk_337; // state for which objects to use?
    /* 0x0338 */ u8 unk_338;
    /* 0x0339 */ s8 unk_339;
    /* 0x033C */ f32 unk_33C; // light blend modifier?
    /* 0x0340 */ s16 unk_340; // random value to initialize RNG?
    /* 0x0342 */ s16 damageFlashTimer;
    /* 0x0344 */ s16 tailDamageTimer;
    /* 0x0346 */ s16 tailRotX;
    /* 0x0348 */ s16 unk_348[5];
    /* 0x0352 */ s16 unk_352[5];
    /* 0x035C */ f32 unk_35C;
    /* 0x0360 */ Vec3f unk_360;
    /* 0x036C */ f32 unk_36C;
    /* 0x0370 */ Vec3f unk_370;
    /* 0x037C */ f32 zeldaMagicAlpha;
    /* 0x0380 */ f32 zeldaMagicScaleZ;
    /* 0x0384 */ f32 zeldaLightOrbScale;
    /* 0x0388 */ f32 zeldaLightOrbRotZ;
    /* 0x038C */ f32 masterSwordLightOrbAlpha;
    /* 0x0390 */ s16 unk_390;
    /* 0x0392 */ s16 unk_392;
    /* 0x0394 */ f32 introCutsceneRotX; // used for when Ganon spins around in the air
    /* 0x0398 */ u32 cutsceneTimer;
    /* 0x039C */ s16 cutsceneState;
    /* 0x039E */ s16 subCamId;
    /* 0x03A0 */ char unk_3A0[0x4];
    /* 0x03A4 */ Vec3f subCamEye;
    /* 0x03B0 */ Vec3f subCamAt;
    /* 0x03BC */ Vec3f subCamUp;
    /* 0x03C8 */ char unk_3C8[0x48];
    /* 0x0410 */ Vec3f unk_410;
    /* 0x041C */ f32 unk_41C;
    /* 0x0420 */ f32 unk_420;
    /* 0x0424 */ ColliderJntSph collider;
    /* 0x0444 */ ColliderJntSph swordCollider;
    /* 0x0464 */ ColliderJntSphElement colliderElements[16];
    /* 0x0864 */ ColliderJntSphElement swordColliderElements[2];
} BossGanon2; // size = 0x08E4

#endif
