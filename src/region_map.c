#include "global.h"
#include "main.h"
#include "text.h"
#include "menu.h"
#include "malloc.h"
#include "gpu_regs.h"
#include "palette.h"
#include "party_menu.h"
#include "trig.h"
#include "constants/maps.h"
#include "overworld.h"
#include "constants/flags.h"
#include "event_data.h"
#include "rom6.h"
#include "secret_base.h"
#include "string_util.h"
#include "international_string_util.h"
#include "strings.h"
#include "text_window.h"
#include "constants/songs.h"
#include "m4a.h"
#include "field_effect.h"
#include "region_map.h"
#include "sound.h"
#include "constants/region_map_sections.h"
#include "heal_location.h"
#include "constants/heal_locations.h"

#define MAP_WIDTH 22
#define MAP_HEIGHT 15
#define MAPCURSOR_X_MIN 4
#define MAPCURSOR_Y_MIN 4

struct WindowCoords
{
    u16 x1;
    u16 y1;
    u16 x2;
    u16 y2;
};

// Static type declarations

// Static RAM declarations

static EWRAM_DATA struct RegionMap *gRegionMap = NULL;
static EWRAM_DATA struct {
    /*0x000*/ void (*unk_000)(void);
    /*0x004*/ u16 unk_004;
    /*0x006*/ u16 mapSecId;
    /*0x008*/ struct RegionMap regionMap;
    /*0x88c*/ u8 unk_88c[0x1c0];
    /*0xa4c*/ u8 unk_a4c[0x26];
    /*0xa72*/ bool8 unk_a72;
} *sFlyMap = NULL; // a74

static bool32 gUnknown_03001180;
static bool32 gUnknown_03001184;

// Static ROM declarations

static u8 ProcessRegionMapInput_Full(void);
static u8 MoveRegionMapCursor_Full(void);
static u8 GetRegionMapSectionIdAt_Internal(s16 x, s16 y, u8 region, bool8 secondary);
static void RegionMap_SetBG2XAndBG2Y(s16 x, s16 y);
static void RegionMap_InitializeStateBasedOnPlayerLocation(void);
static void RegionMap_InitializeStateBasedOnSSTidalLocation(void);
static u8 get_flagnr_blue_points(u16 mapSecId);
static u16 CorrectSpecialMapSecId_Internal(u16 mapSecId);
static u16 RegionMap_GetTerraCaveMapSecId(void);
static void RegionMap_GetMarineCaveCoords(u16 *x, u16 *y);
static bool32 RegionMap_IsPlayerInCave(u8 mapSecId);
static void RegionMap_GetPositionOfCursorWithinMapSection(void);
static bool8 RegionMap_IsMapSecIdInNextRow(u16 y);
static void SpriteCallback_CursorFull(struct Sprite *sprite);
static void HideRegionMapPlayerIcon(void);
static void UnhideRegionMapPlayerIcon(void);
static void RegionMapPlayerIconSpriteCallback(struct Sprite *sprite);
static void sub_81248C0(void);
static void sub_81248D4(void);
static void sub_81248F4(void callback(void));
static void sub_8124904(void);
static void sub_8124A70(void);
static void sub_8124AD4(void);
static void sub_8124BE4(void);
static void sub_8124CBC(struct Sprite *sprite);
static void sub_8124D14(void);
static void sub_8124D64(void);
static void sub_8124E0C(void);

static void LoadPrimaryLayerMapSec(void);
static void LoadSecondaryLayerMapSec(void);
static void SetupShadowBoxes(u8 layerNum, const struct WindowCoords *coords);
static u8 GetMapSecStatusByLayer(u8 layer);
static void SetShadowBoxState(u8 offset, bool8 hide);
static const u8 *GetRegionMapTilemap(u8 region);

// .rodata
extern const struct SpritePalette gSpritePalette_PokegearMenuSprites;
static const u16 sRegionMapCursorPal[] = INCBIN_U16("graphics/region_map/cursor.gbapal");
static const u8 sRegionMapCursorGfxLZ[] = INCBIN_U8("graphics/region_map/cursor_small.4bpp.lz");
static const u16 sRegionMapPal[] = INCBIN_U16("graphics/region_map/region_map.gbapal");
static const u8 sRegionMapTileset[] = INCBIN_U8("graphics/region_map/region_map.4bpp.lz");
static const u8 sRegionMapJohtoTilemap[] = INCBIN_U8("graphics/region_map/johto_map.bin.lz");
static const u8 sRegionMapKantoTilemap[] = INCBIN_U8("graphics/region_map/kanto_map.bin.lz");
static const u16 sRegionMapTownNames_Pal[] = INCBIN_U16("graphics/region_map/town_names.gbapal");
static const u16 sRegionMapPlayerIcon_GoldPal[] = INCBIN_U16("graphics/region_map/gold_icon.gbapal");
static const u8 sRegionMapPlayerIcon_GoldGfx[] = INCBIN_U8("graphics/region_map/gold_icon.4bpp");
static const u16 sRegionMapPlayerIcon_KrisPal[] = INCBIN_U16("graphics/region_map/kris_icon.gbapal");
static const u8 sRegionMapPlayerIcon_KrisGfx[] = INCBIN_U8("graphics/region_map/kris_icon.4bpp");
static const u8 sRegionMapDots_Gfx[] = INCBIN_U8("graphics/region_map/dots.4bpp");
static const u16 sRegionMapDots_Pal[] = INCBIN_U16("graphics/region_map/dots.gbapal");
static const u8 sRegionMapNames_Gfx[] = INCBIN_U8("graphics/region_map/region_names.4bpp");
static const u8 sRegionMapNamesCurve_Gfx[] = INCBIN_U8("graphics/region_map/region_names_curve.4bpp");

static const u8 sMapSectionLayout_JohtoPrimary[] = INCBIN_U8("graphics/region_map/mapsec_layout_johto_primary.bin");
static const u8 sMapSectionLayout_JohtoSecondary[] = INCBIN_U8("graphics/region_map/mapsec_layout_johto_secondary.bin");
static const u8 sMapSectionLayout_KantoPrimary[] = INCBIN_U8("graphics/region_map/mapsec_layout_kanto_primary.bin");
static const u8 sMapSectionLayout_KantoSecondary[] = INCBIN_U8("graphics/region_map/mapsec_layout_kanto_secondary.bin");

#include "data/region_map/region_map_entries.h"
#include "data/region_map/mapsec_to_region.h"

static const u16 sRegionMap_SpecialPlaceLocations[][2] = {
    {MAPSEC_UNDERWATER_TERRA_CAVE,     MAPSEC_ROUTE_105},
    {MAPSEC_UNDERWATER_124,            MAPSEC_ROUTE_124},
    {MAPSEC_UNDERWATER_UNK1,           MAPSEC_ROUTE_129},
    {MAPSEC_UNDERWATER_125,            MAPSEC_ROUTE_126},
    {MAPSEC_UNDERWATER_126,            MAPSEC_ROUTE_127},
    {MAPSEC_UNDERWATER_127,            MAPSEC_ROUTE_128},
    {MAPSEC_UNDERWATER_129,            MAPSEC_ROUTE_129},
    {MAPSEC_UNDERWATER_SOOTOPOLIS,     MAPSEC_SOOTOPOLIS_CITY},
    {MAPSEC_UNDERWATER_128,            MAPSEC_ROUTE_128},
    {MAPSEC_AQUA_HIDEOUT,              MAPSEC_LILYCOVE_CITY},
    {MAPSEC_AQUA_HIDEOUT_OLD,          MAPSEC_LILYCOVE_CITY},
    {MAPSEC_MAGMA_HIDEOUT,             MAPSEC_ROUTE_112},
    {MAPSEC_UNDERWATER_SEALED_CHAMBER, MAPSEC_ROUTE_134},
    {MAPSEC_PETALBURG_WOODS,           MAPSEC_ROUTE_104},
    {MAPSEC_JAGGED_PASS,               MAPSEC_ROUTE_112},
    {MAPSEC_MT_PYRE,                   MAPSEC_ROUTE_122},
    {MAPSEC_SKY_PILLAR,                MAPSEC_ROUTE_131},
    {MAPSEC_MIRAGE_TOWER,              MAPSEC_ROUTE_111},
    {MAPSEC_TRAINER_HILL,              MAPSEC_ROUTE_111},
    {MAPSEC_DESERT_UNDERPASS,          MAPSEC_ROUTE_114},
    {MAPSEC_ALTERING_CAVE_2,           MAPSEC_ROUTE_103},
    {MAPSEC_ARTISAN_CAVE,              MAPSEC_ROUTE_103},
    {MAPSEC_ABANDONED_SHIP,            MAPSEC_ROUTE_108},
    {MAPSEC_NONE,                      MAPSEC_NONE}
};

static const u16 sRegionMap_MarineCaveMapSecIds[] = {
    MAPSEC_MARINE_CAVE,
    MAPSEC_UNDERWATER_MARINE_CAVE,
    MAPSEC_UNDERWATER_MARINE_CAVE
};

static const u16 sTerraCaveMapSectionIds[] = {
    MAPSEC_ROUTE_114,
    MAPSEC_ROUTE_114,
    MAPSEC_ROUTE_115,
    MAPSEC_ROUTE_115,
    MAPSEC_ROUTE_116,
    MAPSEC_ROUTE_116,
    MAPSEC_ROUTE_118,
    MAPSEC_ROUTE_118,
    MAPSEC_ROUTE_105,
    MAPSEC_ROUTE_105,
    MAPSEC_ROUTE_125,
    MAPSEC_ROUTE_125,
    MAPSEC_ROUTE_127,
    MAPSEC_ROUTE_127,
    MAPSEC_ROUTE_129,
    MAPSEC_ROUTE_129
};

static const struct UCoords16 sTerraCaveLocationCoords[] = {
    {0x00, 0x0a},
    {0x00, 0x0c},
    {0x18, 0x03},
    {0x19, 0x04},
    {0x19, 0x06},
    {0x19, 0x07},
    {0x18, 0x0a},
    {0x18, 0x0a}
};

static const u8 sRegionMap_MapSecAquaHideoutOld[] = {
    MAPSEC_AQUA_HIDEOUT_OLD
};

static const struct OamData sRegionMapCursorOam = {
    .size = 1, .priority = 2
};

static const union AnimCmd sRegionMapCursorAnim1[] = {
    ANIMCMD_FRAME(0, 20),
    ANIMCMD_FRAME(4, 20),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd *const sRegionMapCursorAnimTable[] = {
    sRegionMapCursorAnim1
};

static const struct SpritePalette sRegionMapCursorSpritePalette = { sRegionMapCursorPal, 0 };

static const struct SpriteTemplate sRegionMapCursorSpriteTemplate = {
    0,
    0,
    &sRegionMapCursorOam,
    sRegionMapCursorAnimTable,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCallback_CursorFull
};

static const struct OamData sRegionMapPlayerIconOam = {
    .size = 1, .priority = 2
};

static const struct OamData sRegionMapDotsOam = {
    .priority = 2
};

static const union AnimCmd sRegionMapDotsAnim1[] = {
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_END
};

static const union AnimCmd sRegionMapDotsAnim2[] = {
    ANIMCMD_FRAME(1, 5),
    ANIMCMD_END
};

static const union AnimCmd *const sRegionMapDotsAnimTable[] = {
    sRegionMapDotsAnim1,
    sRegionMapDotsAnim2
};

static const struct OamData sRegionMapNameCurveOam = {
    .shape = ST_OAM_SQUARE, .size = 0, .priority = 2
};

static const struct SpriteTemplate sRegionMapNameCurveSpriteTemplate = {
    0,
    0,
    &sRegionMapNameCurveOam,
    gDummySpriteAnimTable,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCallbackDummy
};

static const struct OamData sRegionMapNameOam = {
    .shape = ST_OAM_H_RECTANGLE, .size = 1, .priority = 2
};

static const union AnimCmd sRegionMapNameJohto[] = {
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_END
};

static const union AnimCmd sRegionMapNameKanto[] = {
    ANIMCMD_FRAME(4, 5),
    ANIMCMD_END
};

static const union AnimCmd sRegionMapNameSevii[] = {
    ANIMCMD_FRAME(8, 5),
    ANIMCMD_END
};

static const union AnimCmd *const sRegionMapNameAnimTable[] = {
    sRegionMapNameJohto,
    sRegionMapNameKanto,
    sRegionMapNameSevii
};

static const struct SpriteTemplate sRegionMapNameSpriteTemplate = {
    0,
    0,
    &sRegionMapNameOam,
    sRegionMapNameAnimTable,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCallbackDummy
};

static const u8 sRegionMapEventSectionIds[] = {
    MAPSEC_BIRTH_ISLAND_2,
    MAPSEC_FARAWAY_ISLAND,
    MAPSEC_NAVEL_ROCK2
};

static const u16 sRegionMapFramePal[] = INCBIN_U16("graphics/region_map/map_frame.gbapal");

static const u8 sRegionMapFrameGfxLZ[] = INCBIN_U8("graphics/region_map/map_frame.4bpp.lz");

static const u8 sRegionMapFrameTilemapLZ[] = INCBIN_U8("graphics/region_map/map_frame.bin.lz");

static const u16 Unknown_085A1D48[] = INCBIN_U16("graphics/region_map/fly_target_icons.gbapal");

static const u8 sUnknown_085A1D68[] = INCBIN_U8("graphics/region_map/fly_target_icons.4bpp.lz");

static const u8 sMapHealLocations[][3] = {
    {MAP_GROUP(LITTLEROOT_TOWN), MAP_NUM(LITTLEROOT_TOWN), HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F},
    {MAP_GROUP(OLDALE_TOWN), MAP_NUM(OLDALE_TOWN), HEAL_LOCATION_OLDALE_TOWN},
    {MAP_GROUP(DEWFORD_TOWN), MAP_NUM(DEWFORD_TOWN), HEAL_LOCATION_DEWFORD_TOWN},
    {MAP_GROUP(LAVARIDGE_TOWN), MAP_NUM(LAVARIDGE_TOWN), HEAL_LOCATION_LAVARIDGE_TOWN},
    {MAP_GROUP(FALLARBOR_TOWN), MAP_NUM(FALLARBOR_TOWN), HEAL_LOCATION_FALLARBOR_TOWN},
    {MAP_GROUP(VERDANTURF_TOWN), MAP_NUM(VERDANTURF_TOWN), HEAL_LOCATION_VERDANTURF_TOWN},
    {MAP_GROUP(PACIFIDLOG_TOWN), MAP_NUM(PACIFIDLOG_TOWN), HEAL_LOCATION_PACIFIDLOG_TOWN},
    {MAP_GROUP(PETALBURG_CITY), MAP_NUM(PETALBURG_CITY), HEAL_LOCATION_PETALBURG_CITY},
    {MAP_GROUP(SLATEPORT_CITY), MAP_NUM(SLATEPORT_CITY), HEAL_LOCATION_SLATEPORT_CITY},
    {MAP_GROUP(MAUVILLE_CITY), MAP_NUM(MAUVILLE_CITY), HEAL_LOCATION_MAUVILLE_CITY},
    {MAP_GROUP(RUSTBORO_CITY), MAP_NUM(RUSTBORO_CITY), HEAL_LOCATION_RUSTBORO_CITY},
    {MAP_GROUP(FORTREE_CITY), MAP_NUM(FORTREE_CITY), HEAL_LOCATION_FORTREE_CITY},
    {MAP_GROUP(LILYCOVE_CITY), MAP_NUM(LILYCOVE_CITY), HEAL_LOCATION_LILYCOVE_CITY},
    {MAP_GROUP(MOSSDEEP_CITY), MAP_NUM(MOSSDEEP_CITY), HEAL_LOCATION_MOSSDEEP_CITY},
    {MAP_GROUP(SOOTOPOLIS_CITY), MAP_NUM(SOOTOPOLIS_CITY), HEAL_LOCATION_SOOTOPOLIS_CITY},
    {MAP_GROUP(EVER_GRANDE_CITY), MAP_NUM(EVER_GRANDE_CITY), HEAL_LOCATION_EVER_GRANDE_CITY_1},
    {MAP_GROUP(ROUTE101), MAP_NUM(ROUTE101), 0},
    {MAP_GROUP(ROUTE102), MAP_NUM(ROUTE102), 0},
    {MAP_GROUP(ROUTE103), MAP_NUM(ROUTE103), 0},
    {MAP_GROUP(ROUTE104), MAP_NUM(ROUTE104), 0},
    {MAP_GROUP(ROUTE105), MAP_NUM(ROUTE105), 0},
    {MAP_GROUP(ROUTE106), MAP_NUM(ROUTE106), 0},
    {MAP_GROUP(ROUTE107), MAP_NUM(ROUTE107), 0},
    {MAP_GROUP(ROUTE108), MAP_NUM(ROUTE108), 0},
    {MAP_GROUP(ROUTE109), MAP_NUM(ROUTE109), 0},
    {MAP_GROUP(ROUTE110), MAP_NUM(ROUTE110), 0},
    {MAP_GROUP(ROUTE111), MAP_NUM(ROUTE111), 0},
    {MAP_GROUP(ROUTE112), MAP_NUM(ROUTE112), 0},
    {MAP_GROUP(ROUTE113), MAP_NUM(ROUTE113), 0},
    {MAP_GROUP(ROUTE114), MAP_NUM(ROUTE114), 0},
    {MAP_GROUP(ROUTE115), MAP_NUM(ROUTE115), 0},
    {MAP_GROUP(ROUTE116), MAP_NUM(ROUTE116), 0},
    {MAP_GROUP(ROUTE117), MAP_NUM(ROUTE117), 0},
    {MAP_GROUP(ROUTE118), MAP_NUM(ROUTE118), 0},
    {MAP_GROUP(ROUTE119), MAP_NUM(ROUTE119), 0},
    {MAP_GROUP(ROUTE120), MAP_NUM(ROUTE120), 0},
    {MAP_GROUP(ROUTE121), MAP_NUM(ROUTE121), 0},
    {MAP_GROUP(ROUTE122), MAP_NUM(ROUTE122), 0},
    {MAP_GROUP(ROUTE123), MAP_NUM(ROUTE123), 0},
    {MAP_GROUP(ROUTE124), MAP_NUM(ROUTE124), 0},
    {MAP_GROUP(ROUTE125), MAP_NUM(ROUTE125), 0},
    {MAP_GROUP(ROUTE126), MAP_NUM(ROUTE126), 0},
    {MAP_GROUP(ROUTE127), MAP_NUM(ROUTE127), 0},
    {MAP_GROUP(ROUTE128), MAP_NUM(ROUTE128), 0},
    {MAP_GROUP(ROUTE129), MAP_NUM(ROUTE129), 0},
    {MAP_GROUP(ROUTE130), MAP_NUM(ROUTE130), 0},
    {MAP_GROUP(ROUTE131), MAP_NUM(ROUTE131), 0},
    {MAP_GROUP(ROUTE132), MAP_NUM(ROUTE132), 0},
    {MAP_GROUP(ROUTE133), MAP_NUM(ROUTE133), 0},
    {MAP_GROUP(ROUTE134), MAP_NUM(ROUTE134), 0}
};

static const u8 *const gUnknown_085A1ED4[] = {
    gText_PokemonLeague,
    gText_PokemonCenter
};

static const struct {
    const u8 *const *name;
    u16 mapSecId;
    u16 flag;
} gUnknown_085A1EDC[] = {
    gUnknown_085A1ED4,
    MAPSEC_EVER_GRANDE_CITY,
    FLAG_LANDMARK_POKEMON_LEAGUE
};

static const struct BgTemplate gUnknown_085A1EE4[] = {
    { .bg = 0, .charBaseIndex = 0, .mapBaseIndex = 31, .screenSize = 0, .paletteMode = 0, .priority = 0 },
    { .bg = 1, .charBaseIndex = 3, .mapBaseIndex = 30, .screenSize = 0, .paletteMode = 0, .priority = 1 },
    { .bg = 2, .charBaseIndex = 2, .mapBaseIndex = 29, .screenSize = 0, .paletteMode = 0, .priority = 2 }
};

static const struct WindowTemplate gUnknown_085A1EF0[] = {
    { 0, 17, 17, 12,  2, 15, 0x01 },
    { 0, 17, 15, 12,  4, 15, 0x19 },
    { 0,  1, 18, 14,  2, 15, 0x49 },
    DUMMY_WIN_TEMPLATE
};

static const struct SpritePalette gUnknown_085A1F10 = {
    Unknown_085A1D48, 2
};

static const u16 sUnknown_085A1F18[][2] = {
    {FLAG_LANDMARK_BATTLE_FRONTIER, MAPSEC_BATTLE_FRONTIER},
    {-1, MAPSEC_NONE}
};

static const struct OamData gOamData_085A1F20 = {
    .priority = 2
};

static const union AnimCmd gUnknown_085A1F28[] = {
    ANIMCMD_FRAME( 0, 5),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_085A1F30[] = {
    ANIMCMD_FRAME( 1, 5),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_085A1F38[] = {
    ANIMCMD_FRAME( 3, 5),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_085A1F40[] = {
    ANIMCMD_FRAME( 5, 5),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_085A1F48[] = {
    ANIMCMD_FRAME( 6, 5),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_085A1F50[] = {
    ANIMCMD_FRAME( 8, 5),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_085A1F58[] = {
    ANIMCMD_FRAME(10, 5),
    ANIMCMD_END
};

static const union AnimCmd *const gUnknown_085A1F60[] = {
    gUnknown_085A1F28,
    gUnknown_085A1F30,
    gUnknown_085A1F38,
    gUnknown_085A1F40,
    gUnknown_085A1F48,
    gUnknown_085A1F50,
    gUnknown_085A1F58
};

static const struct SpriteTemplate gUnknown_085A1F7C = {
    2,
    2,
    &gOamData_085A1F20,
    gUnknown_085A1F60,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCallbackDummy
};

static const u8 whiteTextColor[] = {
	0x00, 0x01, 0x02
};

static const struct WindowCoords blankWindowCoords = {
    .x1 = 0,
    .y1 = 0,
    .x2 = 0,
    .y2 = 0,
};

static const struct WindowCoords windowCoords[] = {
    {
        .x1 = 24,
        .y1 = 16,
        .x2 = 144,
        .y2 = 32,
    },
    {
        .x1 = 24,
        .y1 = 32,
        .x2 = 144,
        .y2 = 48,
    },
};

// .text

void InitRegionMap(struct RegionMap *regionMap, s8 xOffset)
{
    sub_8122CF8(regionMap, NULL, xOffset);
    while (sub_8122DB0());
}

void sub_8122CF8(struct RegionMap *regionMap, const struct BgTemplate *template, s8 xOffset)
{
    gRegionMap = regionMap;
    gRegionMap->initStep = 0;
    gRegionMap->xOffset = xOffset;
    gRegionMap->currentRegion = GetCurrentRegion();
    gRegionMap->canChangeRegion = FALSE;    // TODO: some flag check here
    gRegionMap->inputCallback = ProcessRegionMapInput_Full;

    if (template != NULL)
    {
        gRegionMap->bgNum = template->bg;
        gRegionMap->charBaseIdx = template->charBaseIndex;
        gRegionMap->mapBaseIdx = template->mapBaseIndex;
        gRegionMap->bgManaged = TRUE;
    }
    else
    {
        gRegionMap->bgNum = 2;
        gRegionMap->charBaseIdx = 2;
        gRegionMap->mapBaseIdx = 29;
        gRegionMap->bgManaged = FALSE;
    }
}

void sub_8122D88(struct RegionMap *regionMap)
{
    gRegionMap = regionMap;
    RegionMap_InitializeStateBasedOnPlayerLocation();
    gRegionMap->playerIconSpritePosX = gRegionMap->cursorPosX;
    gRegionMap->playerIconSpritePosY = gRegionMap->cursorPosY;
}

bool8 sub_8122DB0(void)
{
    const struct WindowTemplate layerTemplates[] = {
        {0, 3, 2, 15, 2, 14, 1},
        {0, 3, 4, 15, 2, 14, 31}
    };

    struct WindowTemplate window;

    const u8 *regionTilemap;
    u8 i;

    switch (gRegionMap->initStep)
    {
        case 0:
            SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_TGT1_OBJ | BLDCNT_EFFECT_DARKEN);
            SetGpuReg(REG_OFFSET_BLDY, 6);
            SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0 |
                                        WININ_WIN0_BG1 |
                                        WININ_WIN0_BG2 |
                                        WININ_WIN0_BG3 |
                                        WININ_WIN0_OBJ |
                                        WININ_WIN0_CLR |
                                        WININ_WIN1_BG0 |
                                        WININ_WIN1_BG1 |
                                        WININ_WIN1_BG2 |
                                        WININ_WIN1_BG3 |
                                        WININ_WIN1_OBJ |
                                        WININ_WIN1_CLR);
            SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 |
                                         WINOUT_WIN01_BG1 |
                                         WINOUT_WIN01_BG2 |
                                         WINOUT_WIN01_BG3 |
                                         WINOUT_WIN01_OBJ);
            SetupShadowBoxes(0, &windowCoords[0]);
            SetupShadowBoxes(1, &windowCoords[1]);

            window = layerTemplates[0];
            window.tilemapLeft += gRegionMap->xOffset;
            gRegionMap->primaryWindowId = AddWindow(&window);

            window = layerTemplates[1];
            window.tilemapLeft += gRegionMap->xOffset;
            gRegionMap->secondaryWindowId = AddWindow(&window);
            break;
        case 1:
            if (gRegionMap->bgManaged)
            {
                decompress_and_copy_tile_data_to_vram(gRegionMap->bgNum, sRegionMapTileset, 0, 0, 0);
            }
            else
            {
                LZ77UnCompVram(sRegionMapTileset, (u16 *)BG_CHAR_ADDR(2));
            }
            break;
        case 2:
            /*regionTilemap = GetRegionMapTilemap(gRegionMap->currentRegion);
            if (gRegionMap->bgManaged)
            {
                if (!free_temp_tile_data_buffers_if_possible())
                {
                    decompress_and_copy_tile_data_to_vram(gRegionMap->bgNum, regionTilemap, 0, 0, 1);
                }
            }
            else
            {
                LZ77UnCompVram(regionTilemap, (u16 *)BG_SCREEN_ADDR(28));
            }*/
            {
                int size;
                u8 x, y;
                u16 *ptr = malloc_and_decompress(GetRegionMapTilemap(gRegionMap->currentRegion), &size);
                
                if (!gRegionMap->canChangeRegion)
                {
                    for (y = 16; y < 19; y++)
                    {
                        for (x = 24; x < 27; x++)
                        {
                            ptr[x + y * 32] = 0x7096;
                        }
                    }
                }

                if (gRegionMap->bgManaged)
                {
                    if (!free_temp_tile_data_buffers_if_possible())
                    {
                        copy_decompressed_tile_data_to_vram(gRegionMap->bgNum, ptr, size, gRegionMap->xOffset, 1);
                    }
                }
                else
                {
                    CpuFastCopy(ptr, (u16 *)BG_SCREEN_ADDR(29) + gRegionMap->xOffset, size);
                }

                FREE_AND_SET_NULL(ptr);
            }
            break;
        case 3:
            if (!free_temp_tile_data_buffers_if_possible())
            {
                LoadPalette(sRegionMapPal, 0x70, sizeof(sRegionMapPal));
                LoadPalette(sRegionMapTownNames_Pal, 0xE0, sizeof(sRegionMapTownNames_Pal));
            }
            break;
        case 4:
            LZ77UnCompWram(sRegionMapCursorGfxLZ, gRegionMap->cursorImage);
            break;
        case 5:
            RegionMap_InitializeStateBasedOnPlayerLocation();
            SetShadowBoxState(0, FALSE);

            if (gRegionMap->secondaryMapSecId != MAPSEC_NONE)
                SetShadowBoxState(1, FALSE);
            
            gRegionMap->playerIconSpritePosX = gRegionMap->cursorPosX;
            gRegionMap->playerIconSpritePosY = gRegionMap->cursorPosY;
            gRegionMap->primaryMapSecId = CorrectSpecialMapSecId_Internal(gRegionMap->primaryMapSecId);
            gRegionMap->primaryMapSecStatus = get_flagnr_blue_points(gRegionMap->primaryMapSecId);
            gRegionMap->secondaryMapSecId = CorrectSpecialMapSecId_Internal(gRegionMap->secondaryMapSecId);
            gRegionMap->secondaryMapSecStatus = get_flagnr_blue_points(gRegionMap->secondaryMapSecId);

            LoadPrimaryLayerMapSec();
            LoadSecondaryLayerMapSec();
            schedule_bg_copy_tilemap_to_vram(0);
            break;
        case 6:
            RegionMap_GetPositionOfCursorWithinMapSection();

            for (i = 0; i < sizeof(gRegionMap->spriteIds); i++)
            {
                gRegionMap->spriteIds[i] = 0xFF;
            }

            gRegionMap->cursorMovementFrameCounter = 0;
            gRegionMap->blinkPlayerIcon = FALSE;
            gRegionMap->initStep++;
            return FALSE;
        default:
            return FALSE;
    }
    gRegionMap->initStep++;
    return TRUE;
}

static const u8 *GetRegionMapTilemap(u8 region)
{
    const u8 *const tilemaps[] = {
        sRegionMapJohtoTilemap,
        sRegionMapKantoTilemap,
        sRegionMapJohtoTilemap,
        sRegionMapJohtoTilemap,
        sRegionMapJohtoTilemap,
    };

    return tilemaps[region];
}

void sub_8123030(u16 a0, u32 a1)
{
    BlendPalettes(0x380, a1, a0);
    CpuCopy16(gPlttBufferFaded + 0x70, gPlttBufferUnfaded + 0x70, 0x60);
}

void FreeRegionMapIconResources(void)
{
    if (gRegionMap->spriteIds[0] != 0xFF)
    {
        DestroySprite(&gSprites[gRegionMap->spriteIds[0]]);
        FreeSpriteTilesByTag(gRegionMap->cursorTileTag);
        FreeSpritePaletteByTag(gRegionMap->cursorPaletteTag);
    }
    if (gRegionMap->spriteIds[1] != 0xFF)
    {
        DestroySprite(&gSprites[gRegionMap->spriteIds[1]]);
        FreeSpriteTilesByTag(gRegionMap->playerIconTileTag);
        FreeSpritePaletteByTag(gRegionMap->playerIconPaletteTag);
    }
}

void FreeRegionMapResources(bool8 shouldClearNamePalette)
{
    u8 i;

    if (gRegionMap->spriteIds[0] != 0xFF)
    {
        DestroySprite(&gSprites[gRegionMap->spriteIds[0]]);
        FreeSpriteTilesByTag(gRegionMap->cursorTileTag);
        FreeSpritePaletteByTag(gRegionMap->cursorPaletteTag);
    }
    if (gRegionMap->spriteIds[1] != 0xFF)
    {
        DestroySprite(&gSprites[gRegionMap->spriteIds[1]]);
        FreeSpriteTilesByTag(gRegionMap->playerIconTileTag);
        FreeSpritePaletteByTag(gRegionMap->playerIconPaletteTag);
    }
    if (gRegionMap->spriteIds[2] != 0xFF)
    {
        DestroySprite(&gSprites[gRegionMap->spriteIds[2]]);
        FreeSpriteTilesByTag(gRegionMap->regionNameCurveTileTag);
        if (shouldClearNamePalette)
        {
            FreeSpritePaletteByTag(gRegionMap->regionNamePaletteTag);
            shouldClearNamePalette = FALSE;
        }
    }
    if (gRegionMap->spriteIds[3] != 0xFF)
    {
        DestroySprite(&gSprites[gRegionMap->spriteIds[3]]);
        FreeSpriteTilesByTag(gRegionMap->regionNameMainTileTag);
        if (shouldClearNamePalette)
        {
            FreeSpritePaletteByTag(gRegionMap->regionNamePaletteTag);
            shouldClearNamePalette = FALSE;
        }
    }

    for (i = 4; i < sizeof(gRegionMap->spriteIds); i++)
    {
        if (gRegionMap->spriteIds[i] != 0xFF)
        {
            DestroySprite(&gSprites[gRegionMap->spriteIds[i]]);
        }
    }
    
    FreeSpriteTilesByTag(gRegionMap->dotsTileTag);
    FreeSpritePaletteByTag(gRegionMap->dotsPaletteTag);
    
    FillWindowPixelBuffer(gRegionMap->primaryWindowId, 0);
    ClearWindowTilemap(gRegionMap->primaryWindowId);
    CopyWindowToVram(gRegionMap->primaryWindowId, 2);
    RemoveWindow(gRegionMap->primaryWindowId);

    FillWindowPixelBuffer(gRegionMap->secondaryWindowId, 0);
    ClearWindowTilemap(gRegionMap->secondaryWindowId);
    CopyWindowToVram(gRegionMap->secondaryWindowId, 2);
    RemoveWindow(gRegionMap->secondaryWindowId);

    schedule_bg_copy_tilemap_to_vram(0);

    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);

    FREE_AND_SET_NULL(gRegionMap);
}

u8 sub_81230AC(void)
{
    return gRegionMap->inputCallback();
}

static u8 ProcessRegionMapInput_Full(void)
{
    u8 input;

    input = INPUT_EVENT_NONE;
    gRegionMap->cursorDeltaX = 0;
    gRegionMap->cursorDeltaY = 0;
    if (gMain.heldKeys & DPAD_UP && gRegionMap->cursorPosY > 0)
    {
        gRegionMap->cursorDeltaY = -1;
        input = INPUT_EVENT_MOVE_START;
    }
    if (gMain.heldKeys & DPAD_DOWN && gRegionMap->cursorPosY < MAP_HEIGHT - 1)
    {
        gRegionMap->cursorDeltaY = +1;
        input = INPUT_EVENT_MOVE_START;
    }
    if (gMain.heldKeys & DPAD_LEFT && gRegionMap->cursorPosX > 0)
    {
        gRegionMap->cursorDeltaX = -1;
        input = INPUT_EVENT_MOVE_START;
    }
    if (gMain.heldKeys & DPAD_RIGHT && gRegionMap->cursorPosX < MAP_WIDTH - 1)
    {
        gRegionMap->cursorDeltaX = +1;
        input = INPUT_EVENT_MOVE_START;
    }
    if (gMain.newKeys & A_BUTTON)
    {
        input = INPUT_EVENT_A_BUTTON;
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        input = INPUT_EVENT_B_BUTTON;
    }
    if (input == INPUT_EVENT_MOVE_START)
    {
        gRegionMap->cursorMovementFrameCounter = 4;
        gRegionMap->inputCallback = MoveRegionMapCursor_Full;
    }
    return input;
}

static bool8 LoadMapLayersFromPosition(u16 x, u16 y)
{
    u8 mapSecId;
    bool8 sameSecondary = TRUE;

    mapSecId = GetRegionMapSectionIdAt_Internal(x, y, gRegionMap->currentRegion, FALSE);
    gRegionMap->primaryMapSecStatus = get_flagnr_blue_points(mapSecId);
    if (mapSecId != gRegionMap->primaryMapSecId)
    {
        gRegionMap->primaryMapSecId = mapSecId;
        LoadPrimaryLayerMapSec();
    }

    mapSecId = GetRegionMapSectionIdAt_Internal(x, y, gRegionMap->currentRegion, TRUE);
    gRegionMap->secondaryMapSecStatus = get_flagnr_blue_points(mapSecId);
    if (mapSecId != gRegionMap->secondaryMapSecId)
    {
        gRegionMap->secondaryMapSecId = mapSecId;
        LoadSecondaryLayerMapSec();
        sameSecondary = FALSE;
    }

    schedule_bg_copy_tilemap_to_vram(0);
    SetupShadowBoxes(1, &windowCoords[1]);

    return sameSecondary;
}

static u8 MoveRegionMapCursor_Full(void)
{
    bool8 sameSecondary;
    u8 inputEvent;

    if (gRegionMap->cursorMovementFrameCounter != 0)
    {
        return INPUT_EVENT_MOVE_CONT;
    }
    if (gRegionMap->cursorDeltaX > 0)
    {
        gRegionMap->cursorPosX++;
    }
    if (gRegionMap->cursorDeltaX < 0)
    {
        gRegionMap->cursorPosX--;
    }
    if (gRegionMap->cursorDeltaY > 0)
    {
        gRegionMap->cursorPosY++;
    }
    if (gRegionMap->cursorDeltaY < 0)
    {
        gRegionMap->cursorPosY--;
    }

    sameSecondary = LoadMapLayersFromPosition(gRegionMap->cursorPosX, gRegionMap->cursorPosY);
    inputEvent = INPUT_EVENT_MOVE_END;

    if ((!sameSecondary && gRegionMap->secondaryMapSecStatus >= MAPSECTYPE_CITY_CANFLY) || gRegionMap->primaryMapSecStatus >= MAPSECTYPE_CITY_CANFLY)
    {
        PlaySE(SE_Z_SCROLL);
    }
    else if (gRegionMap->canChangeRegion && gRegionMap->cursorPosX == 21 && gRegionMap->cursorPosY == 13)
    {
        PlaySE(SE_W255);
        inputEvent = INPUT_EVENT_SWITCH;
    }

    if (gRegionMap->secondaryMapSecStatus == MAPSECTYPE_CITY_CANFLY)
    {
        inputEvent = INPUT_EVENT_LANDMARK;
    }
    
    RegionMap_GetPositionOfCursorWithinMapSection();
    gRegionMap->inputCallback = ProcessRegionMapInput_Full;
    return inputEvent;
}

static void LoadPrimaryLayerMapSec(void)
{
    ClearWindowTilemap(gRegionMap->primaryWindowId);
	FillWindowPixelBuffer(gRegionMap->primaryWindowId, 0);

	if (gRegionMap->primaryMapSecId != MAPSEC_NONE)
    {
		GetMapName(gRegionMap->primaryMapSecName, gRegionMap->primaryMapSecId, 0);
		box_print(gRegionMap->primaryWindowId, 1, 2, 2, whiteTextColor, 0, gRegionMap->primaryMapSecName);
		PutWindowTilemap(gRegionMap->primaryWindowId);
		CopyWindowToVram(gRegionMap->primaryWindowId, 3);
		SetupShadowBoxes(0, &windowCoords[0]);
    }
	else
    {
		SetupShadowBoxes(0, &blankWindowCoords);
	}
}

static void LoadSecondaryLayerMapSec(void)
{
    static const u8 mapNamePalDataPointerTable[][3] = {
        {0x00, 0x07, 0x02}, // green (visited)
        {0x00, 0x0A, 0x02}  // red (not yet visited)
    };

    SetShadowBoxState(1, TRUE);
    ClearWindowTilemap(gRegionMap->secondaryWindowId);

	if (gRegionMap->secondaryMapSecId != MAPSEC_NONE)
    {
        SetShadowBoxState(1, FALSE);
	    FillWindowPixelBuffer(gRegionMap->secondaryWindowId, 0);
		GetMapName(gRegionMap->secondaryMapSecName, gRegionMap->secondaryMapSecId, 0);
		box_print(gRegionMap->secondaryWindowId, 1, 12, 2, mapNamePalDataPointerTable[GetMapSecStatusByLayer(1) - 2], 0, gRegionMap->secondaryMapSecName);
		PutWindowTilemap(gRegionMap->secondaryWindowId);
		CopyWindowToVram(gRegionMap->secondaryWindowId, 3);
	}
}

static void SetupShadowBoxes(u8 layerNum, const struct WindowCoords *coords)
{
    static const u8 windowIORegs[2][2] = {
        { REG_OFFSET_WIN0V, REG_OFFSET_WIN0H },
        { REG_OFFSET_WIN1V, REG_OFFSET_WIN1H }
    };

	SetGpuReg(windowIORegs[layerNum][0], WINHV_COORDS(coords->y1, coords->y2));
	SetGpuReg(windowIORegs[layerNum][1], WINHV_COORDS(coords->x1 + gRegionMap->xOffset * 8, coords->x2 + gRegionMap->xOffset * 8));
}

static void SetShadowBoxState(u8 offset, bool8 hide)
{
    static const u16 windowBits[2] = {
        0x2000, 0x4000
    };

	if (!hide)
    {
		SetGpuRegBits(REG_OFFSET_DISPCNT, windowBits[offset]);
	}
	else
    {
		ClearGpuRegBits(REG_OFFSET_DISPCNT, windowBits[offset]);
	}
}

static u8 GetMapSecStatusByLayer(u8 layer)
{
	if (layer == 1)
        return gRegionMap->secondaryMapSecStatus;
	else
        return gRegionMap->primaryMapSecStatus;
}

void sub_8123418(void)
{

}

bool8 sub_8123514(void)
{
    return FALSE;
}

void UpdateRegionMapVideoRegs(void)
{

}

void PokedexAreaScreen_UpdateRegionMapVariablesAndVideoRegs(s16 x, s16 y)
{

}

static u8 GetRegionMapSectionIdAt_Internal(s16 x, s16 y, u8 region, bool8 secondary)
{
    static const u8 *const layouts[][2] = {
        {sMapSectionLayout_JohtoPrimary, sMapSectionLayout_JohtoSecondary},
        {sMapSectionLayout_KantoPrimary, sMapSectionLayout_KantoSecondary},
        {sMapSectionLayout_JohtoPrimary, sMapSectionLayout_JohtoSecondary},
        {sMapSectionLayout_JohtoPrimary, sMapSectionLayout_JohtoSecondary},
        {sMapSectionLayout_JohtoPrimary, sMapSectionLayout_JohtoSecondary}
    };

    if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH)
    {
        return MAPSEC_NONE;
    }
    return layouts[gRegionMap->currentRegion][secondary][x + y * MAP_WIDTH];
}

static void RegionMap_InitializeStateBasedOnPlayerLocation(void)
{
    const struct MapHeader *mapHeader;
    u16 mapWidth;
    u16 mapHeight;
    u16 x;
    u16 y;
    u16 dimensionScale;
    u16 xOnMap;
    struct WarpData *storedWarp;

    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(SS_TIDAL_CORRIDOR)
        && (gSaveBlock1Ptr->location.mapNum == MAP_NUM(SS_TIDAL_CORRIDOR)
            || gSaveBlock1Ptr->location.mapNum == MAP_NUM(SS_TIDAL_LOWER_DECK)
            || gSaveBlock1Ptr->location.mapNum == MAP_NUM(SS_TIDAL_ROOMS)))
    {
        RegionMap_InitializeStateBasedOnSSTidalLocation();
        return;
    }

    switch (GetMapTypeByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
    {
        default:
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
            gRegionMap->primaryMapSecId = gMapHeader.regionMapSectionId;
            gRegionMap->playerIsInCave = FALSE;
            mapWidth = gMapHeader.mapLayout->width;
            mapHeight = gMapHeader.mapLayout->height;
            x = gSaveBlock1Ptr->pos.x;
            y = gSaveBlock1Ptr->pos.y;
            if (gRegionMap->primaryMapSecId == MAPSEC_UNDERWATER_128 || gRegionMap->primaryMapSecId == MAPSEC_UNDERWATER_MARINE_CAVE)
            {
                gRegionMap->playerIsInCave = TRUE;
            }
            break;
        case 4:
        case 7:
            if (gMapHeader.flags & 0x02)
            {
                mapHeader = Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->warp4.mapGroup, gSaveBlock1Ptr->warp4.mapNum);
                gRegionMap->primaryMapSecId = mapHeader->regionMapSectionId;
                gRegionMap->playerIsInCave = TRUE;
                mapWidth = mapHeader->mapLayout->width;
                mapHeight = mapHeader->mapLayout->height;
                x = gSaveBlock1Ptr->warp4.x;
                y = gSaveBlock1Ptr->warp4.y;
            }
            else
            {
                gRegionMap->primaryMapSecId = gMapHeader.regionMapSectionId;
                gRegionMap->playerIsInCave = TRUE;
                mapWidth = 1;
                mapHeight = 1;
                x = 1;
                y = 1;
            }
            break;
        case 9:
            mapHeader = Overworld_GetMapHeaderByGroupAndId((u16)gSaveBlock1Ptr->warp2.mapGroup, (u16)gSaveBlock1Ptr->warp2.mapNum);
            gRegionMap->primaryMapSecId = mapHeader->regionMapSectionId;
            gRegionMap->playerIsInCave = TRUE;
            mapWidth = mapHeader->mapLayout->width;
            mapHeight = mapHeader->mapLayout->height;
            x = gSaveBlock1Ptr->warp2.x;
            y = gSaveBlock1Ptr->warp2.y;
            break;
        case 8:

            gRegionMap->primaryMapSecId = gMapHeader.regionMapSectionId;
            if (gRegionMap->primaryMapSecId != MAPSEC_DYNAMIC)
            {
                storedWarp = &gSaveBlock1Ptr->warp4;
                mapHeader = Overworld_GetMapHeaderByGroupAndId(storedWarp->mapGroup, storedWarp->mapNum);
            }
            else
            {
                storedWarp = &gSaveBlock1Ptr->warp2;
                mapHeader = Overworld_GetMapHeaderByGroupAndId(storedWarp->mapGroup, storedWarp->mapNum);
                gRegionMap->primaryMapSecId = mapHeader->regionMapSectionId;
            }
            if (RegionMap_IsPlayerInCave(gRegionMap->primaryMapSecId))
            {
                gRegionMap->playerIsInCave = TRUE;
            }
            else
            {
                gRegionMap->playerIsInCave = FALSE;
            }
            mapWidth = mapHeader->mapLayout->width;
            mapHeight = mapHeader->mapLayout->height;
            x = storedWarp->x;
            y = storedWarp->y;
            break;
    }

    xOnMap = x;

    dimensionScale = mapWidth / gRegionMapEntries[gRegionMap->primaryMapSecId].width;
    if (dimensionScale == 0)
    {
        dimensionScale = 1;
    }
    x /= dimensionScale;
    if (x >= gRegionMapEntries[gRegionMap->primaryMapSecId].width)
    {
        x = gRegionMapEntries[gRegionMap->primaryMapSecId].width - 1;
    }

    dimensionScale = mapHeight / gRegionMapEntries[gRegionMap->primaryMapSecId].height;
    if (dimensionScale == 0)
    {
        dimensionScale = 1;
    }
    y /= dimensionScale;
    if (y >= gRegionMapEntries[gRegionMap->primaryMapSecId].height)
    {
        y = gRegionMapEntries[gRegionMap->primaryMapSecId].height - 1;
    }

    switch (gRegionMap->primaryMapSecId)
    {
        case MAPSEC_ROUTE_114:
            if (y != 0)
            {
                x = 0;
            }
            break;
        case MAPSEC_ROUTE_126:
        case MAPSEC_UNDERWATER_125:
            x = 0;
            if (gSaveBlock1Ptr->pos.x > 32)
            {
                x = 1;
            }
            if (gSaveBlock1Ptr->pos.x > 0x33)
            {
                x++;
            }
            y = 0;
            if (gSaveBlock1Ptr->pos.y > 0x25)
            {
                y = 1;
            }
            if (gSaveBlock1Ptr->pos.y > 0x38)
            {
                y++;
            }
            break;
        case MAPSEC_ROUTE_121:
            x = 0;
            if (xOnMap > 14)
            {
                x = 1;
            }
            if (xOnMap > 0x1C)
            {
                x++;
            }
            if (xOnMap > 0x36)
            {
                x++;
            }
            break;
        case MAPSEC_UNDERWATER_MARINE_CAVE:
            RegionMap_GetMarineCaveCoords(&gRegionMap->cursorPosX, &gRegionMap->cursorPosY);
            return;
    }
    gRegionMap->cursorPosX = gRegionMapEntries[gRegionMap->primaryMapSecId].x + x;
    gRegionMap->cursorPosY = gRegionMapEntries[gRegionMap->primaryMapSecId].y + y;
    gRegionMap->secondaryMapSecId = GetRegionMapSectionIdAt_Internal(gRegionMap->cursorPosX, gRegionMap->cursorPosY, gRegionMap->currentRegion, TRUE);
}

static void RegionMap_InitializeStateBasedOnSSTidalLocation(void)
{
    u16 y;
    u16 x;
    u8 mapGroup;
    u8 mapNum;
    u16 dimensionScale;
    s16 xOnMap;
    s16 yOnMap;
    const struct MapHeader *mapHeader;

    y = 0;
    x = 0;
    switch (GetSSTidalLocation(&mapGroup, &mapNum, &xOnMap, &yOnMap))
    {
        case 1:
            gRegionMap->primaryMapSecId = MAPSEC_SLATEPORT_CITY;
            break;
        case 2:
            gRegionMap->primaryMapSecId = MAPSEC_LILYCOVE_CITY;
            break;
        case 3:
            gRegionMap->primaryMapSecId = MAPSEC_ROUTE_124;
            break;
        case 4:
            gRegionMap->primaryMapSecId = MAPSEC_ROUTE_131;
            break;
        default:
        case 0:
            mapHeader = Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum);

            gRegionMap->primaryMapSecId = mapHeader->regionMapSectionId;
            dimensionScale = mapHeader->mapLayout->width / gRegionMapEntries[gRegionMap->primaryMapSecId].width;
            if (dimensionScale == 0)
                dimensionScale = 1;
            x = xOnMap / dimensionScale;
            if (x >= gRegionMapEntries[gRegionMap->primaryMapSecId].width)
                x = gRegionMapEntries[gRegionMap->primaryMapSecId].width - 1;

            dimensionScale = mapHeader->mapLayout->height / gRegionMapEntries[gRegionMap->primaryMapSecId].height;
            if (dimensionScale == 0)
                dimensionScale = 1;
            y = yOnMap / dimensionScale;
            if (y >= gRegionMapEntries[gRegionMap->primaryMapSecId].height)
                y = gRegionMapEntries[gRegionMap->primaryMapSecId].height - 1;
            break;
    }
    gRegionMap->playerIsInCave = FALSE;
    gRegionMap->cursorPosX = gRegionMapEntries[gRegionMap->primaryMapSecId].x + x;
    gRegionMap->cursorPosY = gRegionMapEntries[gRegionMap->primaryMapSecId].y + y;
    gRegionMap->secondaryMapSecId = GetRegionMapSectionIdAt_Internal(gRegionMap->cursorPosX, gRegionMap->cursorPosY, gRegionMap->currentRegion, TRUE);
}

static u8 get_flagnr_blue_points(u16 mapSecId)
{
    switch (mapSecId)
    {
        case MAPSEC_NONE:
            return MAPSECTYPE_NONE;
        case MAPSEC_LITTLEROOT_TOWN:
            return FlagGet(FLAG_VISITED_LITTLEROOT_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_OLDALE_TOWN:
            return FlagGet(FLAG_VISITED_OLDALE_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_DEWFORD_TOWN:
            return FlagGet(FLAG_VISITED_DEWFORD_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_LAVARIDGE_TOWN:
            return FlagGet(FLAG_VISITED_LAVARIDGE_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_FALLARBOR_TOWN:
            return FlagGet(FLAG_VISITED_FALLARBOR_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_VERDANTURF_TOWN:
            return FlagGet(FLAG_VISITED_VERDANTURF_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_PACIFIDLOG_TOWN:
            return FlagGet(FLAG_VISITED_PACIFIDLOG_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_PETALBURG_CITY:
            return FlagGet(FLAG_VISITED_PETALBURG_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_SLATEPORT_CITY:
            return FlagGet(FLAG_VISITED_SLATEPORT_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_MAUVILLE_CITY:
            return FlagGet(FLAG_VISITED_MAUVILLE_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_RUSTBORO_CITY:
            return FlagGet(FLAG_VISITED_RUSTBORO_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_FORTREE_CITY:
            return FlagGet(FLAG_VISITED_FORTREE_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_LILYCOVE_CITY:
            return FlagGet(FLAG_VISITED_LILYCOVE_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_MOSSDEEP_CITY:
            return FlagGet(FLAG_VISITED_MOSSDEEP_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_SOOTOPOLIS_CITY:
            return FlagGet(FLAG_VISITED_SOOTOPOLIS_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_EVER_GRANDE_CITY:
            return FlagGet(FLAG_VISITED_EVER_GRANDE_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
        case MAPSEC_BATTLE_FRONTIER:
            return FlagGet(FLAG_LANDMARK_BATTLE_FRONTIER) ? MAPSECTYPE_BATTLE_FRONTIER : MAPSECTYPE_NONE;
        case MAPSEC_SOUTHERN_ISLAND:
            return FlagGet(FLAG_LANDMARK_SOUTHERN_ISLAND) ? MAPSECTYPE_PLAIN : MAPSECTYPE_NONE;
        default:
            return MAPSECTYPE_PLAIN;
    }
}

u16 GetRegionMapSectionIdAt(u16 x, u16 y)
{
    return GetRegionMapSectionIdAt_Internal(x, y, REGION_JOHTO, FALSE);
}

static u16 CorrectSpecialMapSecId_Internal(u16 mapSecId)
{
    u32 i;

    for (i = 0; i < 3; i++)
    {
        if (sRegionMap_MarineCaveMapSecIds[i] == mapSecId)
        {
            return RegionMap_GetTerraCaveMapSecId();
        }
    }
    for (i = 0; sRegionMap_SpecialPlaceLocations[i][0] != MAPSEC_NONE; i++)
    {
        if (sRegionMap_SpecialPlaceLocations[i][0] == mapSecId)
        {
            return sRegionMap_SpecialPlaceLocations[i][1];
        }
    }
    return mapSecId;
}

static u16 RegionMap_GetTerraCaveMapSecId(void)
{
    s16 idx;

    idx = VarGet(VAR_0x4037) - 1;
    if (idx < 0 || idx > 15)
    {
        idx = 0;
    }
    return sTerraCaveMapSectionIds[idx];
}

static void RegionMap_GetMarineCaveCoords(u16 *x, u16 *y)
{
    u16 idx;

    idx = VarGet(VAR_0x4037);
    if (idx < 9 || idx > 16)
    {
        idx = 9;
    }
    idx -= 9;
    *x = sTerraCaveLocationCoords[idx].x;
    *y = sTerraCaveLocationCoords[idx].y;
}

static bool32 RegionMap_IsPlayerInCave(u8 mapSecId)
{
    u32 i;

    for (i = 0; i < 1; i++)
    {
        if (sRegionMap_MapSecAquaHideoutOld[i] == mapSecId)
        {
            return TRUE;
        }
    }
    return FALSE;
}

u16 CorrectSpecialMapSecId(u16 mapSecId)
{
    return CorrectSpecialMapSecId_Internal(mapSecId);
}

static void RegionMap_GetPositionOfCursorWithinMapSection(void)
{
    u16 x;
    u16 y;
    u16 posWithinMapSec;

    if (gRegionMap->primaryMapSecId == MAPSEC_NONE)
    {
        gRegionMap->posWithinMapSec = 0;
        return;
    }
    x = gRegionMap->cursorPosX;
    y = gRegionMap->cursorPosY;
    posWithinMapSec = 0;
    while (1)
    {
        if (x <= 0)
        {
            if (RegionMap_IsMapSecIdInNextRow(y))
            {
                y--;
                x = MAP_WIDTH;
            }
            else
            {
                break;
            }
        }
        else
        {
            x--;
            if (GetRegionMapSectionIdAt_Internal(x, y, gRegionMap->currentRegion, FALSE) == gRegionMap->primaryMapSecId)
            {
                posWithinMapSec++;
            }
        }
    }
    gRegionMap->posWithinMapSec = posWithinMapSec;
}

static bool8 RegionMap_IsMapSecIdInNextRow(u16 y)
{
    u16 x;

    if (y-- == 0)
    {
        return FALSE;
    }
    for (x = 0; x < MAP_WIDTH; x++)
    {
        if (GetRegionMapSectionIdAt_Internal(x, y, gRegionMap->currentRegion, FALSE) == gRegionMap->primaryMapSecId)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static void SpriteCallback_CursorFull(struct Sprite *sprite)
{
    if (gRegionMap->cursorMovementFrameCounter != 0)
    {
        sprite->pos1.x += 2 * gRegionMap->cursorDeltaX;
        sprite->pos1.y += 2 * gRegionMap->cursorDeltaY;
        gRegionMap->cursorMovementFrameCounter--;
    }
}

void CreateRegionMapCursor(u16 tileTag, u16 paletteTag, bool8 visible)
{
    u8 spriteId;
    struct Sprite *sprite;
    struct SpriteTemplate template;
    struct SpritePalette palette;
    struct SpriteSheet sheet;

    palette = sRegionMapCursorSpritePalette;
    template = sRegionMapCursorSpriteTemplate;
    sheet.tag = tileTag;
    template.tileTag = tileTag;
    gRegionMap->cursorTileTag = tileTag;
    palette.tag = paletteTag;
    template.paletteTag = paletteTag;
    gRegionMap->cursorPaletteTag = paletteTag;
    sheet.data = gRegionMap->cursorImage;
    sheet.size = sizeof(gRegionMap->cursorImage);
    LoadSpriteSheet(&sheet);
    LoadSpritePalette(&palette);
    spriteId = CreateSprite(&template, 0x38, 0x48, 0);
    if (spriteId != MAX_SPRITES)
    {
        gRegionMap->spriteIds[0] = spriteId;
        sprite = &gSprites[spriteId];
        sprite->oam.size = 1;

        if (visible)
        {
            sprite->pos1.x = (gRegionMap->cursorPosX + gRegionMap->xOffset + MAPCURSOR_X_MIN) * 8 + 4;
            sprite->pos1.y = (gRegionMap->cursorPosY + MAPCURSOR_Y_MIN) * 8 + 4;
        }
        else
        {
            sprite->invisible = TRUE;
            sprite->callback = SpriteCallbackDummy;
        }

        sprite->data[1] = 2;
        sprite->data[2] = (IndexOfSpritePaletteTag(paletteTag) << 4) + 0x101;
        sprite->data[3] = TRUE;
    }
}

void ShowRegionMapCursorSprite(void)
{
    if (gRegionMap->spriteIds[0] != 0xFF)
    {
        struct Sprite *sprite = &gSprites[gRegionMap->spriteIds[0]];

        sprite->pos1.x = (gRegionMap->cursorPosX + gRegionMap->xOffset + MAPCURSOR_X_MIN) * 8 + 4;
        sprite->pos1.y = (gRegionMap->cursorPosY + MAPCURSOR_Y_MIN) * 8 + 4;
        sprite->callback = SpriteCallback_CursorFull;
        StartSpriteAnim(sprite, 0);
        sprite->invisible = FALSE;
    }
}

void HideRegionMapCursorSprite(void)
{
    if (gRegionMap->spriteIds[0] != 0xFF)
    {
        struct Sprite *sprite = &gSprites[gRegionMap->spriteIds[0]];

        gRegionMap->cursorPosX = gRegionMap->playerIconSpritePosX;
        gRegionMap->cursorPosY = gRegionMap->playerIconSpritePosY;
        LoadMapLayersFromPosition(gRegionMap->cursorPosX, gRegionMap->cursorPosY);

        sprite->invisible = TRUE;
        sprite->callback = SpriteCallbackDummy;
    }
}

void sub_8124268(void)
{
    gSprites[gRegionMap->spriteIds[0]].data[3] = TRUE;
}

void sub_8124278(void)
{
    gSprites[gRegionMap->spriteIds[0]].data[3] = FALSE;
}

void CreateRegionMapPlayerIcon(u16 tileTag, u16 paletteTag)
{
    struct Sprite *sprite;
    struct SpriteSheet sheet = {sRegionMapPlayerIcon_GoldGfx, 0x80, tileTag};
    struct SpritePalette palette = {sRegionMapPlayerIcon_GoldPal, paletteTag};
    struct SpriteTemplate template = {tileTag, paletteTag, &sRegionMapPlayerIconOam, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy};

    if (sub_8124668(gMapHeader.regionMapSectionId))
    {
        gRegionMap->spriteIds[1] = 0xFF;
        return;
    }
    if (gSaveBlock2Ptr->playerGender == FEMALE)
    {
        sheet.data = sRegionMapPlayerIcon_KrisGfx;
        palette.data = sRegionMapPlayerIcon_KrisPal;
    }
    LoadSpriteSheet(&sheet);
    LoadSpritePalette(&palette);
    gRegionMap->spriteIds[1] = CreateSprite(&template, 0, 0, 1);
    sprite = &gSprites[gRegionMap->spriteIds[1]];
    sprite->pos1.x = (gRegionMap->playerIconSpritePosX + gRegionMap->xOffset + MAPCURSOR_X_MIN) * 8 + 4;
    sprite->pos1.y = (gRegionMap->playerIconSpritePosY + MAPCURSOR_Y_MIN) * 8 + 4;
    //sprite->callback = RegionMapPlayerIconSpriteCallback;
}

static void HideRegionMapPlayerIcon(void)
{
    if (gRegionMap->spriteIds[1] != 0xFF)
    {
        struct Sprite *sprite = &gSprites[gRegionMap->spriteIds[1]];

        sprite->invisible = TRUE;
        sprite->callback = SpriteCallbackDummy;
    }
}

static void UnhideRegionMapPlayerIcon(void)
{
    if (gRegionMap->spriteIds[1] != 0xFF)
    {
        struct Sprite *sprite = &gSprites[gRegionMap->spriteIds[1]];

        sprite->pos1.x = (gRegionMap->playerIconSpritePosX + gRegionMap->xOffset + MAPCURSOR_X_MIN) * 8 + 4;
        sprite->pos1.y = (gRegionMap->playerIconSpritePosY + MAPCURSOR_Y_MIN) * 8 + 4;
        sprite->pos2.x = 0;
        sprite->pos2.y = 0;
        //sprite->callback = RegionMapPlayerIconSpriteCallback;
        sprite->invisible = FALSE;
    }
}

static void RegionMapPlayerIconSpriteCallback(struct Sprite *sprite)
{
    if (gRegionMap->blinkPlayerIcon)
    {
        if (++sprite->data[7] > 16)
        {
            sprite->data[7] = 0;
            sprite->invisible = sprite->invisible ? FALSE : TRUE;
        }
    }
    else
    {
        sprite->invisible = FALSE;
    }
}

void sub_812454C(void)
{
    if (gRegionMap->playerIsInCave)
    {
        gRegionMap->blinkPlayerIcon = TRUE;
    }
}

void CreateRegionMapName(u16 tileTagCurve, u16 tileTagMain, u16 paletteTag)
{
    u8 nameToDisplay;

    struct SpriteTemplate template;
    struct SpritePalette palette;
    struct SpriteSheet curveSheet = {sRegionMapNamesCurve_Gfx, sizeof(sRegionMapNamesCurve_Gfx), tileTagCurve};
    struct SpriteSheet mainSheet = {sRegionMapNames_Gfx, sizeof(sRegionMapNames_Gfx), tileTagMain};

    template = sRegionMapNameCurveSpriteTemplate;
    template.tileTag = tileTagCurve;
    template.paletteTag = paletteTag;
    palette = gSpritePalette_PokegearMenuSprites;
    palette.tag = paletteTag;
    LoadSpriteSheet(&curveSheet);
    LoadSpritePalette(&palette);
    gRegionMap->spriteIds[2] = CreateSprite(&template, 180 + gRegionMap->xOffset * 8, 156, 0);
    gRegionMap->regionNameCurveTileTag = tileTagCurve;
    gRegionMap->regionNamePaletteTag = paletteTag;
    
    template = sRegionMapNameSpriteTemplate;
    template.tileTag = tileTagMain;
    template.paletteTag = paletteTag;
    LoadSpriteSheet(&mainSheet);
    gRegionMap->spriteIds[3] = CreateSprite(&template, 200 + gRegionMap->xOffset * 8, 156, 0);
    gRegionMap->regionNameMainTileTag = tileTagMain;

    if (gRegionMap->currentRegion >= REGION_SEVII1)
    {
        nameToDisplay = REGION_SEVII1;
    }
    else
    {
        nameToDisplay = gRegionMap->currentRegion;
    }

    StartSpriteAnim(&gSprites[gRegionMap->spriteIds[3]], gRegionMap->currentRegion);
}

void CreateSecondaryLayerDots(u16 tileTag, u16 paletteTag)
{
    u8 i = 0;
    u16 x, y;

    struct SpriteSheet sheet = {sRegionMapDots_Gfx, sizeof(sRegionMapDots_Gfx), tileTag};
    struct SpritePalette palette = {sRegionMapDots_Pal, paletteTag};
    struct SpriteTemplate template = {tileTag, paletteTag, &sRegionMapDotsOam, sRegionMapDotsAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy};

    LoadSpriteSheet(&sheet);
    LoadSpritePalette(&palette);
    gRegionMap->dotsTileTag = tileTag;
    gRegionMap->dotsPaletteTag = paletteTag;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            u8 secondaryMapSec = GetRegionMapSectionIdAt_Internal(x, y, gRegionMap->currentRegion, TRUE);
            
            if (secondaryMapSec != MAPSEC_NONE)
            {
                u8 spriteId;

                if ((gRegionMapEntries[secondaryMapSec].width > 1 || gRegionMapEntries[secondaryMapSec].height > 1) && (x == gRegionMapEntries[secondaryMapSec].x && y == gRegionMapEntries[secondaryMapSec].y))
                {
                    x = (gRegionMapEntries[secondaryMapSec].width * 8) / 2 + (gRegionMapEntries[secondaryMapSec].x + MAPCURSOR_X_MIN + gRegionMap->xOffset) * 8;
                    y = (gRegionMapEntries[secondaryMapSec].height * 8) / 2 + (gRegionMapEntries[secondaryMapSec].y + MAPCURSOR_Y_MIN) * 8;
                    spriteId = CreateSprite(&template, x, y, 3);
                }
                else
                {
                    u8 offset = 0;

                    if (get_flagnr_blue_points(GetRegionMapSectionIdAt_Internal(x, y, gRegionMap->currentRegion, FALSE)) >= MAPSECTYPE_CITY_CANFLY)
                    {
                        offset = 2;
                    }

                    spriteId = CreateSprite(&template, (x + MAPCURSOR_X_MIN + gRegionMap->xOffset) * 8 + offset + 4, (y + MAPCURSOR_Y_MIN) * 8 + offset + 4, 3);
                }

                if (get_flagnr_blue_points(secondaryMapSec) == MAPSECTYPE_CITY_CANFLY)
                {
                    StartSpriteAnim(&gSprites[spriteId], 1);
                }

                gRegionMap->spriteIds[i++ + 4] = spriteId;
                
                if (i + 4 > sizeof(gRegionMap->spriteIds))
                {
                    return;
                }
            }
        }
    }
}

u8 *GetMapName(u8 *dest, u16 regionMapId, u16 padLength)
{
    u8 *str;
    u16 i;

    if (regionMapId == MAPSEC_SECRET_BASE)
    {
        str = GetSecretBaseMapName(dest);
    }
    else if (regionMapId < MAPSEC_NONE)
    {
        str = StringCopy(dest, gRegionMapEntries[regionMapId].name);
    }
    else
    {
        if (padLength == 0)
        {
            padLength = 18;
        }
        return StringFill(dest, CHAR_SPACE, padLength);
    }
    if (padLength != 0)
    {
        for (i = str - dest; i < padLength; i++)
        {
            *str++ = CHAR_SPACE;
        }
        *str = EOS;
    }
    return str;
}

u8 *sub_81245DC(u8 *dest, u16 mapSecId)
{
    switch (mapSecId)
    {
        case MAPSEC_DYNAMIC:
            return StringCopy(dest, gText_Ferry);
        case MAPSEC_SECRET_BASE:
            return StringCopy(dest, gText_SecretBase);
        default:
            return GetMapName(dest, mapSecId, 0);
    }
}

u8 *sub_8124610(u8 *dest, u16 mapSecId)
{
    if (mapSecId == MAPSEC_AQUA_HIDEOUT_OLD)
    {
        return StringCopy(dest, gText_Hideout);
    }
    else
    {
        return sub_81245DC(dest, mapSecId);
    }
}

void sub_8124630(u16 mapSecId, u16 *x, u16 *y, u16 *width, u16 *height)
{
    *x = gRegionMapEntries[mapSecId].x;
    *y = gRegionMapEntries[mapSecId].y;
    *width = gRegionMapEntries[mapSecId].width;
    *height = gRegionMapEntries[mapSecId].height;
}

bool8 sub_8124658(void)
{
    return FALSE;
}

bool32 sub_8124668(u8 mapSecId)
{
    u32 i;

    for (i = 0; i < 3; i++)
    {
        if (mapSecId == sRegionMapEventSectionIds[i])
        {
            return TRUE;
        }
    }
    return FALSE;
}

void MCB2_FlyMap(void)
{
    switch (gMain.state)
    {
        case 0:
            SetVBlankCallback(NULL);
            SetGpuReg(REG_OFFSET_DISPCNT, 0);
            SetGpuReg(REG_OFFSET_BG0HOFS, 0);
            SetGpuReg(REG_OFFSET_BG0VOFS, 0);
            SetGpuReg(REG_OFFSET_BG1HOFS, 0);
            SetGpuReg(REG_OFFSET_BG1VOFS, 0);
            SetGpuReg(REG_OFFSET_BG2VOFS, 0);
            SetGpuReg(REG_OFFSET_BG2HOFS, 0);
            SetGpuReg(REG_OFFSET_BG3HOFS, 0);
            SetGpuReg(REG_OFFSET_BG3VOFS, 0);
            sFlyMap = malloc(sizeof(*sFlyMap));
            if (sFlyMap == NULL)
            {
                SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
            }
            else
            {
                ResetPaletteFade();
                ResetSpriteData();
                FreeSpriteTileRanges();
                FreeAllSpritePalettes();
                gMain.state++;
            }
            break;
        case 1:
            ResetBgsAndClearDma3BusyFlags(0);
            InitBgsFromTemplates(0, gUnknown_085A1EE4, 3);
            gMain.state++;
            break;
        case 2:
            InitWindows(gUnknown_085A1EF0);
            DeactivateAllTextPrinters();
            gMain.state++;
            break;
        case 3:
            LoadUserWindowBorderGfx(0, 0x65, 0xd0);
            clear_scheduled_bg_copies_to_vram();
            gMain.state++;
            break;
        case 4:
            InitRegionMap(&sFlyMap->regionMap, FALSE);
            CreateRegionMapCursor(0, 0, TRUE);
            CreateRegionMapPlayerIcon(1, 1);
            sFlyMap->mapSecId = sFlyMap->regionMap.primaryMapSecId;
            StringFill(sFlyMap->unk_a4c, CHAR_SPACE, 16);
            gUnknown_03001180 = TRUE;
            sub_8124904();
            gMain.state++;
            break;
        case 5:
            LZ77UnCompVram(sRegionMapFrameGfxLZ, (u16 *)BG_CHAR_ADDR(3));
            gMain.state++;
            break;
        case 6:
            LZ77UnCompVram(sRegionMapFrameTilemapLZ, (u16 *)BG_SCREEN_ADDR(30));
            gMain.state++;
            break;
        case 7:
            LoadPalette(sRegionMapFramePal, 0x10, 0x20);
            PutWindowTilemap(2);
            FillWindowPixelBuffer(2, 0x00);
            PrintTextOnWindow(2, 1, gText_FlyToWhere, 0, 1, 0, NULL);
            schedule_bg_copy_tilemap_to_vram(0);
            gMain.state++;
            break;
        case 8:
            sub_8124A70();
            gMain.state++;
            break;
        case 9:
            BlendPalettes(-1, 16, 0);
            SetVBlankCallback(sub_81248C0);
            gMain.state++;
            break;
        case 10:
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
            ShowBg(0);
            ShowBg(1);
            ShowBg(2);
            sub_81248F4(sub_8124D14);
            SetMainCallback2(sub_81248D4);
            gMain.state++;
            break;
    }
}

static void sub_81248C0(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void sub_81248D4(void)
{
    sFlyMap->unk_000();
    AnimateSprites();
    BuildOamBuffer();
    do_scheduled_bg_tilemap_copies_to_vram();
}

static void sub_81248F4(void callback(void))
{
    sFlyMap->unk_000 = callback;
    sFlyMap->unk_004 = 0;
}

static void sub_8124904(void)
{
    u16 i;
    bool32 flag;
    const u8 *name;

    if (sFlyMap->regionMap.primaryMapSecStatus > MAPSECTYPE_NONE && sFlyMap->regionMap.primaryMapSecStatus <= MAPSECTYPE_BATTLE_FRONTIER)
    {
        flag = FALSE;
        for (i = 0; i < 1; i++)
        {
            if (sFlyMap->regionMap.primaryMapSecId == gUnknown_085A1EDC[i].mapSecId)
            {
                if (FlagGet(gUnknown_085A1EDC[i].flag))
                {
                    StringLength(gUnknown_085A1EDC[i].name[sFlyMap->regionMap.posWithinMapSec]);
                    flag = TRUE;
                    sub_8198070(0, FALSE);
                    SetWindowBorderStyle(1, FALSE, 0x65, 0x0d);
                    PrintTextOnWindow(1, 1, sFlyMap->regionMap.primaryMapSecName, 0, 1, 0, NULL);
                    name = gUnknown_085A1EDC[i].name[sFlyMap->regionMap.posWithinMapSec];
                    PrintTextOnWindow(1, 1, name, GetStringRightAlignXOffset(1, name, 0x60), 0x11, 0, NULL);
                    schedule_bg_copy_tilemap_to_vram(0);
                    gUnknown_03001180 = TRUE;
                }
                break;
            }
        }
        if (!flag)
        {
            if (gUnknown_03001180 == TRUE)
            {
                sub_8198070(1, FALSE);
                SetWindowBorderStyle(0, FALSE, 0x65, 0x0d);
            }
            else
            {
                FillWindowPixelBuffer(0, 0x11);
            }
            PrintTextOnWindow(0, 1, sFlyMap->regionMap.primaryMapSecName, 0, 1, 0, NULL);
            schedule_bg_copy_tilemap_to_vram(0);
            gUnknown_03001180 = FALSE;
        }
    }
    else
    {
        if (gUnknown_03001180 == TRUE)
        {
            sub_8198070(1, FALSE);
            SetWindowBorderStyle(0, FALSE, 0x65, 0x0d);
        }
        FillWindowPixelBuffer(0, 0x11);
        CopyWindowToVram(0, 2);
        schedule_bg_copy_tilemap_to_vram(0);
        gUnknown_03001180 = FALSE;
    }
}


static void sub_8124A70(void)
{
    struct SpriteSheet sheet;

    LZ77UnCompWram(sUnknown_085A1D68, sFlyMap->unk_88c);
    sheet.data = sFlyMap->unk_88c;
    sheet.size = 0x1c0;
    sheet.tag = 2;
    LoadSpriteSheet(&sheet);
    LoadSpritePalette(&gUnknown_085A1F10);
    sub_8124AD4();
    sub_8124BE4();
}

static void sub_8124AD4(void)
{
    u16 canFlyFlag;
    u16 i;
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 shape;
    u8 spriteId;

    canFlyFlag = FLAG_VISITED_LITTLEROOT_TOWN;
    for (i = 0; i < 16; i++)
    {
        sub_8124630(i, &x, &y, &width, &height);
        x = (x + MAPCURSOR_X_MIN) * 8 + 4;
        y = (y + MAPCURSOR_Y_MIN) * 8 + 4;
        if (width == 2)
        {
            shape = ST_OAM_H_RECTANGLE;
        }
        else if (height == 2)
        {
            shape = ST_OAM_V_RECTANGLE;
        }
        else
        {
            shape = ST_OAM_SQUARE;
        }
        spriteId = CreateSprite(&gUnknown_085A1F7C, x, y, 10);
        if (spriteId != MAX_SPRITES)
        {
            gSprites[spriteId].oam.shape = shape;
            if (FlagGet(canFlyFlag))
            {
                gSprites[spriteId].callback = sub_8124CBC;
            }
            else
            {
                shape += 3;
            }
            StartSpriteAnim(&gSprites[spriteId], shape);
            gSprites[spriteId].data[0] = i;
        }
        canFlyFlag++;
    }
}

static void sub_8124BE4(void)
{
    u16 i;
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 mapSecId;
    u8 spriteId;

    for (i = 0; sUnknown_085A1F18[i][1] != MAPSEC_NONE; i++)
    {
        if (FlagGet(sUnknown_085A1F18[i][0]))
        {
            mapSecId = sUnknown_085A1F18[i][1];
            sub_8124630(mapSecId, &x, &y, &width, &height);
            x = (x + MAPCURSOR_X_MIN) * 8;
            y = (y + MAPCURSOR_Y_MIN) * 8;
            spriteId = CreateSprite(&gUnknown_085A1F7C, x, y, 10);
            if (spriteId != MAX_SPRITES)
            {
                gSprites[spriteId].oam.size = 1;
                gSprites[spriteId].callback = sub_8124CBC;
                StartSpriteAnim(&gSprites[spriteId], 6);
                gSprites[spriteId].data[0] = mapSecId;
            }
        }
    }
}

static void sub_8124CBC(struct Sprite *sprite)
{
    if (sFlyMap->regionMap.primaryMapSecId == sprite->data[0])
    {
        if (++sprite->data[1] > 16)
        {
            sprite->data[1] = 0;
            sprite->invisible = sprite->invisible ? FALSE : TRUE;
        }
    }
    else
    {
        sprite->data[1] = 16;
        sprite->invisible = FALSE;
    }
}

static void sub_8124D14(void)
{
    switch (sFlyMap->unk_004)
    {
        case 0:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0);
            sFlyMap->unk_004++;
            break;
        case 1:
            if (!UpdatePaletteFade())
            {
                sub_81248F4(sub_8124D64);
            }
            break;
    }
}

static void sub_8124D64(void)
{
    if (sFlyMap->unk_004 == 0)
    {
        switch (sub_81230AC())
        {
            case INPUT_EVENT_NONE:
            case INPUT_EVENT_MOVE_START:
            case INPUT_EVENT_MOVE_CONT:
                break;
            case INPUT_EVENT_MOVE_END:
                sub_8124904();
                break;
            case INPUT_EVENT_A_BUTTON:
                if (sFlyMap->regionMap.primaryMapSecStatus == MAPSECTYPE_CITY_CANFLY || sFlyMap->regionMap.primaryMapSecStatus == MAPSECTYPE_BATTLE_FRONTIER)
                {
                    m4aSongNumStart(SE_SELECT);
                    sFlyMap->unk_a72 = TRUE;
                    sub_81248F4(sub_8124E0C);
                }
                break;
            case INPUT_EVENT_B_BUTTON:
                m4aSongNumStart(SE_SELECT);
                sFlyMap->unk_a72 = FALSE;
                sub_81248F4(sub_8124E0C);
                break;
        }
    }
}

static void sub_8124E0C(void)
{
    switch (sFlyMap->unk_004)
    {
        case 0:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
            sFlyMap->unk_004++;
            break;
        case 1:
            if (!UpdatePaletteFade())
            {
                FreeRegionMapIconResources();
                if (sFlyMap->unk_a72)
                {
                    switch (sFlyMap->regionMap.primaryMapSecId)
                    {
                        case MAPSEC_SOUTHERN_ISLAND:
                            sub_8084CCC(HEAL_LOCATION_SOUTHERN_ISLAND_EXTERIOR);
                            break;
                        case MAPSEC_BATTLE_FRONTIER:
                            sub_8084CCC(HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST);
                            break;
                        case MAPSEC_LITTLEROOT_TOWN:
                            sub_8084CCC(gSaveBlock2Ptr->playerGender == MALE ? HEAL_LOCATION_LITTLEROOT_TOWN_1 : HEAL_LOCATION_LITTLEROOT_TOWN_2);
                            break;
                        case MAPSEC_EVER_GRANDE_CITY:
                            sub_8084CCC(FlagGet(FLAG_LANDMARK_POKEMON_LEAGUE) && sFlyMap->regionMap.posWithinMapSec == 0 ? HEAL_LOCATION_EVER_GRANDE_CITY_2 : HEAL_LOCATION_EVER_GRANDE_CITY_1);
                            break;
                        default:
                            if (sMapHealLocations[sFlyMap->regionMap.primaryMapSecId][2] != 0)
                            {
                                sub_8084CCC(sMapHealLocations[sFlyMap->regionMap.primaryMapSecId][2]);
                            }
                            else
                            {
                                warp1_set_2(sMapHealLocations[sFlyMap->regionMap.primaryMapSecId][0], sMapHealLocations[sFlyMap->regionMap.primaryMapSecId][1], -1);
                            }
                            break;
                    }
                    sub_80B69DC();
                }
                else
                {
                    SetMainCallback2(sub_81B58A8);
                }
                if (sFlyMap != NULL)
                {
                    free(sFlyMap);
                    sFlyMap = NULL;
                }
                FreeAllWindowBuffers();
            }
            break;
    }
}

u8 GetCurrentRegion(void)
{
    return sMapSecToRegion[gMapHeader.regionMapSectionId];
}
