/*
 * native.cpp
 *
 *  Created on: 04 марта 2016 г.
 *      Author: sadko
 */

#include <core/types.h>
#include <core/dsp.h>
#include <core/bits.h>
#include <core/units.h>

#include <core/native/dsp.h>
#include <core/native/float.h>
#include <core/native/graphics.h>

namespace lsp
{
    namespace native
    {
        void dsp_init()
        {
            // Generic init
            dsp::start                      = native::start;
            dsp::finish                     = native::finish;

            dsp::copy                       = native::copy;
            dsp::copy_saturated             = native::copy_saturated;
            dsp::saturate                   = native::saturate;
            dsp::move                       = native::move;
            dsp::fill                       = native::fill;
            dsp::fill_one                   = native::fill_one;
            dsp::fill_zero                  = native::fill_zero;
            dsp::fill_minus_one             = native::fill_minus_one;
            dsp::abs                        = native::abs;
            dsp::abs_normalized             = native::abs_normalized;
            dsp::normalize                  = native::normalize;
            dsp::min                        = native::min;
            dsp::max                        = native::max;
            dsp::abs_max                    = native::abs_max;
            dsp::abs_min                    = native::abs_min;
            dsp::minmax                     = native::minmax;
            dsp::min_index                  = native::min_index;
            dsp::max_index                  = native::max_index;
            dsp::abs_max_index              = native::abs_max_index;
            dsp::abs_min_index              = native::abs_min_index;
            dsp::scale                      = native::scale;
            dsp::multiply                   = native::multiply;
            dsp::h_sum                      = native::h_sum;
            dsp::h_sqr_sum                  = native::h_sqr_sum;
            dsp::h_abs_sum                  = native::h_abs_sum;
            dsp::scalar_mul                 = native::scalar_mul;
            dsp::accumulate                 = native::accumulate;
            dsp::add                        = native::add;
            dsp::sub                        = native::sub;
            dsp::add_multiplied             = native::add_multiplied;
            dsp::sub_multiplied             = native::sub_multiplied;
            dsp::integrate                  = native::integrate;
            dsp::mix                        = native::mix;
            dsp::mix_add                    = native::mix_add;
            dsp::convolve_single            = native::convolve_single;
            dsp::convolve                   = native::convolve;
            dsp::reverse                    = native::reverse;
            dsp::direct_fft                 = native::direct_fft;
            dsp::reverse_fft                = native::reverse_fft;
            dsp::normalize_fft              = native::normalize_fft;
            dsp::center_fft                 = native::center_fft;
            dsp::combine_fft                = native::combine_fft;
            dsp::complex_mul                = native::complex_mul;
            dsp::complex_cvt2modarg         = native::complex_cvt2modarg;
            dsp::complex_cvt2reim           = native::complex_cvt2reim;
            dsp::complex_mod                = native::complex_mod;
            dsp::lr_to_ms                   = native::lr_to_ms;
            dsp::lr_to_mid                  = native::lr_to_mid;
            dsp::lr_to_side                 = native::lr_to_side;
            dsp::ms_to_lr                   = native::ms_to_lr;
            dsp::ms_to_left                 = native::ms_to_left;
            dsp::ms_to_right                = native::ms_to_right;
            dsp::avoid_denormals            = native::avoid_denormals;

            dsp::biquad_process             = native::biquad_process;
            dsp::biquad_process_multi       = native::biquad_process_multi;
            dsp::biquad_process_x1          = native::biquad_process_x1;
            dsp::biquad_process_x2          = native::biquad_process_x2;
            dsp::biquad_process_x4          = native::biquad_process_x4;
            dsp::biquad_process_x8          = native::biquad_process_x8;

            dsp::vec4_scalar_mul            = native::vec4_scalar_mul;
            dsp::vec4_push                  = native::vec4_push;
            dsp::vec4_unshift               = native::vec4_unshift;
            dsp::vec4_zero                  = native::vec4_zero;
            dsp::axis_apply_log             = native::axis_apply_log;
            dsp::rgba32_to_bgra32           = native::rgba32_to_bgra32;
        }
    } // namespace native
} // namespace dsp
