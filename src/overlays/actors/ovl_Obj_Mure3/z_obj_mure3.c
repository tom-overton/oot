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

s32 D_80B9B0C0[] = { 0x00050005, 0x00070000 };

// sInitChain
InitChainEntry D_80B9B0C8[] = {
    ICHAIN_F32(uncullZoneForward, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

ObjMure3ActionFunc D_80B9B0D4[] = { func_80B9A9D0, func_80B9AA90, func_80B9ABA0 };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9A9D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9AA90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9ABA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9ACE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Obj_Mure3/func_80B9ADCC.s")

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
    func_80B9ADCC();
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
