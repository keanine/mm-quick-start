#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

#define CFG_TITLE_SCREEN_SKIP_ENABLED (bool)recomp_get_config_u32("title_screen_skip_enabled")

PlayState* gPlay;

RECOMP_HOOK("EnMag_Update") void EnMag_Update(Actor* thisx, PlayState* play) {
    gPlay = play;
}

RECOMP_HOOK_RETURN("EnMag_Update") void EnMag_Update_Return() {
    if (CFG_TITLE_SCREEN_SKIP_ENABLED) {
        Audio_SetCutsceneFlag(false);
        gOpeningEntranceIndex++;
        if (gOpeningEntranceIndex >= 2) {
            gOpeningEntranceIndex = 0;
        }
        gSaveContext.gameMode = GAMEMODE_FILE_SELECT;
        gPlay->transitionTrigger = TRANS_TRIGGER_START;
        gPlay->transitionType = TRANS_TYPE_INSTANT;
        gPlay->nextEntrance = ENTRANCE(CUTSCENE, 0);
        gSaveContext.save.cutsceneIndex = 0;
        gSaveContext.sceneLayer = 0;
    }
}
