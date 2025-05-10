#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

#define CFG_N64_SCREEN_SKIP_ENABLED (bool)recomp_get_config_u32("n64_screen_skip_enabled")

typedef struct {
    /* 0x000 */ GameState state;
    /* 0x0A4 */ u8* staticSegment;
    /* 0x0A8 */ View view;
    /* 0x210 */ SramContext sramCtx;
    /* 0x238 */ s16 timer;
    /* 0x23A */ s16 coverAlpha;
    /* 0x23C */ s16 addAlpha;
    /* 0x23E */ s16 visibleDuration;
    /* 0x240 */ s16 ult;
    /* 0x242 */ s16 uls;
    /* 0x244 */ u8 exit;
} ConsoleLogoState; // size = 0x248

void TitleSetup_Init(GameState* thisx);

RECOMP_HOOK("ConsoleLogo_Init") void ConsoleLogo_Init(GameState* thisx) {
    if (CFG_N64_SCREEN_SKIP_ENABLED) {
        ConsoleLogoState* this = (ConsoleLogoState*)thisx;
        STOP_GAMESTATE(&this->state);
        SET_NEXT_GAMESTATE(&this->state, TitleSetup_Init, 0x210); //sizeof(TitleSetupState)
    }
}