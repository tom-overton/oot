/*
 * File: z_obj_mure3.c
 * Overlay: ovl_Obj_Mure3
 * Description: Tower of Rupees
 */

#include "z_obj_mure3.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure3*)thisx)

void ObjMure3_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure3_Update(Actor* thisx, GlobalContext* globalCtx);
void func_80B9A9D0(ObjMure3* this, GlobalContext* globalCtx);
void func_80B9AA90(ObjMure3* this, GlobalContext* globalCtx);
void func_80B9ABA0(ObjMure3* this, GlobalContext* globalCtx);
void func_80B9AF24(Actor* thisx);
void func_80B9AF34(ObjMure3* this, GlobalContext* globalCtx);
void func_80B9AF54(ObjMure3* this);
void func_80B9AF64(ObjMure3* this, GlobalContext* globalCtx);
void func_80B9AFEC(ObjMure3* this);
void func_80B9AFFC(ObjMure3* this, GlobalContext* globalCtx);

const ActorInit Obj_Mure3_InitVars = {
    ACTOR_OBJ_MURE3,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(ObjMure3),
    (ActorFunc)ObjMure3_Init,
    (ActorFunc)ObjMure3_Destroy,
    (ActorFunc)ObjMure3_Update,
    NULL,
};

s16 D_80B9B0C0[] = { 0x0005, 0x0005, 0x0007, 0x0000 };

// sInitChain
InitChainEntry D_80B9B0C8[] = {
    ICHAIN_F32(uncullZoneForward, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

ObjMure3ActionFunc D_80B9B0D4[] = { func_80B9A9D0, func_80B9AA90, func_80B9ABA0 };

#if NON_MATCHING
void func_80B9A9D0(ObjMure3 *this, GlobalContext *globalCtx) {
    s32 i;
    Vec3f spawnPos;
    EnItem00 *collectible;
 
    Math_Vec3f_Copy(&spawnPos, &this->actor.posRot.pos);
    for (i = 0; i < 5; i++) {
        if (((this->unk_16C >> i) & 1) == 0) {
            collectible = Item_DropCollectible2(globalCtx, &spawnPos, 0x4001);
            this->unk_150[i] = collectible;
            if (collectible != 0) {
                collectible->actor.room = this->actor.room;
            }
        }
        spawnPos.y += 20.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9A9D0.s")
#endif

#if NON_MATCHING
void func_80B9AA90(ObjMure3 *this, GlobalContext *globalCtx) {
    EnItem00 *collectible;
    f32 sn;
    f32 cos;
    Vec3f spawnPos;
    f32 constant;
    s32 i;

    sn = Math_SinS(this->actor.posRot.rot.y);
    cos = Math_CosS(this->actor.posRot.rot.y);
    spawnPos.y = this->actor.posRot.pos.y;
    constant = -40.0f;
    for (i = 0; i < 5; i++) {
        if (((this->unk_16C >> i) & 1) == 0) {
            spawnPos.x = this->actor.posRot.pos.x + (sn * constant);
            spawnPos.z = this->actor.posRot.pos.z + (cos * constant);
            collectible = Item_DropCollectible2(globalCtx, &spawnPos, 0x4000);
            this->unk_150[i] = collectible;
            if (collectible != 0) {
                collectible->actor.room = this->actor.room;
            }
        }
        constant += 20.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9AA90.s")
#endif

#if NON_MATCHING
void func_80B9ABA0(ObjMure3 *this, GlobalContext *globalCtx) {
    EnItem00 *collectible;
    s32 i;
    s16 yRot;
    Vec3f spawnPos;

    spawnPos.y = this->actor.posRot.pos.y;
    yRot = this->actor.posRot.rot.y;
    for (i = 0; i < 6; i++) {
        if (((this->unk_16C >> i) & 1) == 0) {
            spawnPos.x = (Math_SinS(yRot) * 40.0f) + this->actor.posRot.pos.x;
            spawnPos.z = (Math_CosS(yRot) * 40.0f) + this->actor.posRot.pos.z;
            collectible = Item_DropCollectible2(globalCtx, &spawnPos, 0x4000);
            this->unk_150[i] = collectible;
            if (collectible != 0) {
                collectible->actor.room = this->actor.room;
            }
        }
        yRot = (s16) (yRot + 0x2AAA);
    }
    if (((this->unk_16C >> 6) & 1) == 0) {
        spawnPos.x = this->actor.posRot.pos.x;
        spawnPos.z = this->actor.posRot.pos.z;
        collectible = Item_DropCollectible2(globalCtx, &spawnPos, 0x4002);
        this->unk_150[6] = collectible;
        if (collectible != 0) {
            collectible->actor.room = this->actor.room;
        }
    }
}
# else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9ABA0.s")
#endif

#if NON_MATCHING
void func_80B9ACE4(ObjMure3 *this, GlobalContext *globalCtx) {
    EnItem00 *collectible;
    s16 size;
    s32 i;

    size = D_80B9B0C0[(this->actor.params >> 13) & 7];
    i = 0;
    for (i = 0; i < size; i++) {
        if (((this->unk_16C >> i) & 1) == 0) {
            collectible = this->unk_150[i];
            if (collectible != 0) {
                if ((Actor_HasParent(&collectible->actor, globalCtx) != 0) || (collectible->actor.update == 0)) {
                    this->unk_16C = this->unk_16C | (1 << i);
                } else {
                    Actor_Kill(&collectible->actor);
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9ACE4.s")
#endif

#if NON_MATCHING
void func_80B9ADCC(ObjMure3 *this, GlobalContext *globalCtx) {
    EnItem00 *collectible;
    s16 size;
    s32 i;

    size = D_80B9B0C0[(this->actor.params >> 13) & 7];
    for (i = 0; i < size; i++) {
        if (this->unk_150[i] != 0) {
            collectible = this->unk_150[i];
            if (((this->unk_16C >> i) & 1) == 0) {
                if (Actor_HasParent(&collectible->actor, globalCtx) != 0) {
                    Flags_SetSwitch(globalCtx, this->actor.params & 0x3F);
                }
                if (collectible->actor.update == 0) {
                    this->unk_16C = (this->unk_16C | (1 << i));
                    this->unk_150[i] = 0;
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9ADCC.s")
#endif

void ObjMure3_Init(Actor* thisx, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, thisx->params & 0x3F) != 0) {
        Actor_Kill(thisx);
        return;
    }
    Actor_ProcessInitChain(thisx, D_80B9B0C8);
    func_80B9AF24(thisx);
}

void ObjMure3_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80B9AF24(Actor* thisx) {
    ObjMure3* this = THIS;

    this->actionFunc = func_80B9AF34;
}

void func_80B9AF34(ObjMure3 *this, GlobalContext *globalCtx) {
    func_80B9AF54(this);
}

void func_80B9AF54(ObjMure3 *this) {
    this->actionFunc = func_80B9AF64;
}

void func_80B9AF64(ObjMure3 *this, GlobalContext *globalCtx) {
    if (Math3D_Dist1DSq(this->actor.projectedPos.x, this->actor.projectedPos.z) < 1322500.0f) {
        this->actor.flags = this->actor.flags | 0x10;
        D_80B9B0D4[(this->actor.params >> 13) & 7](this, globalCtx);
        func_80B9AFEC(this);
    }
}

void func_80B9AFEC(ObjMure3 *this) {
    this->actionFunc = func_80B9AFFC;
}

void func_80B9AFFC(ObjMure3 *this, GlobalContext *globalCtx) {
    func_80B9ADCC(this, globalCtx);
    if (Math3D_Dist1DSq(this->actor.projectedPos.x, this->actor.projectedPos.z) >= 2102500.0f) {
        this->actor.flags = this->actor.flags & ~0x10;
        func_80B9ACE4(this, globalCtx);
        func_80B9AF54(this);
    }
}

void ObjMure3_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjMure3* this = THIS;

    this->actionFunc(this, globalCtx);
}
