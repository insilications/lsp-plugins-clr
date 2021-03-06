/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 06 окт. 2015 г.
 *
 * lsp-plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins. If not, see <https://www.gnu.org/licenses/>.
 */

// Define capabilities
#ifndef MOD_PLUGIN
    #define MOD_PLUGIN(plugin, ui)
#endif /* MOD_PLUGIN */

// Specify modules

// Phase detector
MOD_PLUGIN(phase_detector, plugin_ui)

// Delay compensator
MOD_PLUGIN(comp_delay_mono, plugin_ui)
MOD_PLUGIN(comp_delay_stereo, plugin_ui)
MOD_PLUGIN(comp_delay_x2_stereo, plugin_ui)

// Spectrum Analyzer
MOD_PLUGIN(spectrum_analyzer_x1, plugin_ui)
MOD_PLUGIN(spectrum_analyzer_x2, plugin_ui)
MOD_PLUGIN(spectrum_analyzer_x4, plugin_ui)
MOD_PLUGIN(spectrum_analyzer_x8, plugin_ui)
MOD_PLUGIN(spectrum_analyzer_x12, plugin_ui)
MOD_PLUGIN(spectrum_analyzer_x16, plugin_ui)

// Sampler
MOD_PLUGIN(sampler_mono, plugin_ui)
MOD_PLUGIN(sampler_stereo, plugin_ui)
MOD_PLUGIN(multisampler_x12, multisampler_ui)
MOD_PLUGIN(multisampler_x12_do, multisampler_ui)
MOD_PLUGIN(multisampler_x24, multisampler_ui)
MOD_PLUGIN(multisampler_x24_do, multisampler_ui)
MOD_PLUGIN(multisampler_x48, multisampler_ui)
MOD_PLUGIN(multisampler_x48_do, multisampler_ui)

// Trigger
MOD_PLUGIN(trigger_mono, plugin_ui)
MOD_PLUGIN(trigger_stereo, plugin_ui)
MOD_PLUGIN(trigger_midi_mono, plugin_ui)
MOD_PLUGIN(trigger_midi_stereo, plugin_ui)

// Parametric Equalizer
MOD_PLUGIN(para_equalizer_x16_mono, para_equalizer_ui)
MOD_PLUGIN(para_equalizer_x32_mono, para_equalizer_ui)
MOD_PLUGIN(para_equalizer_x16_stereo, para_equalizer_ui)
MOD_PLUGIN(para_equalizer_x32_stereo, para_equalizer_ui)
MOD_PLUGIN(para_equalizer_x16_lr, para_equalizer_ui)
MOD_PLUGIN(para_equalizer_x32_lr, para_equalizer_ui)
MOD_PLUGIN(para_equalizer_x16_ms, para_equalizer_ui)
MOD_PLUGIN(para_equalizer_x32_ms, para_equalizer_ui)

// Graphic Equalizer
MOD_PLUGIN(graph_equalizer_x16_mono, plugin_ui)
MOD_PLUGIN(graph_equalizer_x16_stereo, plugin_ui)
MOD_PLUGIN(graph_equalizer_x16_lr, plugin_ui)
MOD_PLUGIN(graph_equalizer_x16_ms, plugin_ui)
MOD_PLUGIN(graph_equalizer_x32_mono, plugin_ui)
MOD_PLUGIN(graph_equalizer_x32_stereo, plugin_ui)
MOD_PLUGIN(graph_equalizer_x32_lr, plugin_ui)
MOD_PLUGIN(graph_equalizer_x32_ms, plugin_ui)

// Compressor
MOD_PLUGIN(compressor_mono, plugin_ui)
MOD_PLUGIN(compressor_stereo, plugin_ui)
MOD_PLUGIN(compressor_lr, plugin_ui)
MOD_PLUGIN(compressor_ms, plugin_ui)
MOD_PLUGIN(sc_compressor_mono, plugin_ui)
MOD_PLUGIN(sc_compressor_stereo, plugin_ui)
MOD_PLUGIN(sc_compressor_lr, plugin_ui)
MOD_PLUGIN(sc_compressor_ms, plugin_ui)

// Dynamic processor
MOD_PLUGIN(dyna_processor_mono, plugin_ui)
MOD_PLUGIN(dyna_processor_stereo, plugin_ui)
MOD_PLUGIN(dyna_processor_lr, plugin_ui)
MOD_PLUGIN(dyna_processor_ms, plugin_ui)
MOD_PLUGIN(sc_dyna_processor_mono, plugin_ui)
MOD_PLUGIN(sc_dyna_processor_stereo, plugin_ui)
MOD_PLUGIN(sc_dyna_processor_lr, plugin_ui)
MOD_PLUGIN(sc_dyna_processor_ms, plugin_ui)

// Expander
MOD_PLUGIN(expander_mono, plugin_ui)
MOD_PLUGIN(expander_stereo, plugin_ui)
MOD_PLUGIN(expander_lr, plugin_ui)
MOD_PLUGIN(expander_ms, plugin_ui)
MOD_PLUGIN(sc_expander_mono, plugin_ui)
MOD_PLUGIN(sc_expander_stereo, plugin_ui)
MOD_PLUGIN(sc_expander_lr, plugin_ui)
MOD_PLUGIN(sc_expander_ms, plugin_ui)

// Gate
MOD_PLUGIN(gate_mono, plugin_ui)
MOD_PLUGIN(gate_stereo, plugin_ui)
MOD_PLUGIN(gate_lr, plugin_ui)
MOD_PLUGIN(gate_ms, plugin_ui)
MOD_PLUGIN(sc_gate_mono, plugin_ui)
MOD_PLUGIN(sc_gate_stereo, plugin_ui)
MOD_PLUGIN(sc_gate_lr, plugin_ui)
MOD_PLUGIN(sc_gate_ms, plugin_ui)

// Limiter
MOD_PLUGIN(limiter_mono, plugin_ui)
MOD_PLUGIN(limiter_stereo, plugin_ui)
MOD_PLUGIN(sc_limiter_mono, plugin_ui)
MOD_PLUGIN(sc_limiter_stereo, plugin_ui)

// Impulse responses
MOD_PLUGIN(impulse_responses_mono, plugin_ui)
MOD_PLUGIN(impulse_responses_stereo, plugin_ui)

// Impulse reverb
MOD_PLUGIN(impulse_reverb_mono, plugin_ui)
MOD_PLUGIN(impulse_reverb_stereo, plugin_ui)

// Slap delay
MOD_PLUGIN(slap_delay_mono, plugin_ui)
MOD_PLUGIN(slap_delay_stereo, plugin_ui)

// Oscillator
MOD_PLUGIN(oscillator_mono, plugin_ui)

// Latency Meter
MOD_PLUGIN(latency_meter, plugin_ui)

// Multiband compressors
MOD_PLUGIN(mb_compressor_mono, plugin_ui)
MOD_PLUGIN(mb_compressor_stereo, plugin_ui)
MOD_PLUGIN(mb_compressor_lr, plugin_ui)
MOD_PLUGIN(mb_compressor_ms, plugin_ui)
MOD_PLUGIN(sc_mb_compressor_mono, plugin_ui)
MOD_PLUGIN(sc_mb_compressor_stereo, plugin_ui)
MOD_PLUGIN(sc_mb_compressor_lr, plugin_ui)
MOD_PLUGIN(sc_mb_compressor_ms, plugin_ui)

// Profiler
MOD_PLUGIN(profiler_mono, plugin_ui)
MOD_PLUGIN(profiler_stereo, plugin_ui)

// Room builder
MOD_PLUGIN(room_builder_mono, room_builder_ui)
MOD_PLUGIN(room_builder_stereo, room_builder_ui)

// Multiband expanders
MOD_PLUGIN(mb_expander_mono, plugin_ui)
MOD_PLUGIN(mb_expander_stereo, plugin_ui)
MOD_PLUGIN(mb_expander_lr, plugin_ui)
MOD_PLUGIN(mb_expander_ms, plugin_ui)
MOD_PLUGIN(sc_mb_expander_mono, plugin_ui)
MOD_PLUGIN(sc_mb_expander_stereo, plugin_ui)
MOD_PLUGIN(sc_mb_expander_lr, plugin_ui)
MOD_PLUGIN(sc_mb_expander_ms, plugin_ui)

// Multiband gates
MOD_PLUGIN(mb_gate_mono, plugin_ui)
MOD_PLUGIN(mb_gate_stereo, plugin_ui)
MOD_PLUGIN(mb_gate_lr, plugin_ui)
MOD_PLUGIN(mb_gate_ms, plugin_ui)
MOD_PLUGIN(sc_mb_gate_mono, plugin_ui)
MOD_PLUGIN(sc_mb_gate_stereo, plugin_ui)
MOD_PLUGIN(sc_mb_gate_lr, plugin_ui)
MOD_PLUGIN(sc_mb_gate_ms, plugin_ui)

// Oscilloscope
MOD_PLUGIN(oscilloscope_x1, plugin_ui)
MOD_PLUGIN(oscilloscope_x2, plugin_ui)
MOD_PLUGIN(oscilloscope_x4, plugin_ui)

// Loudness compensator
MOD_PLUGIN(loud_comp_mono, plugin_ui)
MOD_PLUGIN(loud_comp_stereo, plugin_ui)

// Surge filter
MOD_PLUGIN(surge_filter_mono, plugin_ui)
MOD_PLUGIN(surge_filter_stereo, plugin_ui)

// Crossover plugin
MOD_PLUGIN(crossover_mono, plugin_ui)
MOD_PLUGIN(crossover_stereo, plugin_ui)
MOD_PLUGIN(crossover_ms, plugin_ui)
MOD_PLUGIN(crossover_lr, plugin_ui)

// Artistic delay plugin
MOD_PLUGIN(art_delay_mono, plugin_ui)
MOD_PLUGIN(art_delay_stereo, plugin_ui)

#ifndef LSP_NO_EXPERIMENTAL
    // Nonlinear Convolver
    // MOD_PLUGIN(nonlinear_convolver_mono, plugin_ui)

    // Test plugin
    MOD_PLUGIN(test_plugin, test_plugin_ui)

    // Test plugin
    MOD_PLUGIN(filter_analyzer, plugin_ui)
#endif

// Undefine capabilities
#undef MOD_PLUGIN

