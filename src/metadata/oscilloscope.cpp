/*
 * oscilloscope.cpp
 *
 *  Created on: 26 Feb 2020
 *      Author: crocoduck
 */

#include <metadata/plugins.h>
#include <metadata/ports.h>
#include <metadata/developers.h>

namespace lsp
{
    static const int osclilloscope_classes[] = { C_UTILITY, -1};

    static const port_item_t ovs_mode[] =
    {
        {"None",        "oscilloscope.oversampler.none"},
        {"2X",          "oscilloscope.oversampler.2x"},
        {"3X",          "oscilloscope.oversampler.3x"},
        {"4X",          "oscilloscope.oversampler.4x"},
        {"6X",          "oscilloscope.oversampler.6x"},
        {"8X",          "oscilloscope.oversampler.8x"},
        {NULL,          NULL}
    };

    static const port_item_t osc_mode[] =
    {
        {"XY",          "oscilloscope.mode.xy"},
        {"Triggered",   "oscilloscope.mode.triggered"},
        {"Goniometer",  "oscilloscope.mode.goniometer"},
        {NULL,          NULL}
    };

    static const port_item_t osc_channels_x2[] =
    {
        {"1",           NULL },
        {"2",           NULL },
        {NULL,          NULL}
    };

    static const port_item_t osc_channels_x4[] =
    {
        {"1",           NULL },
        {"2",           NULL },
        {"3",           NULL },
        {"4",           NULL },
        {NULL,          NULL}
    };

    static const port_item_t sweep_type[] =
    {
        {"Sawtooth",    "oscilloscope.sweeptype.sawtooth"},
        {"Triangular",  "oscilloscope.sweeptype.triangular"},
        {"Sine",        "oscilloscope.sweeptype.sine"},
        {NULL,          NULL}
    };

    static const port_item_t osc_trg_input[] =
    {
        {"Y",    "oscilloscope.trigger.input.y"},
        {"EXT",  "oscilloscope.trigger.input.ext"},
        {NULL,      NULL}
    };

    static const port_item_t osc_trg_mode[] =
    {
        {"Single",  "oscilloscope.trigger.mode.single"},
        {"Manual",  "oscilloscope.trigger.mode.manual"},
        {"Repeat",  "oscilloscope.trigger.mode.repeat"},
        {NULL,      NULL}
    };

    static const port_item_t osc_trg_type[] =
    {
        {"None",                    "oscilloscope.trigger.type.none"},
        {"Simple Rising Edge",      "oscilloscope.trigger.type.simple_rising_edge"},
        {"Simple Falling Edge",     "oscilloscope.trigger.type.simple_falling_edge"},
        {"Advanced Rising Edge",    "oscilloscope.trigger.type.advanced_rising_edge"},
        {"Advanced Falling Edge",   "oscilloscope.trigger.type.advanced_falling_edge"},
        {NULL,                      NULL}
    };

    static const port_item_t osc_coupling[] =
    {
        {"AC",  "oscilloscope.coupling.ac"},
        {"DC",  "oscilloscope.coupling.dc"},
        {NULL,  NULL}
    };

    #define CHANNEL_AUDIO_PORTS(id, label) \
        AUDIO_INPUT("in_x" id, "Input x" label), \
        AUDIO_INPUT("in_y" id, "Input y" label), \
        AUDIO_INPUT("in_ext" id, "Input external" label), \
        AUDIO_OUTPUT("out_x" id, "Output x" label), \
        AUDIO_OUTPUT("out_y" id, "Output y" label)

    #define COMMON_CONTROLS \
        CONTROL("sh_sz", "Strobe History Size", U_NONE, oscilloscope_base_metadata::STROBE_HISTORY), \
        LOG_CONTROL("xyrt", "XY Record Time", U_MSEC, oscilloscope_base_metadata::XY_RECORD_TIME), \
        LOG_CONTROL("maxdots", "Maximum Dots for Plotting", U_NONE, oscilloscope_base_metadata::MAXDOTS), \
        SWITCH("freeze", "Global Freeze Switch", 0.0f)

    #define CHANNEL_SELECTOR(osc_channels) \
        COMBO("osc_cs", "Oscilloscope Channel Selector", 0, osc_channels)

    #define CHANNEL_SWITCHES(id, label) \
        SWITCH("glsw" id, "Global Switch" label, 0.0f), \
        SWITCH("frz" id, "Freeze Switch" label, 0.0f), \
        SWITCH("chsl" id, "Solo Switch" label, 0.0f), \
        SWITCH("chmt" id, "Mute Switch" label, 0.0f)

    #define OP_CONTROLS(id, label) \
        COMBO("ovmo" id, "Oversampler Mode" label, oscilloscope_base_metadata::OSC_OVS_DFL, ovs_mode), \
        COMBO("scmo" id, "Mode" label, oscilloscope_base_metadata::MODE_DFL, osc_mode)

    #define CP_CONTROLS(id, label) \
        COMBO("sccx" id, "Coupling X" label, oscilloscope_base_metadata::COUPLING_DFL, osc_coupling), \
        COMBO("sccy" id, "Coupling Y" label, oscilloscope_base_metadata::COUPLING_DFL, osc_coupling), \
        COMBO("scce" id, "Coupling EXT" label, oscilloscope_base_metadata::COUPLING_DFL, osc_coupling)

    #define HOR_CONTROLS(id, label) \
        COMBO("swtp" id, "Sweep Type" label, oscilloscope_base_metadata::SWEEP_TYPE_DFL, sweep_type), \
        LOG_CONTROL("tmdv" id, "Time Division" label, U_MSEC, oscilloscope_base_metadata::TIME_DIVISION), \
        LOG_CONTROL("hzdv" id, "Horizontal Division" label, U_NONE, oscilloscope_base_metadata::HORIZONTAL_DIVISION), \
        CONTROL("hzps" id, "Horizontal Position" label, U_PERCENT, oscilloscope_base_metadata::TIME_POSITION)

    #define VER_CONTROLS(id, label) \
        LOG_CONTROL("vedv" id, "Vertical Division" label, U_NONE, oscilloscope_base_metadata::VERTICAL_DIVISION), \
        CONTROL("veps" id, "Vertical Position" label, U_PERCENT, oscilloscope_base_metadata::VERTICAL_POSITION)

    #define TRG_CONTROLS(id, label) \
        CONTROL("trhy" id, "Trigger Hysteresis" label, U_PERCENT, oscilloscope_base_metadata::TRIGGER_HYSTERESIS), \
        CONTROL("trlv" id, "Trigger Level" label, U_PERCENT, oscilloscope_base_metadata::TRIGGER_LEVEL), \
        LOG_CONTROL("trho" id, "Trigger Hold Time" label, U_SEC, oscilloscope_base_metadata::TRIGGER_HOLD_TIME), \
        COMBO("trmo" id, "Trigger Mode" label, oscilloscope_base_metadata::TRIGGER_MODE_DFL, osc_trg_mode), \
        COMBO("trtp" id, "Trigger Type" label, oscilloscope_base_metadata::TRIGGER_TYPE_DFL, osc_trg_type), \
        COMBO("trin" id, "Trigger Input" label, oscilloscope_base_metadata::TRIGGER_INPUT_DFL, osc_trg_input), \
        TRIGGER("trre" id, "Trigger Reset")

    #define CHANNEL_CONTROLS(id, label) \
        OP_CONTROLS(id, label), \
        CP_CONTROLS(id, label), \
        HOR_CONTROLS(id, label), \
        VER_CONTROLS(id, label), \
        TRG_CONTROLS(id, label)

    #define OSC_VISUALOUTS(id, label) \
        STREAM("oscv" id, "Stream buffer" label, 3, 128, 0x4000)

    static const port_t oscilloscope_x1_ports[] =
    {
        CHANNEL_AUDIO_PORTS("_1", " 1"),
        COMMON_CONTROLS,
        CHANNEL_CONTROLS("_1", " 1"),
        OSC_VISUALOUTS("_1", " 1"),
        PORTS_END
    };

    static const port_t oscilloscope_x2_ports[] =
    {
        CHANNEL_AUDIO_PORTS("_1", " 1"),
        CHANNEL_AUDIO_PORTS("_2", " 2"),

        COMMON_CONTROLS,
        CHANNEL_SELECTOR(osc_channels_x2),

        CHANNEL_CONTROLS("", " Global"),
        CHANNEL_CONTROLS("_1", " 1"),
        CHANNEL_CONTROLS("_2", " 2"),

        CHANNEL_SWITCHES("_1", " 1"),
        CHANNEL_SWITCHES("_2", " 2"),

        OSC_VISUALOUTS("_1", " 1"),
        OSC_VISUALOUTS("_2", " 2"),

        PORTS_END
    };

    static const port_t oscilloscope_x4_ports[] =
    {
        CHANNEL_AUDIO_PORTS("_1", " 1"),
        CHANNEL_AUDIO_PORTS("_2", " 2"),
        CHANNEL_AUDIO_PORTS("_3", " 3"),
        CHANNEL_AUDIO_PORTS("_4", " 4"),

        COMMON_CONTROLS,
        CHANNEL_SELECTOR(osc_channels_x4),

        CHANNEL_CONTROLS("", " Global"),
        CHANNEL_CONTROLS("_1", " 1"),
        CHANNEL_CONTROLS("_2", " 2"),
        CHANNEL_CONTROLS("_3", " 3"),
        CHANNEL_CONTROLS("_4", " 4"),

        CHANNEL_SWITCHES("_1", " 1"),
        CHANNEL_SWITCHES("_2", " 2"),
        CHANNEL_SWITCHES("_3", " 3"),
        CHANNEL_SWITCHES("_4", " 4"),

        OSC_VISUALOUTS("_1", " 1"),
        OSC_VISUALOUTS("_2", " 2"),
        OSC_VISUALOUTS("_3", " 3"),
        OSC_VISUALOUTS("_4", " 4"),

        PORTS_END
    };

    const plugin_metadata_t oscilloscope_x1_metadata::metadata =
    {
        "Oscilloscope x1",
        "Oscilloscope x1",
        "O1", // Oscilloscope x1
        &developers::s_tronci,
        "oscilloscope_x1",
        "qbla",
        LSP_OSCILLOSCOPE_BASE + 0,
        LSP_VERSION(1, 0, 0),
        osclilloscope_classes,
        E_INLINE_DISPLAY | E_DUMP_STATE,
        oscilloscope_x1_ports,
        "util/oscilloscope/x1.xml",
        NULL,
        NULL
    };

    const plugin_metadata_t oscilloscope_x2_metadata::metadata =
    {
        "Oscilloscope x2",
        "Oscilloscope x2",
        "O2", // Oscilloscope x2
        &developers::s_tronci,
        "oscilloscope_x2",
        "ubsb",
        LSP_OSCILLOSCOPE_BASE + 1,
        LSP_VERSION(1, 0, 0),
        osclilloscope_classes,
        E_INLINE_DISPLAY | E_DUMP_STATE,
        oscilloscope_x2_ports,
        "util/oscilloscope/x2.xml",
        NULL,
        NULL
    };

    const plugin_metadata_t oscilloscope_x4_metadata::metadata =
    {
        "Oscilloscope x4",
        "Oscilloscope x4",
        "O4", // Oscilloscope x4
        &developers::s_tronci,
        "oscilloscope_x4",
        "atvi",
        LSP_OSCILLOSCOPE_BASE + 2,
        LSP_VERSION(1, 0, 0),
        osclilloscope_classes,
        E_INLINE_DISPLAY | E_DUMP_STATE,
        oscilloscope_x4_ports,
        "util/oscilloscope/x4.xml",
        NULL,
        NULL
    };

}
